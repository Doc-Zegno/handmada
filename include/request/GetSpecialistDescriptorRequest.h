//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_GETSPECIALISTDESCRIPTORREQUEST_H
#define EQUEUE_V2_GETSPECIALISTDESCRIPTORREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class GetSpecialistDescriptorRequest : public IRequest
    {
    private:
        ServiceId serviceId_;

    public:
        GetSpecialistDescriptorRequest(ServiceId serviceId = INVALID_SERVICE_ID);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        ServiceId serviceId() const;
    };
}


#endif //EQUEUE_V2_GETSPECIALISTDESCRIPTORREQUEST_H
