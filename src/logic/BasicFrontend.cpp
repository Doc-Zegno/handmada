//
// Created by syzegno on 23.04.17.
//


#include "BasicFrontend.h"

#include <unordered_map>
#include <string>

#include "IInfoContainer.h"
#include "Responses.h"
#include "SnapShooter.h"
#include "MessageCreator.h"


namespace Handmada {
    BasicFrontend::BasicFrontend(IDataBaseController* controller)
            : controller_(controller)
    { }


    std::unique_ptr<IResponse> BasicFrontend::acceptRequest(const IRequest& request)
    {
        request.accept(*this);
        return std::move(response_);
    }


    void BasicFrontend::visit(const RegisterUserRequest& request)
    {
        auto& login = request.login();
        if (controller_->containsLogin(login)) {
            response_ = GeneralResponse::create(OpCode::ALREADY_REGISTERED);
        } else {
            UserId userId = static_cast<UserId>(controller_->usersAmount());
            controller_->addLogin(login, userId);
            response_ = RegisterUserResponse::create(userId);
        }
    }


    void BasicFrontend::visit(const SignInRequest& request)
    {
        auto& login = request.login();
        if (!controller_->containsLogin(login)) {
            response_ = GeneralResponse::create(OpCode::NOT_REGISTERED);
        } else {
            auto userId = controller_->signInUser(login);
            if (userId == USER_ALREADY_SIGN_IN) {
                response_ = GeneralResponse::create(OpCode::ALREADY_SIGN_IN);
            } else {
                response_ = SignInResponse::create(userId);
            }
        }
    }


    void BasicFrontend::visit(const SignOutRequest& request)
    {
        UserId userId = request.userId();
        if (!controller_->isUserIdActive(userId)) {
            response_ = GeneralResponse::create(OpCode::ALREADY_SIGN_OUT);
        } else {
            auto& login = controller_->getLoginById(userId);
            controller_->signOutUser(userId);
            response_ = SignOutResponse::create(login);
        }
    }


    void BasicFrontend::visit(const AddServiceRequest& request)
    {
        ServiceId serviceId = generateServiceId();
        if (controller_->addService(request.name(), request.description(), serviceId)) {
            response_ = AddServiceResponse::create(serviceId);
        } else {
            response_ = GeneralResponse::create(OpCode::SERVICE_EXISTS);
        }
    }


    void BasicFrontend::visit(const AddSpecialistRequest& request)
    {
        SpecialistId specialistId = generateSpecialistId();
        if (controller_->addSpecialist(request.name(), specialistId)) {
            response_ = AddSpecialistResponse::create(specialistId);
        } else {
            response_ = GeneralResponse::create(OpCode::SPECIALIST_EXISTS);
        }
    }


    void BasicFrontend::visit(const AddPriorityRuleRequest& request)
    {
        auto serviceId = request.serviceId();
        if (!controller_->containsServiceId(serviceId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_SERVICE);
            return;
        }

        PolyVector<IRequirement> markedForAdding;
        std::vector<const RequirementDescriptor*> markedForIncreasing;
        std::unordered_map<std::string, AttributeType::Type> collisions;

        for (auto& requirement : request.requirements()) {
            auto candidate = controller_->getServiceRequirementByName(
                    serviceId, requirement->name()
            );
            if (!candidate) {
                markedForAdding.push_back(requirement->clone());
            } else {
                if (candidate->requirement().type() == requirement->type()) {
                    markedForIncreasing.push_back(candidate);
                } else {
                    collisions.insert(std::make_pair(
                            requirement->name(), candidate->requirement().type()
                    ));
                }
            }
        }

        if (collisions.empty()) {
            for (auto& requirement : markedForAdding) {
                controller_->addServiceRequirement(
                        serviceId, RequirementDescriptor(std::move(requirement))
                );
            }
            for (auto& descriptor : markedForIncreasing) {
                descriptor->addUsage();
            }
            auto predicateId = generatePredicateId(serviceId);
            controller_->addServicePredicate(
                    serviceId,
                    BigPredicateDescriptor(
                            predicateId,
                            request.predicate().clone(),
                            SnapShooter::copy(request.requirements())
                    )
            );
            response_ = AddPriorityRuleResponse::create(serviceId, predicateId);
        } else {
            response_ = RequirementCollisionResponse::create(std::move(collisions));
        }
    }


    void BasicFrontend::visit(const AddUserAttributeRequest& request)
    {
        auto userId = request.userId();
        if (!controller_->containsUserId(userId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_USER);
            return;
        }

        std::vector<std::string> markedForAdding;
        auto container = controller_->getUserAttributes(userId);
        for (auto& attribute : request.attributes()) {
            if (!container->getAttributeByName(attribute->name())) {
                markedForAdding.push_back(attribute->name());
                controller_->addUserAttribute(userId, attribute->clone());
            }
        }

        response_ = AddUserAttributeResponse::create(userId, std::move(markedForAdding));
    }


    void BasicFrontend::visit(const RemoveUserAttributeRequest& request)
    {
        auto userId = request.userId();
        if (!controller_->containsUserId(userId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_USER);
            return;
        }

        PolyVector<IAttribute> deleted;
        for (auto& name : request.attributes()) {
            auto attribute = controller_->removeUserAttribute(userId, name);
            if (attribute) {
                deleted.push_back(std::move(attribute));
            }
        }
        response_ = RemoveUserAttributeResponse::create(userId, std::move(deleted));
    }


    void BasicFrontend::visit(const AttachSpecialistRequest& request)
    {
        auto specialistId = request.specialistId();
        auto serviceId = request.serviceId();

        auto code = controller_->attachSpecialistToService(specialistId, serviceId);
        if (code == OpCode::SUCCESS) {
            response_ = AttachSpecialistResponse::create(specialistId, serviceId);
        } else {
            response_ = GeneralResponse::create(code);
        }
    }


    void BasicFrontend::visit(const MakeAppointmentRequest& request)
    {
        auto userId = request.userId();
        auto serviceId = request.serviceId();

        if (!controller_->containsUserId(userId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_USER);
            return;
        }
        if (!controller_->containsServiceId(serviceId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_SERVICE);
            return;
        }
        auto& service = controller_->getServiceById(serviceId);
        if (service.hasUser(userId)) {
            response_ = GeneralResponse::create(OpCode::ALREADY_IN_QUEUE);
            return;
        }

        PolyVector<IRequirement> missing;
        auto attributes = controller_->getUserAttributes(userId);
        auto requirementIterator = controller_->getServiceRequirementIterator(serviceId);
        while (requirementIterator->hasNext()) {
            auto& requirement = requirementIterator->next()->requirement();
            auto attribute = attributes->getAttributeByName(requirement.name());
            if (!attribute) {
                missing.push_back(requirement.clone());
            }
        }

        if (missing.empty()) {
            auto predicateIterator = controller_->getServicePredicateIterator(serviceId);
            bool hasPriority = true;
            while (predicateIterator->hasNext()) {
                auto& predicate = predicateIterator->next()->predicate();
                hasPriority = predicate(*attributes);
                if (!hasPriority) {
                    break;
                }
            }
            service.addUser(userId, hasPriority);
            response_ = MakeAppointmentResponse::create(userId, serviceId, hasPriority);
        } else {
            response_ = MissingAttributeResponse::create(std::move(missing));
        }
    }


    void BasicFrontend::runServices()
    {
        class Container : public IInfoContainer
        {
        public:
            std::vector<std::tuple<UserId, ServiceId, Specialist*>> infoVec;
            virtual void addInfo(UserId userId, ServiceId serviceId, Specialist* specialist) override
            {
                infoVec.push_back(std::make_tuple(userId, serviceId, specialist));
            }
        };

        Container container;
        auto iterator = controller_->getServiceIterator();
        while (iterator->hasNext()) {
            iterator->next()->run(container);
        }

        for (auto& tuple : container.infoVec) {
            addMessageForUser(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
        }
    }


    void BasicFrontend::visit(const GetMessageRequest& request)
    {
        auto userId = request.userId();
        if (!controller_->containsUserId(userId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_USER);
            return;
        }

        auto iterator = controller_->getMessagesForUser(userId);
        std::vector<Message> messages;
        while (iterator->hasNext()) {
            messages.push_back(*iterator->next());
        }
        controller_->deleteMessageForUser(userId);
        response_ = GetMessageResponse::create(std::move(messages));
    }


    void BasicFrontend::visit(const GetServiceDescriptorRequest& request)
    {
        std::vector<ServiceDescriptor> descriptors;
        auto iterator = controller_->getServiceIterator();
        while (iterator->hasNext()) {
            auto service = iterator->next();
            descriptors.push_back(
                    ServiceDescriptor(service->id(), service->name, service->description)
            );
        }
        response_ = GetServiceDescriptorResponse::create(std::move(descriptors));
    }


    void BasicFrontend::visit(const GetSpecialistDescriptorRequest& request)
    {
        auto serviceId = request.serviceId();
        if (isServiceIdValid(serviceId)) {
            if (!controller_->containsServiceId(serviceId)) {
                response_ = GeneralResponse::create(OpCode::NO_SUCH_SERVICE);
                return;
            }

            auto& service = controller_->getServiceById(serviceId);
            auto iterator = service.getSpecialistsIterator();
            std::vector<SpecialistDescriptor> descriptors;
            while (iterator->hasNext()) {
                auto pair = iterator->next();
                descriptors.push_back(
                        SpecialistDescriptor(pair->first, pair->second->name())
                );
            }
            response_ = GetSpecialistDescriptorResponse::create(std::move(descriptors));

        } else {
            auto iterator = controller_->getSpecialistIterator();
            std::vector<SpecialistDescriptor> descriptors;
            while (iterator->hasNext()) {
                auto pair = iterator->next();
                descriptors.push_back(
                        SpecialistDescriptor(pair->first, pair->second.name())
                );
            }
            response_ = GetSpecialistDescriptorResponse::create(std::move(descriptors));
        }
    }


    void BasicFrontend::visit(const GetUserAttributeRequest& request)
    {
        auto userId = request.userId();
        if (!controller_->containsUserId(userId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_USER);
            return;
        }

        PolyVector<IAttribute> attributes;
        auto iterator = controller_->getUserAttributeIterator(userId);
        while (iterator->hasNext()) {
            auto attribute = iterator->next();
            attributes.push_back(attribute->clone());
        }
        response_ = GetUserAttributeResponse::create(std::move(attributes));
    }


    void BasicFrontend::visit(const GetUserDescriptorRequest& request)
    {
        auto serviceId = request.serviceId();
        if (!controller_->containsServiceId(serviceId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_SERVICE);
            return;
        }

        std::vector<UserDescriptor> descriptors;
        auto& service = controller_->getServiceById(serviceId);

        auto premium = service.getPremiumUsersIterator();
        while (premium->hasNext()) {
            auto userId = *premium->next();
            auto& login = controller_->getLoginById(userId);
            descriptors.push_back(UserDescriptor(userId, login, true));
        }

        auto standard = service.getStandardUsersIterator();
        while (standard->hasNext()) {
            auto userId = *standard->next();
            auto& login = controller_->getLoginById(userId);
            descriptors.push_back(UserDescriptor(userId, login, false));
        }

        response_ = GetUserDescriptorResponse::create(std::move(descriptors));
    }


    void BasicFrontend::visit(const GetPriorityRuleRequest& request)
    {
        auto serviceId = request.serviceId();
        if (!controller_->containsServiceId(serviceId)) {
            response_ = GeneralResponse::create(OpCode::NO_SUCH_SERVICE);
            return;
        }

        std::vector<SmallPredicateDescriptor> descriptors;
        auto iterator = controller_->getServicePredicateIterator(serviceId);
        while (iterator->hasNext()) {
            auto descriptor = iterator->next();
            descriptors.push_back(descriptor->getSmallDescriptor());
        }
        response_ = GetPriorityRuleResponse::create(std::move(descriptors));
    }



    // A u x i l i a r y
    void BasicFrontend::addMessageForUser(
            UserId userId,
            ServiceId serviceId,
            Specialist* specialist
    )
    {
        std::time_t when = std::time(nullptr);
        const std::string& from = specialist->name();
        const std::string& to = controller_->getLoginById(userId);
        std::string theme = controller_->getServiceById(serviceId).name;

        controller_->addMessageForUser(
                userId, MessageCreator::create(when, from, to, theme)
        );
    }


    ServiceId BasicFrontend::generateServiceId() const
    {
        return controller_->servicesAmount();
    }


    SpecialistId BasicFrontend::generateSpecialistId() const
    {
        return controller_->specialistsAmount();
    }


    PredicateId BasicFrontend::generatePredicateId(ServiceId id) const
    {
        return controller_->servicePredicatesAmount(id);
    }



    /*UserId BasicFrontend::registerUser(const std::string& login)
    {
        if (!controller_->containsLogin(login)) {
            UserId id = controller_->usersAmount();
            controller_->addLogin(login, id);
            return id;
        } else {
            return INVALID_USER_ID;
        }
    }


    BasicFrontend::BasicFrontend(IDataBaseController* controller) : controller_(controller)
    { }


    ServiceId BasicFrontend::addService(const std::string& serviceName, const std::string& description)
    {
        if (!controller_->containsService(serviceName)) {
            ServiceId id = controller_->servicesAmount();
            controller_->addService(serviceName, description, id);
            return id;
        } else {
            return INVALID_SERVICE_ID;
        }
    }


    size_t BasicFrontend::printUserInfo(UserId id, std::ostream& output) const
    {
        size_t count = 0;
        auto iterator = controller_->getUserAttributeIterator(id);
        output << "ID: " << id << std::endl;
        AttributePrinter printer(output);
        while (iterator->hasNext()) {
            iterator->next()->accept(printer);
        }
        return count;
    }


    UserId BasicFrontend::signIn(const std::string& login) const
    {
        if (!controller_->containsLogin(login)) {
            return INVALID_USER_ID;
        } else {
            return controller_->signInUser(login);
        }
    }


    void BasicFrontend::signOut(UserId id) const
    {
        controller_->signOutUser(id);
    }


    bool BasicFrontend::isUserIdActive(UserId id) const
    {
        return controller_->isUserIdActive(id);
    }


    SpecialistId BasicFrontend::addSpecialist(const std::string& name)
    {
        SpecialistId id = controller_->specialistsAmount();
        if (controller_->containsSpecialist(name)) {
            return INVALID_SPECIALIST_ID;
        } else {
            controller_->addSpecialist(name, id);
            return id;
        }
    }


    OpCode BasicFrontend::attachSpecialistToService(SpecialistId specialistId, ServiceId serviceId)
    {
        return controller_->attachSpecialistToService(specialistId, serviceId);
    }


    void BasicFrontend::printServices(std::ostream& output) const
    {
        auto iterator = controller_->getServiceIterator();
        while (iterator->hasNext()) {
            Service* service = iterator->next();
            output << "ID: " << service->id() << std::endl;
            output << service->name << std::endl;
            if (service->description.length() != 0) {
                output << service->description << std::endl;
            }
            output << std::endl;
        }
    }


    void BasicFrontend::runServices()
    {
        class Container : public IInfoContainer
        {
        public:
            std::vector<std::tuple<UserId, ServiceId, Specialist*>> infoVec;
            virtual void addInfo(UserId userId, ServiceId serviceId, Specialist* specialist) override
            {
                infoVec.push_back(std::make_tuple(userId, serviceId, specialist));
            }
        };

        Container container;
        auto iterator = controller_->getServiceIterator();
        while (iterator->hasNext()) {
            iterator->next()->run(container);
        }

        for (auto& tuple : container.infoVec) {
            UserId id = std::get<0>(tuple);
            std::time_t now = std::time(nullptr);
            std::string message = std::ctime(&now);
            message += "\tyou were accepted by ";
            message += std::get<2>(tuple)->name();
            message += ", ";
            message += controller_->getServiceById(std::get<1>(tuple)).name;
            controller_->addMessageForUser(id, message);
        }
    }


    size_t BasicFrontend::printMessagesForUser(UserId id, std::ostream& output) const
    {
        size_t count = 0;
        auto iterator = controller_->getMessagesForUser(id);
        while (iterator->hasNext()) {
            output << *iterator->next() << "\n\n";
            count++;
        }
        controller_->deleteMessageForUser(id);
        return count;
    }


    void BasicFrontend::addUserAttribute(UserId id, std::unique_ptr<Handmada::IAttribute>&& attribute)
    {
        controller_->addUserAttribute(id, std::move(attribute));
    }


    OpCode BasicFrontend::makeAppointmentForUser(
            UserId userId,
            ServiceId serviceId,
            IInsertAdapter<Handmada::IRequirement>& requirements
    )
    {
        OpCode code = OpCode::SUCCESS;
        auto attributes = controller_->getUserAttributes(userId);

        auto iterator = controller_->getServiceRequirementIterator(serviceId);
        while (iterator->hasNext()) {
            auto requirement = iterator->next();
            IAttribute* attribute = attributes->getAttributeByName(requirement->name());
            if (!attribute) {
                requirements.insert(requirement->clone());
                code = OpCode::MISSING_ATTRIBUTES;
            }
        }


        if (code != OpCode::SUCCESS) {
            return code;
        }

        auto predicateIterator = controller_->getServicePredicateIterator(serviceId);
        bool hasPriority = true;
        while (predicateIterator->hasNext()) {
            IPredicate* predicate = predicateIterator->next();
            hasPriority = predicate->operator()(*attributes);
            if (!hasPriority) {
                break;
            }
        }

        auto& service = controller_->getServiceById(serviceId);
        if (service.addUser(userId, hasPriority)) {
            std::time_t now = std::time(nullptr);
            std::string message = std::ctime(&now);
            message += "\tyou are in queue to ";
            message += service.name;
            if (hasPriority) {
                message += "; you got a priority";
            }
            controller_->addMessageForUser(userId, message);
            return OpCode::SUCCESS;
        } else {
            return OpCode::ALREADY_IN_QUEUE;
        }
    }


    void BasicFrontend::addServicePredicate(ServiceId id, std::unique_ptr<Handmada::IPredicate>&& predicate)
    {
        controller_->addServicePredicate(id, std::move(predicate));
    }


    void BasicFrontend::addServiceRequirement(ServiceId id, std::unique_ptr<Handmada::IRequirement>&& requirement)
    {
        controller_->addServiceRequirement(id, std::move(requirement));
    }


    OpCode BasicFrontend::addServicePredicateAndRequirements(
            ServiceId id,
            std::unique_ptr<Handmada::IPredicate>&& predicate,
            IIterator<Handmada::IRequirement>& requirementIterator,
            IMapInserter<std::string, Handmada::AttributeType::Type>& collisions
    )
    {
        std::vector<std::unique_ptr<Handmada::IRequirement>> markedForAdding;
        OpCode code = OpCode::SUCCESS;

        while (requirementIterator.hasNext()) {
            IRequirement* requirement = requirementIterator.next();
            IRequirement* candidate = controller_->getServiceRequirementByName(id, requirement->name());
            if (!candidate) {
                markedForAdding.push_back(requirement->clone());
            } else if (candidate->type() != requirement->type()) {
                collisions.insert(candidate->name(), candidate->type());
                code = OpCode::REQUIREMENT_TYPE_COLLISION;
            }
        }

        if (code == OpCode::SUCCESS) {
            for (auto& requirement : markedForAdding) {
                controller_->addServiceRequirement(id, std::move(requirement));
            }
            controller_->addServicePredicate(id, std::move(predicate));
        }
        return code;
    }


    void BasicFrontend::printSpecialists(std::ostream& output) const
    {
        auto iterator = controller_->getSpecialistIterator();
        while (iterator->hasNext()) {
            auto pair = iterator->next();
            output << "ID: " << pair->first << std::endl;
            output << "name: " << pair->second.name() << "\n\n";
        }
    }


    OpCode BasicFrontend::printSpecialistsAttachedToService(ServiceId id, std::ostream& output) const
    {
        try {
            auto& service = controller_->getServiceById(id);
            service.printSpecialists(output);
            return OpCode::SUCCESS;
        } catch (std::exception& e) {
            return  OpCode::NO_SUCH_SERVICE;
        }
    }


    OpCode BasicFrontend::printServicePredicates(ServiceId id, std::ostream& output) const
    {
        auto iterator = controller_->getServicePredicateIterator(id);
        if (!iterator) {
            return OpCode::NO_SUCH_SERVICE;
        }

        int i = 1;
        PredicatePrinter printer(output);
        while (iterator->hasNext()) {
            auto predicate = iterator->next();
            output << '#' << i << ":\n";
            predicate->accept(printer);
            output << std::endl;
        }
        return OpCode::SUCCESS;
    }



    // N e w    m e t h o d s
    void BasicFrontend::getServiceDescriptors(std::vector<ServiceDescriptor>& descriptors) const
    {
        auto iterator = controller_->getServiceIterator();
        while (iterator->hasNext()) {
            auto service = iterator->next();
            ServiceDescriptor descriptor(service->name, service->description, service->id());
            descriptors.push_back(std::move(descriptor));
        }
    }


    void BasicFrontend::getSpecialistDescriptors(std::vector<SpecialistDescriptor>& descriptors) const
    {

    }

    OpCode
    BasicFrontend::getSpecialistDescriptors(std::vector<SpecialistDescriptor>& descriptors, ServiceId serviceId) const
    {
        return OpCode::GENERAL_FAILURE;
    }

    OpCode BasicFrontend::getUserDescriptors(std::vector<UserDescriptor>& descriptors, ServiceId serviceId) const
    {
        return OpCode::GENERAL_FAILURE;
    }

    OpCode
    BasicFrontend::getServicePredicates(std::vector<std::unique_ptr<IPredicate>>& predicates, ServiceId serviceId) const
    {
        return OpCode::GENERAL_FAILURE;
    }

    OpCode BasicFrontend::getUserAttributes(std::vector<std::unique_ptr<IAttribute>>& attributes, UserId userId) const
    {
        return OpCode::GENERAL_FAILURE;
    }*/
}
