//
// Created by syzegno on 19.05.17.
//


#include "RegisterUserResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    RegisterUserResponse::RegisterUserResponse(UserId userId)
            : userId_(userId)
    { }


    OpCode RegisterUserResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void RegisterUserResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId RegisterUserResponse::userId() const
    {
        return userId_;
    }


    std::unique_ptr<IResponse> RegisterUserResponse::create(UserId userId)
    {
        return std::unique_ptr<IResponse>(new RegisterUserResponse(userId));
    }
}
