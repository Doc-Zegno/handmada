//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETUSERDESCRIPTORRESPONSE_H
#define EQUEUE_V2_GETUSERDESCRIPTORRESPONSE_H


#include <memory>
#include <vector>

#include "IResponse.h"
#include "Descriptors.h"


namespace Handmada {
    class GetUserDescriptorResponse : public IResponse
    {
    private:
        std::vector<UserDescriptor> descriptors_;

    public:
        GetUserDescriptorResponse(std::vector<UserDescriptor>&& descriptors);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::vector<UserDescriptor>& descriptors() const;
        static std::unique_ptr<IResponse> create(std::vector<UserDescriptor>&& descriptors);
    };
}


#endif //EQUEUE_V2_GETUSERDESCRIPTORRESPONSE_H
