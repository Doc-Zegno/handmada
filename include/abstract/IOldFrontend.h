//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IOLDFRONTEND_H
#define EQUEUE_V2_IOLDFRONTEND_H



#include <string>
#include <vector>
#include <iostream>

#include "IDataBaseController.h"
#include "Types.h"
#include "OpCode.h"
#include "Service.h"
#include "IInfoContainer.h"
#include "IInsertAdapter.h"
#include "IMapInserter.h"
#include "Descriptors.h"


namespace Handmada {
    // TODO: Jesus! remove this!
    class IOldFrontend
    {
    public:
        virtual UserId registerUser(const std::string& login) = 0;
        virtual UserId signIn(const std::string& login) const = 0;
        virtual void signOut(UserId id) const = 0;
        virtual bool isUserIdActive(UserId id) const = 0;

        virtual void addUserAttribute(
                UserId id,
                std::unique_ptr<Handmada::IAttribute>&& attribute
        ) = 0;
        virtual size_t printUserInfo(UserId id, std::ostream& output) const = 0;
        virtual size_t printMessagesForUser(UserId id, std::ostream& output) const = 0;

        virtual ServiceId addService(
                const std::string& serviceName,
                const std::string& description = ""
        ) = 0;
        /// \deprecated consider using getServiceDescriptors instead
        virtual void printServices(std::ostream& output) const = 0;
        virtual OpCode addServicePredicateAndRequirements(
                ServiceId id,
                std::unique_ptr<Handmada::IPredicate>&& predicate,
                IIterator<Handmada::IRequirement>& requirementIterator,
                IMapInserter<std::string, Handmada::AttributeType::Type>& collisions
        ) = 0;
        /// \deprecated consider using getServicePredicates instead
        virtual OpCode printServicePredicates(
                ServiceId id,
                std::ostream& output
        ) const = 0;


        virtual SpecialistId addSpecialist(const std::string& name) = 0;
        virtual OpCode attachSpecialistToService(
                SpecialistId specialistId,
                ServiceId serviceId
        ) = 0;
        /// \deprecated consider using getSpecialistDescriptors instead
        virtual void printSpecialists(std::ostream& output) const = 0;
        /// \deprecated consider using overloaded version of getSpecialistDescriptors instead
        virtual OpCode printSpecialistsAttachedToService(
                ServiceId id,
                std::ostream& output
        ) const = 0;

        virtual OpCode makeAppointmentForUser(
                UserId userId,
                ServiceId serviceId,
                IInsertAdapter<Handmada::IRequirement>& requirements
        ) = 0;


        // T e s t    m e t h o d s
        virtual void getServiceDescriptors(std::vector<ServiceDescriptor>& descriptors) const = 0;
        virtual void getSpecialistDescriptors(std::vector<SpecialistDescriptor>& descriptors) const = 0;
        virtual OpCode getSpecialistDescriptors(
                std::vector<SpecialistDescriptor>& descriptors,
                ServiceId serviceId
        ) const = 0;
        virtual OpCode getUserDescriptors(
                std::vector<UserDescriptor>& descriptors,
                ServiceId serviceId
        ) const = 0;
        virtual OpCode getServicePredicates(
                std::vector<std::unique_ptr<IPredicate>>& predicates,
                ServiceId serviceId
        ) const = 0;
        virtual OpCode getUserAttributes(
                std::vector<std::unique_ptr<IAttribute>>& attributes,
                UserId userId
        ) const = 0;


        // R e q u e s t D r i v e n


        virtual ~IOldFrontend() { }
    };
}



#endif //EQUEUE_V2_IOLDFRONTEND_H
