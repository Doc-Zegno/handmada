//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_REGISTERUSERREQUEST_H
#define EQUEUE_V2_REGISTERUSERREQUEST_H


#include <string>

#include "IRequest.h"


namespace Handmada {
    class RegisterUserRequest : public IRequest
    {
    private:
        std::string login_;

    public:
        RegisterUserRequest(const std::string& login);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        const std::string& login() const;
    };
}


#endif //EQUEUE_V2_REGISTERUSERREQUEST_H
