//
// Created by syzegno on 19.05.17.
//


#include "SignInResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    SignInResponse::SignInResponse(UserId userId)
            : userId_(userId)
    { }


    OpCode SignInResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void SignInResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId SignInResponse::userId() const
    {
        return userId_;
    }


    std::unique_ptr<IResponse> SignInResponse::create(UserId userId)
    {
        return std::unique_ptr<IResponse>(new SignInResponse(userId));
    }
}
