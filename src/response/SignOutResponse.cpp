//
// Created by syzegno on 19.05.17.
//


#include "SignOutResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    SignOutResponse::SignOutResponse(const std::string& login)
            : login_(login)
    { }


    OpCode SignOutResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void SignOutResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::string& SignOutResponse::login() const
    {
        return login_;
    }


    std::unique_ptr<IResponse> SignOutResponse::create(const std::string& login)
    {
        return std::unique_ptr<IResponse>(new SignOutResponse(login));
    }
}


