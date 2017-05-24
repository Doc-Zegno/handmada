//
// Created by syzegno on 14.05.17.
//


#include "AttachSpecialistRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    AttachSpecialistRequest::AttachSpecialistRequest(
            SpecialistId specialistId,
            ServiceId serviceId
    ) : specialistId_(specialistId), serviceId_(serviceId)
    { }


    std::unique_ptr<IRequest> AttachSpecialistRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new AttachSpecialistRequest(
                specialistId_, serviceId_
        ));
    }


    void AttachSpecialistRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    SpecialistId AttachSpecialistRequest::specialistId() const
    {
        return specialistId_;
    }


    ServiceId AttachSpecialistRequest::serviceId() const
    {
        return serviceId_;
    }
}

