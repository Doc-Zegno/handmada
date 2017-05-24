//
// Created by syzegno on 14.05.17.
//


#include "GetSpecialistDescriptorRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    GetSpecialistDescriptorRequest::GetSpecialistDescriptorRequest(ServiceId serviceId)
            : serviceId_(serviceId)
    { }


    std::unique_ptr<IRequest> GetSpecialistDescriptorRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new GetSpecialistDescriptorRequest(serviceId_));
    }


    void GetSpecialistDescriptorRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    ServiceId GetSpecialistDescriptorRequest::serviceId() const
    {
        return serviceId_;
    }
}

