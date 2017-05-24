//
// Created by syzegno on 14.05.17.
//


#include "AttachSpecialistResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    AttachSpecialistResponse::AttachSpecialistResponse(
            SpecialistId specialistId,
            ServiceId serviceId
    ) : specialistId_(specialistId), serviceId_(serviceId)
    { }


    OpCode AttachSpecialistResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void AttachSpecialistResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    SpecialistId AttachSpecialistResponse::specialistId() const
    {
        return specialistId_;
    }


    ServiceId AttachSpecialistResponse::serviceId() const
    {
        return serviceId_;
    }


    std::unique_ptr<IResponse> AttachSpecialistResponse::create(
            SpecialistId specialistId, ServiceId serviceId
    )
    {
        return std::unique_ptr<IResponse>(new AttachSpecialistResponse(specialistId, serviceId));
    }
}

