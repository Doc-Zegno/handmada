//
// Created by syzegno on 18.05.17.
//

#ifndef EQUEUE_V2_DESCRIPTORS_H
#define EQUEUE_V2_DESCRIPTORS_H


#include <string>

#include "Types.h"
#include "IPredicate.h"
#include "IRequirement.h"
#include "PolyVector.h"


namespace Handmada {
    class ServiceDescriptor
    {
    private:
        ServiceId id_;
        std::string name_;
        std::string description_;

    public:
        ServiceDescriptor() = default;
        ServiceDescriptor(ServiceId id, const std::string& name, const std::string& description);

        const std::string& name() const;
        const std::string& description() const;
        ServiceId id() const;
    };


    class SpecialistDescriptor
    {
    private:
        SpecialistId id_;
        std::string name_;

    public:
        SpecialistDescriptor() = default;
        SpecialistDescriptor(SpecialistId id, const std::string& name);

        const std::string& name() const;
        SpecialistId id() const;
    };


    class UserDescriptor
    {
    private:
        UserId id_;
        std::string login_;
        bool hasPriority_;

    public:
        UserDescriptor() = default;
        UserDescriptor(UserId id, const std::string& login, bool hasPriority);

        const std::string& login() const;
        bool hasPriority() const;
        UserId id() const;
    };


    class SmallPredicateDescriptor
    {
    private:
        PredicateId id_;
        std::unique_ptr<IPredicate> predicate_;

    public:
        SmallPredicateDescriptor() = default;
        SmallPredicateDescriptor(
                PredicateId id,
                std::unique_ptr<IPredicate>&& predicate
        );

        PredicateId id() const;
        const IPredicate& predicate() const;
    };


    class BigPredicateDescriptor
    {
    private:
        SmallPredicateDescriptor descriptor_;
        PolyVector<IRequirement> requirements_;

    public:
        BigPredicateDescriptor() = default;
        BigPredicateDescriptor(
                PredicateId id,
                std::unique_ptr<IPredicate>&& predicate,
                PolyVector<IRequirement>&& requirements
        );

        PredicateId id() const;
        const IPredicate& predicate() const;
        const PolyVector<IRequirement>& requirements() const;
        SmallPredicateDescriptor getSmallDescriptor() const;
    };


    class RequirementDescriptor
    {
    private:
        std::unique_ptr<IRequirement> requirement_;
        mutable size_t number_ = 1;

    public:
        RequirementDescriptor() = default;
        RequirementDescriptor(std::unique_ptr<IRequirement>&& requirement, size_t number = 1);

        const IRequirement& requirement() const;
        size_t numberOfUsages() const;
        void addUsage() const;
        void removeUsage() const;
    };
}


#endif //EQUEUE_V2_DESCRIPTORS_H
