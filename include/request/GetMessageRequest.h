//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_GETMESSAGEREQUEST_H
#define EQUEUE_V2_GETMESSAGEREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class GetMessageRequest : public IRequest
    {
    private:
        UserId userId_;

    public:
        GetMessageRequest(UserId userId);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        UserId userId() const;
    };
}


#endif //EQUEUE_V2_GETMESSAGEREQUEST_H
