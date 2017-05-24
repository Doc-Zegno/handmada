//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_REGISTERUSERRESPONSE_H
#define EQUEUE_V2_REGISTERUSERRESPONSE_H


#include <memory>

#include "IResponse.h"
#include "Types.h"


namespace Handmada {
    class RegisterUserResponse : public IResponse
    {
    private:
        UserId userId_;

    public:
        RegisterUserResponse(UserId userId);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        UserId userId() const;
        static std::unique_ptr<IResponse> create(UserId userId);
    };
}


#endif //EQUEUE_V2_REGISTERUSERRESPONSE_H
