//
// Created by syzegno on 14.05.17.
//


#include "AddUserAttributeRequest.h"
#include "IRequestVisitor.h"
#include "SnapShooter.h"


namespace Handmada {
    // A d d A t t r i b u t e
    AddUserAttributeRequest::AddUserAttributeRequest(
            UserId userId,
            PolyVector<IAttribute>&& attributes
    ) : userId_(userId), attributes_(std::move(attributes))
    { }


    std::unique_ptr<IRequest> AddUserAttributeRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new AddUserAttributeRequest(
                userId_, SnapShooter::copy(attributes_)
        ));
    }


    void AddUserAttributeRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId AddUserAttributeRequest::userId() const
    {
        return userId_;
    }


    const PolyVector<IAttribute>& AddUserAttributeRequest::attributes() const
    {
        return attributes_;
    }



    // R e m o v e A t t r i b u t e
    RemoveUserAttributeRequest::RemoveUserAttributeRequest(
            UserId userId,
            std::vector<std::string>&& attributes
    ) : userId_(userId), attributes_(std::move(attributes))
    { }


    std::unique_ptr<IRequest> RemoveUserAttributeRequest::clone() const
    {
        auto copy = attributes_;
        return std::unique_ptr<IRequest>(
                new RemoveUserAttributeRequest(userId_, std::move(copy))
        );
    }


    void RemoveUserAttributeRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId RemoveUserAttributeRequest::userId() const
    {
        return userId_;
    }


    const std::vector<std::string>& RemoveUserAttributeRequest::attributes() const
    {
        return attributes_;
    }
}
