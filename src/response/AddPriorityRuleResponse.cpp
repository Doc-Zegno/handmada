//
// Created by syzegno on 14.05.17.
//


#include "AddPriorityRuleResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    AddPriorityRuleResponse::AddPriorityRuleResponse(ServiceId serviceId, PredicateId predicateId)
            : serviceId_(serviceId), predicateId_(predicateId)
    { }


    OpCode AddPriorityRuleResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void AddPriorityRuleResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    ServiceId AddPriorityRuleResponse::serviceId() const
    {
        return serviceId_;
    }


    PredicateId AddPriorityRuleResponse::predicateId() const
    {
        return predicateId_;
    }


    std::unique_ptr<IResponse> AddPriorityRuleResponse::create(ServiceId serviceId, PredicateId predicateId)
    {
        return std::unique_ptr<IResponse>(new AddPriorityRuleResponse(serviceId, predicateId));
    }
}
