//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETSPECIALISTDESCRIPTORRESPONSE_H
#define EQUEUE_V2_GETSPECIALISTDESCRIPTORRESPONSE_H


#include <memory>
#include <vector>

#include "IResponse.h"
#include "Descriptors.h"


namespace Handmada {
    class GetSpecialistDescriptorResponse : public IResponse
    {
    private:
        std::vector<SpecialistDescriptor> descriptors_;

    public:
        GetSpecialistDescriptorResponse(std::vector<SpecialistDescriptor>&& descriptors);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::vector<SpecialistDescriptor>& descriptors() const;
        static std::unique_ptr<IResponse> create(
                std::vector<SpecialistDescriptor>&& descriptors
        );
    };
}


#endif //EQUEUE_V2_GETSPECIALISTDESCRIPTORRESPONSE_H
