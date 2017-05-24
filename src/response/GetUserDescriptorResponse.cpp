//
// Created by syzegno on 15.05.17.
//


#include "GetUserDescriptorResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GetUserDescriptorResponse::GetUserDescriptorResponse(
            std::vector<UserDescriptor>&& descriptors
    ) : descriptors_(std::move(descriptors))
    { }


    OpCode GetUserDescriptorResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void GetUserDescriptorResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::vector<UserDescriptor>& GetUserDescriptorResponse::descriptors() const
    {
        return descriptors_;
    }


    std::unique_ptr<IResponse> GetUserDescriptorResponse::create(
            std::vector<UserDescriptor>&& descriptors
    )
    {
        return std::unique_ptr<IResponse>(
                new GetUserDescriptorResponse(std::move(descriptors))
        );
    }
}
