//
// Created by syzegno on 24.04.17.
//

#ifndef EQUEUE_V2_SIMPLECONTROLLER_H
#define EQUEUE_V2_SIMPLECONTROLLER_H


#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "IDataBaseController.h"
#include "DynamicBufferStream.h"
#include "Types.h"
#include "Specialist.h"
#include "Service.h"
#include "Descriptors.h"
#include "DescriptorHash.h"
#include "DescriptorKeyComparator.h"


namespace Handmada {
    class SimpleControllerException : public std::runtime_error
    {
    public:
        SimpleControllerException(const std::string& info);
    };



    /**
     * A bit overcomplicated implementation of IDataBaseController.
     * Swaps session data into files
     */
    class SimpleController : public IDataBaseController
    {
    private:
        class AttributeHash
        {
        public:
            size_t operator()(const AttributePtr& attribute) const
            {
                return std::hash<std::string>()(attribute->name());
            }
        };


        class AttributeComparator
        {
        public:
            bool operator()(const AttributePtr& a, const AttributePtr& b) const
            {
                return a->name() == b->name();
            }
        };


        using AttributeCollection = std::unordered_set<AttributePtr, AttributeHash, AttributeComparator>;


        // U s e r s
        std::unordered_map<std::string, Handmada::UserId> loginsToUserIds_;
        std::unordered_map<UserId, std::string> userIdsToLogins_;
        std::unordered_map<
                UserId,
                AttributeCollection
        > usersAttributes_;

        std::unordered_map<
                Handmada::UserId,
                std::vector<Message>
        > messagesForUsers_;

        std::unordered_set<Handmada::UserId> activeUsers_;


        // S e r v i c e s
        std::unordered_map<std::string, Handmada::ServiceId> namesToServiceIds_;
        std::unordered_map<Handmada::ServiceId, Handmada::Service> services_;
        std::unordered_map<
                Handmada::ServiceId,
                std::unordered_set<
                        BigPredicateDescriptor,
                        PredicateDescriptorHash,
                        PredicateDescriptorKeyComparator
                >
        > servicePredicates_;

        std::unordered_map<
                Handmada::ServiceId,
                std::unordered_set<
                        RequirementDescriptor,
                        RequirementDescriptorHash,
                        RequirementDescriptorKeyComparator
                >
        > serviceRequirements_;


        // S p e c i a l i s t s
        std::unordered_map<std::string, Handmada::SpecialistId> namesToSpecialistsIds_;
        std::unordered_map<Handmada::SpecialistId, Handmada::Specialist> idsToSpecialists_;


        template<typename TContainer>
        void serializeContainer(
                DynamicBufferStream& stream,
                const char* path,
                const TContainer& container
        );

        template<typename TContainer>
        void deserializeContainer(
                DynamicBufferStream& stream,
                const char* path,
                TContainer& container
        );

        void prologue() const;
        void epilogue() const;
        int openedFiles_;

    public:
        virtual bool containsUserId(UserId id) const override;
        virtual bool containsServiceId(ServiceId id) const override;

        virtual void checkOut() override;
        virtual void swap() override;

        virtual bool isUserIdActive(UserId id) const override;
        virtual UserId signInUser(const std::string& login) override;
        virtual void signOutUser(UserId id) override;
        virtual void addLogin(const std::string& login, UserId id) override;
        virtual bool containsLogin(const std::string& login) const override;
        virtual void addMessageForUser(UserId id, const Message& message) override;
        virtual size_t usersAmount() const override;

        virtual const std::string& getLoginById(UserId id) const override;


        virtual bool addService(
                const std::string& serviceName,
                const std::string& description,
                ServiceId id
        ) override;
        virtual Service& getServiceById(ServiceId id) override;
        virtual bool containsService(const std::string& service) const override;
        virtual size_t servicesAmount() const override;


        virtual ServiceIterator getServiceIterator() override;
        virtual RequirementIterator getServiceRequirementIterator(ServiceId id) override;
        virtual PredicateIterator getServicePredicateIterator(ServiceId id) override;
        virtual void addServicePredicate(
                ServiceId id,
                BigPredicateDescriptor&& descriptor
        ) override;
        virtual void addServiceRequirement(
                ServiceId id,
                RequirementDescriptor&& descriptor
        ) override;
        virtual const RequirementDescriptor* getServiceRequirementByName(
                ServiceId id, const std::string& name
        ) override;
        virtual const BigPredicateDescriptor* getServicePredicateById(
                ServiceId serviceId, PredicateId predicateId
        ) override;

        virtual size_t servicePredicatesAmount(ServiceId id) const override;


        virtual bool addSpecialist(const std::string& name, SpecialistId id) override;
        virtual OpCode attachSpecialistToService(
                SpecialistId specialistId,
                ServiceId serviceId
        ) override;
        virtual bool containsSpecialist(const std::string& name) const override;
        virtual SpecialistIterator getSpecialistIterator() override;

        virtual size_t specialistsAmount() const override;
        virtual MessageIterator getMessagesForUser(UserId id) override;
        virtual void deleteMessageForUser(UserId id) override;
        virtual void addUserAttribute(UserId id, AttributePtr&& attribute) override;

        virtual AttributePtr removeUserAttribute(UserId id, const std::string& name) override;

        virtual AttributeContainerPtr getUserAttributes(UserId id) override;
        virtual AttributeIterator getUserAttributeIterator(UserId id) override;

        void removeDump() const;
    };
}


#endif //EQUEUE_V2_SIMPLECONTROLLER_H
