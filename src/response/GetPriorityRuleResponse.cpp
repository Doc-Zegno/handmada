//
// Created by syzegno on 15.05.17.
//


#include "GetPriorityRuleResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GetPriorityRuleResponse::GetPriorityRuleResponse(
            std::vector<SmallPredicateDescriptor>&& descriptor
    ) : descriptors_(std::move(descriptor))
    { }


    OpCode GetPriorityRuleResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void GetPriorityRuleResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::vector<SmallPredicateDescriptor>& GetPriorityRuleResponse::descriptors() const
    {
        return descriptors_;
    }


    std::unique_ptr<IResponse> GetPriorityRuleResponse::create(
            std::vector<SmallPredicateDescriptor>&& descriptors
    )
    {
        return std::unique_ptr<IResponse>(new GetPriorityRuleResponse(std::move(descriptors)));
    }
}


