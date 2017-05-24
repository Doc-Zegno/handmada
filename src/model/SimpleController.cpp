//
// Created by syzegno on 24.04.17.
//


#include "SimpleController.h"

#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Attributes.h"
#include "SimpleIterator.h"
#include "SimplePolySequenceIterator.h"
#include "Path.h"
#include "Serializer.h"
#include "UnixFileStream.h"
#include "DynamicBufferStream.h"


namespace Handmada {
    SimpleControllerException::SimpleControllerException(const std::string& info)
            : runtime_error(info)
    { }



    // A d a p t e r
    class AttributeAdapter : public IAttribute
    {
    private:
        const std::string& name_;

    public:
        AttributeAdapter(const std::string& name) : name_(name) { }

        virtual const std::string& name() const override
        {
            return name_;
        }
        virtual void accept(IAttributeVisitor& visitor) const override { }
        virtual AttributeType::Type type() const override
        {
            return AttributeType::DUMMY;
        }
        virtual int compareTo(const IAttribute& attribute) const override
        {
            throw std::logic_error("this code must be unreachable");
        }
        virtual std::unique_ptr<IAttribute> clone() const override
        {
            throw std::logic_error("this code must be unreachable");
        }
    };



    // C h e c k i n g s
    bool SimpleController::containsUserId(UserId id) const
    {
        return usersAttributes_.find(id) != usersAttributes_.end();
    }


    bool SimpleController::containsServiceId(ServiceId id) const
    {
        return services_.find(id) != services_.end();
    }


    bool SimpleController::containsLogin(const std::string& login) const
    {
        return loginsToUserIds_.find(login) != loginsToUserIds_.end();
    }


    bool SimpleController::containsService(const std::string& service) const
    {
        return namesToServiceIds_.find(service) != namesToServiceIds_.end();
    }


    bool SimpleController::containsSpecialist(const std::string& name) const
    {
        return namesToSpecialistsIds_.find(name) != namesToSpecialistsIds_.end();
    }



    // A c t i v e    m e t h o d s
    void SimpleController::addLogin(const std::string& login, UserId id)
    {
        loginsToUserIds_.insert(std::make_pair(login, id));
        userIdsToLogins_.insert(std::make_pair(id, login));
        AttributeCollection collection;
        collection.insert(makeAttribute("login", login));
        usersAttributes_.insert(std::make_pair(id, std::move(collection)));
        messagesForUsers_.insert(std::make_pair(id, std::vector<Message>()));
    }


    size_t SimpleController::usersAmount() const
    {
        return loginsToUserIds_.size();
    }


    bool SimpleController::addService(
            const std::string& serviceName,
            const std::string& description,
            ServiceId id
    )
    {
        if (namesToServiceIds_.find(serviceName) == namesToServiceIds_.end()) {
            namesToServiceIds_.insert(std::make_pair(serviceName, id));
            services_.insert(std::make_pair(id, Service(serviceName, description, id)));

            using PredicateContainer = std::remove_reference<decltype(servicePredicates_)>::type::mapped_type;
            using RequirementContainer = std::remove_reference<decltype(serviceRequirements_)>::type::mapped_type;

            servicePredicates_.insert(std::make_pair(id, PredicateContainer()));
            serviceRequirements_.insert(std::make_pair(id, RequirementContainer()));
            return true;
        } else {
            return false;
        }
    }


    size_t SimpleController::servicesAmount() const
    {
        return namesToServiceIds_.size();
    }


    UserId SimpleController::signInUser(const std::string& login)
    {
        UserId id = loginsToUserIds_[login];
        if (isUserIdActive(id)) {
            return USER_ALREADY_SIGN_IN;
        } else {
            activeUsers_.insert(id);
            return id;
        }
    }


    void SimpleController::signOutUser(UserId id)
    {
        activeUsers_.erase(id);
    }


    bool SimpleController::isUserIdActive(UserId id) const
    {
        return activeUsers_.find(id) != activeUsers_.end();
    }


    bool SimpleController::addSpecialist(const std::string& name, SpecialistId id)
    {
        if (namesToSpecialistsIds_.find(name) == namesToSpecialistsIds_.end()) {
            idsToSpecialists_.insert(std::make_pair(id, Specialist(name)));
            namesToSpecialistsIds_.insert(std::make_pair(name, id));
            return true;
        } else {
            return false;
        }
    }


    OpCode SimpleController::attachSpecialistToService(SpecialistId specialistId, ServiceId serviceId)
    {
        auto specialist = idsToSpecialists_.find(specialistId);
        if (specialist == idsToSpecialists_.end()) {
            return OpCode::NO_SUCH_SPECIALIST;
        }

        auto service = services_.find(serviceId);
        if (service == services_.end()) {
            return OpCode::NO_SUCH_SERVICE;
        }

        auto result = service->second.addSpecialist(specialistId, &specialist->second);
        if (result) {
            return OpCode::SUCCESS;
        } else {
            return OpCode::ALREADY_ATTACHED;
        }
    }


    size_t SimpleController::specialistsAmount() const
    {
        return idsToSpecialists_.size();
    }


    Service& SimpleController::getServiceById(ServiceId id)
    {
        return services_.at(id);
    }


    void SimpleController::addMessageForUser(UserId id, const Message& message)
    {
        messagesForUsers_.at(id).push_back(message);
    }


    IDataBaseController::ServiceIterator SimpleController::getServiceIterator()
    {
        using Container = std::remove_reference<decltype(services_)>::type;

        return Prefab::makeSimpleIterator<Handmada::Service>(
                &services_,
                [](const Container::iterator& iterator) { return &iterator->second; }
        );
    }


    IDataBaseController::RequirementIterator SimpleController::getServiceRequirementIterator(ServiceId id)
    {
        using Container = std::remove_reference<decltype(serviceRequirements_.at(id))>::type;

        return Prefab::makeSimpleIterator<const RequirementDescriptor>(
                &serviceRequirements_.at(id),
                [](const Container::iterator& iterator) { return &(*iterator); }
        );
    }


    IDataBaseController::PredicateIterator SimpleController::getServicePredicateIterator(ServiceId id)
    {
        using Container = std::remove_reference<decltype(servicePredicates_.at(id))>::type;

        return Prefab::makeSimpleIterator<const BigPredicateDescriptor>(
                &servicePredicates_.at(id),
                [](const Container::iterator& iterator) { return &(*iterator); }
        );
    }


    void SimpleController::addServicePredicate(ServiceId id, BigPredicateDescriptor&& descriptor)
    {
        servicePredicates_.at(id).insert(std::move(descriptor));
    }


    void SimpleController::addServiceRequirement(ServiceId id, RequirementDescriptor&& descriptor)
    {
        serviceRequirements_.at(id).insert(std::move(descriptor));
    }


    const RequirementDescriptor* SimpleController::getServiceRequirementByName(ServiceId id, const std::string& name)
    {
        class DummyRequirement : public IRequirement
        {
        private:
            const std::string& name_;

            void crash() const
            {
                throw std::runtime_error("DummyRequirement: this code must be unreachable");
            }

        public:
            DummyRequirement(const std::string& requirementName) : name_(requirementName) { }

            virtual const std::string& name() const override { return name_; }
            virtual AttributeType::Type type() const override
            {
                crash();
                return AttributeType::DUMMY;
            }
            virtual std::unique_ptr<IAttribute> createAttribute() const override
            {
                crash();
                return std::unique_ptr<IAttribute>();
            }
            virtual std::unique_ptr<IRequirement> clone() const override
            {
                crash();
                return std::unique_ptr<IRequirement>();
            }
            virtual void accept(IRequirementVisitor& visitor) const override { crash(); }

            static std::unique_ptr<IRequirement> create(const std::string& requirementName)
            {
                return std::unique_ptr<IRequirement>(new DummyRequirement(requirementName));
            }
        };

        auto& requirements = serviceRequirements_.at(id);
        auto dummy = RequirementDescriptor(DummyRequirement::create(name));
        auto iterator = requirements.find(dummy);
        if (iterator != requirements.end()) {
            return &*iterator;
        }
        return nullptr;
    }


    const BigPredicateDescriptor* SimpleController::getServicePredicateById(
            ServiceId serviceId,
            PredicateId predicateId
    )
    {
        auto& descriptors = servicePredicates_.at(serviceId);
        auto dummy = BigPredicateDescriptor(predicateId, std::unique_ptr<IPredicate>(), PolyVector<IRequirement>());
        auto iterator = descriptors.find(dummy);
        if (iterator != descriptors.end()) {
            return &*iterator;
        }
        return nullptr;
    }


    IDataBaseController::MessageIterator SimpleController::getMessagesForUser(UserId id)
    {
        using Container = std::remove_reference<decltype(messagesForUsers_.at(id))>::type;

        auto& messages = messagesForUsers_.at(id);
        return Prefab::makeAdvancedIterator<Message>(
                messages.rbegin(),
                messages.rend(),
                [](const Container::reverse_iterator& iterator) { return &(*iterator); }
        );
    }


    void SimpleController::deleteMessageForUser(UserId id)
    {
        messagesForUsers_.at(id).clear();
    }


    void SimpleController::addUserAttribute(UserId id, AttributePtr&& attribute)
    {
        auto& attributes = usersAttributes_.at(id);
        attributes.insert(std::move(attribute));
    }


    IDataBaseController::AttributeIterator SimpleController::getUserAttributeIterator(UserId id)
    {
        using Container = std::remove_reference<decltype(usersAttributes_.at(id))>::type;

        return Prefab::makeSimpleIterator<Handmada::IAttribute>(
                &usersAttributes_.at(id),
                [](const Container::iterator& iterator) { return iterator->get(); }
        );
    }


    IDataBaseController::AttributeContainerPtr SimpleController::getUserAttributes(UserId id)
    {
        class Container : public IAttributeContainer
        {
        private:
            AttributeCollection* attributes_;
            const IAttribute* getConstAttribute(const std::string& name) const
            {
                AttributePtr attribute(new AttributeAdapter(name));
                auto iterator = attributes_->find(attribute);
                if (iterator != attributes_->end()) {
                    return iterator->get();
                }
                return nullptr;
            }

        public:
            Container(decltype(attributes_) attributes) : attributes_(attributes) { }
            virtual IAttribute* getAttributeByName(const std::string& name) override
            {
                return const_cast<IAttribute*>(getConstAttribute(name));
            }
            virtual const IAttribute* getAttributeByName(const std::string& name) const override
            {
                return getConstAttribute(name);
            }
        };

        return std::unique_ptr<Handmada::IAttributeContainer>(new Container(&usersAttributes_.at(id)));
    }


    IDataBaseController::SpecialistIterator SimpleController::getSpecialistIterator()
    {
        using Container = std::remove_reference<decltype(idsToSpecialists_)>::type;
        return Prefab::makeSimpleIterator<std::pair<const SpecialistId, Specialist>>(
                &idsToSpecialists_,
                [](Container::iterator& it) { return &*it; }
        );
    }


    const std::string& SimpleController::getLoginById(UserId id) const
    {
        return userIdsToLogins_.at(id);
    }


    size_t SimpleController::servicePredicatesAmount(ServiceId id) const
    {
        return servicePredicates_.at(id).size();
    }


    std::unique_ptr<IAttribute> SimpleController::removeUserAttribute(UserId id, const std::string& name)
    {
        auto& attributes = usersAttributes_.at(id);
        std::unique_ptr<IAttribute> adapter(new AttributeAdapter(name));
        auto iterator = attributes.find(adapter);
        if (iterator == attributes.end()) {
            return std::unique_ptr<IAttribute>();
        } else {
            auto copy = (*iterator)->clone();
            attributes.erase(iterator);
            return std::move(copy);
        }
    }



    // S w a p p i n g
    void SimpleController::checkOut()
    {
        openedFiles_ = 0;
        prologue();
        DynamicBufferStream stream;
        deserializeContainer(stream, loginsToUserIdsPath, loginsToUserIds_);
        deserializeContainer(stream, userIdsToLoginsPath, userIdsToLogins_);
        deserializeContainer(stream, usersAttributesPath, usersAttributes_);
        deserializeContainer(stream, messagesForUsersPath, messagesForUsers_);
        deserializeContainer(stream, namesToServiceIdsPath, namesToServiceIds_);
        deserializeContainer(stream, servicePredicatesPath, servicePredicates_);
        deserializeContainer(stream, serviceRequirementsPath, serviceRequirements_);
        deserializeContainer(stream, namesToSpecialistsIdsPath, namesToSpecialistsIds_);
        deserializeContainer(stream, idsToSpecialistsPath, idsToSpecialists_);
        deserializeContainer(stream, servicesPath, services_);
        epilogue();

        for (auto& pair : services_) {
            auto iterator = pair.second.getSpecialistsIterator();
            while (iterator->hasNext()) {
                auto next = iterator->next();
                next->second = &idsToSpecialists_.at(next->first);
            }
        }
    }


    void SimpleController::swap()
    {
        prologue();
        DynamicBufferStream stream;
        serializeContainer(stream, loginsToUserIdsPath, loginsToUserIds_);
        serializeContainer(stream, userIdsToLoginsPath, userIdsToLogins_);
        serializeContainer(stream, usersAttributesPath, usersAttributes_);
        serializeContainer(stream, messagesForUsersPath, messagesForUsers_);
        serializeContainer(stream, namesToServiceIdsPath, namesToServiceIds_);
        serializeContainer(stream, servicePredicatesPath, servicePredicates_);
        serializeContainer(stream, serviceRequirementsPath, serviceRequirements_);
        serializeContainer(stream, namesToSpecialistsIdsPath, namesToSpecialistsIds_);
        serializeContainer(stream, idsToSpecialistsPath, idsToSpecialists_);
        serializeContainer(stream, servicesPath, services_);
        epilogue();
    }


    template<typename TContainer>
    void SimpleController::serializeContainer(
            DynamicBufferStream& stream,
            const char* path,
            const TContainer& container
    )
    {
        int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        UnixFileStream fileStream(fd);
        Serializer::put(stream, container);
        fileStream.put(stream.buffer(), stream.position());
        stream.seek(0);
        close(fd);
    }


    template<typename TContainer>
    void SimpleController::deserializeContainer(
            DynamicBufferStream& stream,
            const char* path,
            TContainer& container
    )
    {
        int fd = open(path, O_RDONLY, 0666);
        if (fd == -1) {
            if (errno == ENOENT) {
                if (openedFiles_ > 0) {
                    throw SimpleControllerException("data base dump files were partly lost");
                } else {
                    return;
                };
            } else {
                throw SimpleControllerException(strerror(errno));
            }
        }
        openedFiles_++;


        const int CHUNK_SIZE = 256;
        char chunk[CHUNK_SIZE];
        ssize_t haveRead;
        stream.seek(0);
        while ((haveRead = read(fd, chunk, CHUNK_SIZE)) > 0) {
            stream.put(chunk, static_cast<size_t>(haveRead));
        }
        close(fd);

        stream.seek(0);
        Serializer::get(stream, container);
    }


    void SimpleController::prologue() const
    {
        mkdir(dumpPath, 0777);
        chmod(dumpPath, 0777);
        if (chdir(dumpPath) == -1) {
            throw SimpleControllerException(strerror(errno));
        }
    }


    void SimpleController::epilogue() const
    {
        if (chdir("..") == -1) {
            throw SimpleControllerException(strerror(errno));
        }
    }


    void SimpleController::removeDump() const
    {
        prologue();
        for (auto& path : paths) {
            if (unlink(path) < 0) {
                throw SimpleControllerException(strerror(errno));
            }
        }
        epilogue();
        if (rmdir(dumpPath) < 0) {
            throw SimpleControllerException(strerror(errno));
        }
    }
}
