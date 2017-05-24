//
// Created by syzegno on 14.05.17.
//


#include "GetServiceDescriptorRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    std::unique_ptr<IRequest> GetServiceDescriptorRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new GetServiceDescriptorRequest());
    }


    void GetServiceDescriptorRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }
}
