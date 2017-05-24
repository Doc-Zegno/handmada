//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ATTACHSPECIALISTRESPONSE_H
#define EQUEUE_V2_ATTACHSPECIALISTRESPONSE_H


#include <memory>

#include "IResponse.h"
#include "Types.h"


namespace Handmada {
    class AttachSpecialistResponse : public IResponse
    {
    private:
        SpecialistId specialistId_;
        ServiceId serviceId_;

    public:
        AttachSpecialistResponse(SpecialistId specialistId, ServiceId serviceId);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        SpecialistId specialistId() const;
        ServiceId serviceId() const;
        static std::unique_ptr<IResponse> create(SpecialistId specialistId, ServiceId serviceId);
    };
}


#endif //EQUEUE_V2_ATTACHSPECIALISTRESPONSE_H
