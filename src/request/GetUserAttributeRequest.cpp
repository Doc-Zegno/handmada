//
// Created by syzegno on 14.05.17.
//


#include "GetUserAttributeRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    GetUserAttributeRequest::GetUserAttributeRequest(UserId userId)
            : userId_(userId)
    { }


    std::unique_ptr<IRequest> GetUserAttributeRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new GetUserAttributeRequest(userId_));
    }


    void GetUserAttributeRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId GetUserAttributeRequest::userId() const
    {
        return userId_;
    }
}


