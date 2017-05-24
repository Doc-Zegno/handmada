//
// Created by syzegno on 14.05.17.
//


#include "AddPriorityRuleRequest.h"
#include "IRequestVisitor.h"
#include "SnapShooter.h"


namespace Handmada {
    AddPriorityRuleRequest::AddPriorityRuleRequest(
            ServiceId serviceId,
            decltype(predicate_)&& predicate,
            decltype(requirements_)&& requirements
    ) : serviceId_(serviceId), predicate_(std::move(predicate)),
        requirements_(std::move(requirements))
    { }


    std::unique_ptr<IRequest> AddPriorityRuleRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new AddPriorityRuleRequest(
                serviceId_, predicate_->clone(), SnapShooter::copy(requirements_)
        ));
    }


    void AddPriorityRuleRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const IPredicate& AddPriorityRuleRequest::predicate() const
    {
        return *predicate_;
    }


    const PolyVector<IRequirement>& AddPriorityRuleRequest::requirements() const
    {
        return requirements_;
    }


    ServiceId AddPriorityRuleRequest::serviceId() const
    {
        return serviceId_;
    }
}


