//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ATTACHSPECIALISTREQUEST_H
#define EQUEUE_V2_ATTACHSPECIALISTREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class AttachSpecialistRequest : public IRequest
    {
    private:
        SpecialistId specialistId_;
        ServiceId serviceId_;

    public:
        AttachSpecialistRequest(SpecialistId specialistId, ServiceId serviceId);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        SpecialistId specialistId() const;
        ServiceId serviceId() const;
    };
}


#endif //EQUEUE_V2_ATTACHSPECIALISTREQUEST_H
