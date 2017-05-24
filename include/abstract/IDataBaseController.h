//
// Created by syzegno on 23.04.17.
//

#ifndef EQUEUE_V2_IDATABASECONTROLLER_H
#define EQUEUE_V2_IDATABASECONTROLLER_H


#include <iostream>
#include <memory>

#include "Types.h"
#include "OpCode.h"
#include "IAttributeContainer.h"
#include "Service.h"
#include "IIterator.h"
#include "IRequirement.h"
#include "IPredicate.h"
#include "Descriptors.h"
#include "Message.h"


namespace Handmada {
    class IDataBaseController
    {
    public:
        // S h o r t c u t s
        using MessageIterator = std::unique_ptr<Handmada::IIterator<Message>>;
        using AttributePtr = std::unique_ptr<Handmada::IAttribute>;
        using AttributeIterator = std::unique_ptr<Handmada::IIterator<Handmada::IAttribute>>;
        using AttributeContainerPtr = std::unique_ptr<Handmada::IAttributeContainer>;
        using ServiceIterator = std::unique_ptr<Handmada::IIterator<Handmada::Service>>;
        using RequirementIterator = std::unique_ptr<Handmada::IIterator<const RequirementDescriptor>>;
        using PredicateIterator = std::unique_ptr<Handmada::IIterator<const BigPredicateDescriptor>>;
        using PredicatePtr = std::unique_ptr<Handmada::IPredicate>;
        using RequirementPtr = std::unique_ptr<Handmada::IRequirement>;
        using SpecialistIterator = std::unique_ptr<IIterator<std::pair<const SpecialistId, Specialist>>>;

        // S w a p p i n g
        virtual void checkOut() = 0;
        virtual void swap() = 0;

        // C h e c k i n g s
        virtual bool containsUserId(UserId id) const = 0;
        virtual bool containsServiceId(ServiceId id) const = 0;
        virtual bool containsLogin(const std::string& login) const = 0;
        virtual bool containsService(const std::string& service) const = 0;
        virtual bool containsSpecialist(const std::string& name) const = 0;

        // U s e r    c o n t r o l
        virtual bool isUserIdActive(UserId id) const = 0;
        virtual UserId signInUser(const std::string& login) = 0;
        virtual void signOutUser(UserId id) = 0;
        virtual void addLogin(const std::string& login, UserId id) = 0;
        virtual const std::string& getLoginById(UserId id) const = 0;
        virtual size_t usersAmount() const = 0;

        // M e s s a g e s    f o r    u s e r
        virtual void addMessageForUser(UserId id, const Message& message) = 0;
        virtual MessageIterator getMessagesForUser(UserId id) = 0;
        virtual void deleteMessageForUser(UserId id) = 0;

        // S e r v i c e    C o n t r o l
        virtual bool addService(const std::string& serviceName, const std::string& description, ServiceId id) = 0;
        virtual Service& getServiceById(ServiceId id) = 0;
        virtual ServiceIterator getServiceIterator() = 0;
        virtual size_t servicesAmount() const = 0;

        // A t t r i b u t e s    a n d    p r i o r i t y    C o n t r o l
        virtual void addUserAttribute(UserId id, AttributePtr&& attribute) = 0;
        virtual AttributePtr removeUserAttribute(UserId id, const std::string& name) = 0;
        virtual AttributeContainerPtr getUserAttributes(UserId id) = 0;
        virtual AttributeIterator getUserAttributeIterator(UserId id) = 0;
        virtual RequirementIterator getServiceRequirementIterator(ServiceId id) = 0;
        virtual const RequirementDescriptor* getServiceRequirementByName(ServiceId id, const std::string& name) = 0;
        virtual PredicateIterator getServicePredicateIterator(ServiceId id) = 0;
        virtual const BigPredicateDescriptor* getServicePredicateById(ServiceId serviceId, PredicateId predicateId) = 0;
        virtual size_t servicePredicatesAmount(ServiceId id) const = 0;
        virtual void addServicePredicate(ServiceId id, BigPredicateDescriptor&& descriptor) = 0;
        virtual void addServiceRequirement(ServiceId id, RequirementDescriptor&& descriptor) = 0;

        // S p e c i a l i s t    C o n t r o l
        virtual bool addSpecialist(const std::string& name, SpecialistId id) = 0;
        virtual OpCode attachSpecialistToService(SpecialistId specialistId, ServiceId serviceId) = 0;
        virtual size_t specialistsAmount() const = 0;
        virtual SpecialistIterator getSpecialistIterator() = 0;


        virtual ~IDataBaseController() { }
    };
}


#endif //EQUEUE_V2_IDATABASECONTROLLER_H
