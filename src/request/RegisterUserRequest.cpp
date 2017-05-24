//
// Created by syzegno on 19.05.17.
//


#include "RegisterUserRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    RegisterUserRequest::RegisterUserRequest(const std::string& login)
            : login_(login)
    { }


    std::unique_ptr<IRequest> RegisterUserRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new RegisterUserRequest(login_));
    }


    void RegisterUserRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::string& RegisterUserRequest::login() const
    {
        return login_;
    }
}
