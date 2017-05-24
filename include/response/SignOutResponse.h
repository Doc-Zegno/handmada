//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_SIGNOUTRESPONSE_H
#define EQUEUE_V2_SIGNOUTRESPONSE_H


#include <memory>
#include <string>

#include "IResponse.h"


namespace Handmada {
    class SignOutResponse : public IResponse
    {
    private:
        std::string login_;

    public:
        SignOutResponse(const std::string& login);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::string& login() const;
        static std::unique_ptr<IResponse> create(const std::string& login);
    };
}


#endif //EQUEUE_V2_SIGNOUTRESPONSE_H
