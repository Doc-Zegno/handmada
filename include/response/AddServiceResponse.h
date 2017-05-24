//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDSERVICERESPONSE_H
#define EQUEUE_V2_ADDSERVICERESPONSE_H


#include <memory>

#include "IResponse.h"
#include "Types.h"


namespace Handmada {
    class AddServiceResponse : public IResponse
    {
    private:
        ServiceId serviceId_;

    public:
        AddServiceResponse(ServiceId serviceId);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        ServiceId serviceId() const;
        static std::unique_ptr<IResponse> create(ServiceId serviceId);
    };
}


#endif //EQUEUE_V2_ADDSERVICERESPONSE_H
