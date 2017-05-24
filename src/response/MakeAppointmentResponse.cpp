//
// Created by syzegno on 21.05.17.
//


#include "MakeAppointmentResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    MakeAppointmentResponse::MakeAppointmentResponse(
            UserId userId,
            ServiceId serviceId, bool hasPriority
    ) : userId_(userId), serviceId_(serviceId), hasPriority_(hasPriority)
    { }


    OpCode MakeAppointmentResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void MakeAppointmentResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    UserId MakeAppointmentResponse::userId() const
    {
        return userId_;
    }


    ServiceId MakeAppointmentResponse::serviceId() const
    {
        return serviceId_;
    }


    bool MakeAppointmentResponse::hasPriority() const
    {
        return hasPriority_;
    }


    std::unique_ptr<IResponse> MakeAppointmentResponse::create(
            UserId userId,
            ServiceId serviceId,
            bool hasPriority
    )
    {
        return std::unique_ptr<IResponse>(new MakeAppointmentResponse(
                userId, serviceId, hasPriority
        ));
    }
}
