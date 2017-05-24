//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_SIGNINREQUEST_H
#define EQUEUE_V2_SIGNINREQUEST_H


#include <string>

#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class SignInRequest : public IRequest
    {
    private:
        std::string login_;

    public:
        SignInRequest(const std::string& login);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        const std::string& login() const;
    };


    class SignOutRequest : public IRequest
    {
    private:
        UserId userId_;

    public:
        SignOutRequest(UserId userId);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        UserId userId() const;
    };
}


#endif //EQUEUE_V2_SIGNINREQUEST_H
