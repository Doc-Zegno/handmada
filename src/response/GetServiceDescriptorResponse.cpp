//
// Created by syzegno on 15.05.17.
//


#include "GetServiceDescriptorResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GetServiceDescriptorResponse::GetServiceDescriptorResponse(
            std::vector<ServiceDescriptor>&& descriptors
    ) : descriptors_(std::move(descriptors))
    { }


    OpCode GetServiceDescriptorResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void GetServiceDescriptorResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::vector<ServiceDescriptor>& GetServiceDescriptorResponse::descriptors() const
    {
        return descriptors_;
    }


    std::unique_ptr<IResponse> GetServiceDescriptorResponse::create(
            std::vector<ServiceDescriptor>&& descriptors
    )
    {
        return std::unique_ptr<IResponse>(
                new GetServiceDescriptorResponse(std::move(descriptors))
        );
    }

}

