//
// Created by syzegno on 15.05.17.
//


#include "GetSpecialistDescriptorResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GetSpecialistDescriptorResponse::GetSpecialistDescriptorResponse(
            std::vector<SpecialistDescriptor>&& descriptors
    ) : descriptors_(std::move(descriptors))
    { }


    OpCode GetSpecialistDescriptorResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void GetSpecialistDescriptorResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::vector<SpecialistDescriptor>& GetSpecialistDescriptorResponse::descriptors() const
    {
        return descriptors_;
    }


    std::unique_ptr<IResponse> GetSpecialistDescriptorResponse::create(
            std::vector<SpecialistDescriptor>&& descriptors
    )
    {
        return std::unique_ptr<IResponse>(
                new GetSpecialistDescriptorResponse(std::move(descriptors))
        );
    }
}
