//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETPRIORITYRULERESPONSE_H
#define EQUEUE_V2_GETPRIORITYRULERESPONSE_H


#include "IResponse.h"
#include "Descriptors.h"


namespace Handmada {
    class GetPriorityRuleResponse : public IResponse
    {
    private:
        std::vector<SmallPredicateDescriptor> descriptors_;

    public:
        GetPriorityRuleResponse(decltype(descriptors_)&& descriptor);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::vector<SmallPredicateDescriptor>& descriptors() const;
        static std::unique_ptr<IResponse> create(decltype(descriptors_)&& descriptors);
    };
}


#endif //EQUEUE_V2_GETPRIORITYRULERESPONSE_H
