//
// Created by syzegno on 18.05.17.
//


#include "Descriptors.h"


namespace Handmada {
    // S e r v i c e D e s c r i p t o r
    ServiceDescriptor::ServiceDescriptor(ServiceId id, const std::string& name, const std::string& description)
            : id_(id), name_(name), description_(description)
    { }


    const std::string& ServiceDescriptor::name() const
    {
        return name_;
    }


    const std::string& ServiceDescriptor::description() const
    {
        return description_;
    }


    ServiceId ServiceDescriptor::id() const
    {
        return id_;
    }



    // S p e c i a l i s t D e s c r i p t o r
    SpecialistDescriptor::SpecialistDescriptor(SpecialistId id, const std::string& name)
            : id_(id), name_(name)
    { }


    const std::string& SpecialistDescriptor::name() const
    {
        return name_;
    }


    SpecialistId SpecialistDescriptor::id() const
    {
        return id_;
    }



    // U s e r D e s c r i p t o r
    UserDescriptor::UserDescriptor(UserId id, const std::string& login, bool hasPriority)
            : id_(id), login_(login), hasPriority_(hasPriority)
    { }


    const std::string& UserDescriptor::login() const
    {
        return login_;
    }


    bool UserDescriptor::hasPriority() const
    {
        return hasPriority_;
    }


    UserId UserDescriptor::id() const
    {
        return id_;
    }



    // S m a l l P r e d i c a t e D e s c r i p t o r
    SmallPredicateDescriptor::SmallPredicateDescriptor(PredicateId id, std::unique_ptr<IPredicate>&& predicate)
            : id_(id), predicate_(std::move(predicate))
    { }


    PredicateId SmallPredicateDescriptor::id() const
    {
        return id_;
    }


    const IPredicate& SmallPredicateDescriptor::predicate() const
    {
        return *predicate_;
    }



    // B i g P r e d i c a t e D e s c r i p t o r
    BigPredicateDescriptor::BigPredicateDescriptor(
            PredicateId id,
            std::unique_ptr<IPredicate>&& predicate,
            PolyVector<IRequirement>&& requirements
    ) : descriptor_(id, std::move(predicate)), requirements_(std::move(requirements))
    { }


    PredicateId BigPredicateDescriptor::id() const
    {
        return descriptor_.id();
    }


    const IPredicate& BigPredicateDescriptor::predicate() const
    {
        return descriptor_.predicate();
    }


    const PolyVector<IRequirement>& BigPredicateDescriptor::requirements() const
    {
        return requirements_;
    }


    SmallPredicateDescriptor BigPredicateDescriptor::getSmallDescriptor() const
    {
        return SmallPredicateDescriptor(
                descriptor_.id(), descriptor_.predicate().clone()
        );
    }



    // R e q u i r e m e n t D e s c r i p t o r
    RequirementDescriptor::RequirementDescriptor(
            std::unique_ptr<IRequirement>&& requirement, size_t number
    ) : requirement_(std::move(requirement)), number_(number)
    { }


    const IRequirement& RequirementDescriptor::requirement() const
    {
        return *requirement_;
    }


    size_t RequirementDescriptor::numberOfUsages() const
    {
        return number_;
    }


    void RequirementDescriptor::addUsage() const
    {
        number_++;
    }


    void RequirementDescriptor::removeUsage() const
    {
        if (number_ == 0) {
            throw std::runtime_error("attempt to decrease number of usages of unused descriptor");
        }
        number_--;
    }
}
