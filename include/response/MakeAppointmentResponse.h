//
// Created by syzegno on 21.05.17.
//

#ifndef EQUEUE_V2_MAKEAPPOINTMENTRESPONSE_H
#define EQUEUE_V2_MAKEAPPOINTMENTRESPONSE_H


#include <memory>

#include "IResponse.h"
#include "Types.h"


namespace Handmada {
    class MakeAppointmentResponse : public IResponse
    {
    private:
        UserId userId_;
        ServiceId serviceId_;
        /**
         * This field doesn't violate the principle of response symmetry:
         * "Each response should contain information enough to perform undo-request"
         * But it is redundant and left here only to provide UI with extra information
         */
        bool hasPriority_;

    public:
        MakeAppointmentResponse(UserId userId, ServiceId serviceId, bool hasPriority);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        UserId userId() const;
        ServiceId serviceId() const;
        bool hasPriority() const;
        static std::unique_ptr<IResponse> create(
                UserId userId,
                ServiceId serviceId,
                bool hasPriority
        );
    };
}


#endif //EQUEUE_V2_MAKEAPPOINTMENTRESPONSE_H
