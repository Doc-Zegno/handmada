//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_GETUSERATTRIBUTEREQUEST_H
#define EQUEUE_V2_GETUSERATTRIBUTEREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class GetUserAttributeRequest : public IRequest
    {
    private:
        UserId userId_;

    public:
        GetUserAttributeRequest(UserId userId);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        UserId userId() const;
    };
}


#endif //EQUEUE_V2_GETUSERATTRIBUTEREQUEST_H
