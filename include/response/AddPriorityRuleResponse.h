//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDPRIORITYRULERESPONSE_H
#define EQUEUE_V2_ADDPRIORITYRULERESPONSE_H


#include <memory>

#include "IResponse.h"
#include "Types.h"


namespace Handmada {
    class AddPriorityRuleResponse : public IResponse
    {
    private:
        ServiceId serviceId_;
        PredicateId predicateId_;

    public:
        AddPriorityRuleResponse(ServiceId serviceId, PredicateId predicateId);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        ServiceId serviceId() const;
        PredicateId predicateId() const;
        static std::unique_ptr<IResponse> create(ServiceId serviceId, PredicateId predicateId);
    };
}


#endif //EQUEUE_V2_ADDPRIORITYRULERESPONSE_H
