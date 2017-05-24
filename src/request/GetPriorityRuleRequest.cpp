//
// Created by syzegno on 15.05.17.
//


#include "GetPriorityRuleRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    GetPriorityRuleRequest::GetPriorityRuleRequest(ServiceId serviceId)
            : serviceId_(serviceId)
    { }


    std::unique_ptr<IRequest> GetPriorityRuleRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new GetPriorityRuleRequest(serviceId_));
    }


    void GetPriorityRuleRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    ServiceId GetPriorityRuleRequest::serviceId() const
    {
        return serviceId_;
    }
}

