//
// Created by syzegno on 21.05.17.
//


#include "MissingAttributeResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    MissingAttributeResponse::MissingAttributeResponse(PolyVector<IRequirement>&& requirements)
            : requirements_(std::move(requirements))
    { }


    OpCode MissingAttributeResponse::code() const
    {
        return OpCode::MISSING_ATTRIBUTES;
    }


    void MissingAttributeResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const PolyVector<IRequirement>& MissingAttributeResponse::requirements() const
    {
        return requirements_;
    }


    std::unique_ptr<IResponse> MissingAttributeResponse::create(PolyVector<IRequirement>&& requirements)
    {
        return std::unique_ptr<IResponse>(new MissingAttributeResponse(std::move(requirements)));
    }
}
