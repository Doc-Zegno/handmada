//
// Created by syzegno on 15.05.17.
//


#include "GetUserDescriptorRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    GetUserDescriptorRequest::GetUserDescriptorRequest(ServiceId serviceId)
            : serviceId_(serviceId)
    { }


    std::unique_ptr<IRequest> GetUserDescriptorRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new GetUserDescriptorRequest(serviceId_));
    }


    void GetUserDescriptorRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    ServiceId GetUserDescriptorRequest::serviceId() const
    {
        return serviceId_;
    }
}
