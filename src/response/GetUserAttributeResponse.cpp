//
// Created by syzegno on 15.05.17.
//


#include "GetUserAttributeResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GetUserAttributeResponse::GetUserAttributeResponse(PolyVector<IAttribute>&& attributes)
            : attributes_(std::move(attributes))
    { }


    OpCode GetUserAttributeResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void GetUserAttributeResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const PolyVector<Handmada::IAttribute>& GetUserAttributeResponse::attributes() const
    {
        return attributes_;
    }


    std::unique_ptr<IResponse> GetUserAttributeResponse::create(
            PolyVector<IAttribute>&& attributes
    )
    {
        return std::unique_ptr<IResponse>(
                new GetUserAttributeResponse(std::move(attributes))
        );
    }
}
