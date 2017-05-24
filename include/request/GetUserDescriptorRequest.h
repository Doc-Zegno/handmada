//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETUSERDESCRIPTORREQUEST_H
#define EQUEUE_V2_GETUSERDESCRIPTORREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class GetUserDescriptorRequest : public IRequest
    {
    private:
        ServiceId serviceId_;

    public:
        GetUserDescriptorRequest(ServiceId serviceId);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        ServiceId serviceId() const;
    };
}


#endif //EQUEUE_V2_GETUSERDESCRIPTORREQUEST_H
