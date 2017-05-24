//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDPRIORITYRULEREQUEST_H
#define EQUEUE_V2_ADDPRIORITYRULEREQUEST_H


#include "IRequest.h"
#include "IPredicate.h"
#include "IRequirement.h"
#include "PolyVector.h"
#include "Types.h"


namespace Handmada {
    class AddPriorityRuleRequest : public IRequest
    {
    private:
        ServiceId serviceId_;
        std::unique_ptr<IPredicate> predicate_;
        PolyVector<IRequirement> requirements_;

    public:
        AddPriorityRuleRequest(
                ServiceId serviceId,
                decltype(predicate_)&& predicate,
                decltype(requirements_)&& requirements
        );

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        ServiceId serviceId() const;
        const IPredicate& predicate() const;
        const PolyVector<IRequirement>& requirements() const;
    };
}


#endif //EQUEUE_V2_ADDPRIORITYRULEREQUEST_H
