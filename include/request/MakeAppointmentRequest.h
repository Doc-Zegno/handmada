//
// Created by syzegno on 21.05.17.
//

#ifndef EQUEUE_V2_MAKEAPPOINMENTREQUEST_H
#define EQUEUE_V2_MAKEAPPOINMENTREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class MakeAppointmentRequest : public IRequest
    {
    private:
        UserId userId_;
        ServiceId serviceId_;

    public:
        MakeAppointmentRequest(UserId userId, ServiceId serviceId);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        UserId userId() const;
        ServiceId serviceId() const;
    };
}


#endif //EQUEUE_V2_MAKEAPPOINMENTREQUEST_H
