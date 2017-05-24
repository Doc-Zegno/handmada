//
// Created by syzegno on 14.05.17.
//


#include "AddUserAttributeResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    // A d d A t t r i b u t e
    AddUserAttributeResponse::AddUserAttributeResponse(
            UserId userId,
            std::vector<std::string>&& attributes
    ) : userId_(userId), attributes_(std::move(attributes))
    { }


    OpCode AddUserAttributeResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void AddUserAttributeResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::vector<std::string>& AddUserAttributeResponse::attributes() const
    {
        return attributes_;
    }


    std::unique_ptr<IResponse> AddUserAttributeResponse::create(
            UserId userId,
            std::vector<std::string>&& attributes
    )
    {
        return std::unique_ptr<IResponse>(
                new AddUserAttributeResponse(userId, std::move(attributes))
        );
    }


    UserId AddUserAttributeResponse::userId() const
    {
        return userId_;
    }



    // R e m o v e A t t r i b u t e
    RemoveUserAttributeResponse::RemoveUserAttributeResponse(
            UserId userId,
            PolyVector<IAttribute>&& attributes
    ) : userId_(userId), attributes_(std::move(attributes))
    { }


    OpCode RemoveUserAttributeResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void RemoveUserAttributeResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const PolyVector<Handmada::IAttribute>& RemoveUserAttributeResponse::attributes() const
    {
        return attributes_;
    }


    std::unique_ptr<IResponse> RemoveUserAttributeResponse::create(
            UserId userId,
            PolyVector<IAttribute>&& attributes
    )
    {
        return std::unique_ptr<IResponse>(
                new RemoveUserAttributeResponse(userId, std::move(attributes))
        );
    }


    UserId RemoveUserAttributeResponse::userId() const
    {
        return userId_;
    }
}
