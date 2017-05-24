//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETSERVICEDESCRIPTORRESPONSE_H
#define EQUEUE_V2_GETSERVICEDESCRIPTORRESPONSE_H


#include <vector>
#include <memory>

#include "IResponse.h"
#include "Descriptors.h"


namespace Handmada {
    class GetServiceDescriptorResponse : public IResponse
    {
    private:
        std::vector<ServiceDescriptor> descriptors_;

    public:
        GetServiceDescriptorResponse(std::vector<ServiceDescriptor>&& descriptors);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::vector<ServiceDescriptor>& descriptors() const;
        static std::unique_ptr<IResponse> create(std::vector<ServiceDescriptor>&& descriptors);
    };
}


#endif //EQUEUE_V2_GETSERVICEDESCRIPTORRESPONSE_H
