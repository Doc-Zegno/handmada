//
// Created by syzegno on 14.05.17.
//


#include "GetMessageRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    GetMessageRequest::GetMessageRequest(UserId userId) : userId_(userId)
    { }


    std::unique_ptr<IRequest> GetMessageRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new GetMessageRequest(userId_));
    }


    void GetMessageRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId GetMessageRequest::userId() const
    {
        return userId_;
    }
}

