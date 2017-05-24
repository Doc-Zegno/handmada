//
// Created by syzegno on 21.05.17.
//


#include "MakeAppointmentRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    MakeAppointmentRequest::MakeAppointmentRequest(UserId userId, ServiceId serviceId)
            : userId_(userId), serviceId_(serviceId)
    { }


    std::unique_ptr<IRequest> MakeAppointmentRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new MakeAppointmentRequest(userId_, serviceId_));
    }


    void MakeAppointmentRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId MakeAppointmentRequest::userId() const
    {
        return userId_;
    }


    ServiceId MakeAppointmentRequest::serviceId() const
    {
        return serviceId_;
    }
}


