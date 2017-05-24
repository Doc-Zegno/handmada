//
// Created by syzegno on 19.05.17.
//


#include "SignInRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    // S i g n I n
    SignInRequest::SignInRequest(const std::string& login)
            : login_(login)
    { }


    const std::string& SignInRequest::login() const
    {
        return login_;
    }


    std::unique_ptr<IRequest> SignInRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new SignInRequest(login_));
    }


    void SignInRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }



    // S i g n O u t
    SignOutRequest::SignOutRequest(UserId userId) : userId_(userId)
    { }


    std::unique_ptr<IRequest> SignOutRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new SignOutRequest(userId_));
    }


    void SignOutRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId SignOutRequest::userId() const
    {
        return userId_;
    }
}
