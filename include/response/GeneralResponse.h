//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_GENERALFAILURERESPONSE_H
#define EQUEUE_V2_GENERALFAILURERESPONSE_H


#include <memory>

#include "IResponse.h"


namespace Handmada {
    class GeneralResponse : public IResponse
    {
    private:
        OpCode code_;

    public:
        GeneralResponse(OpCode code);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        static std::unique_ptr<IResponse> create(OpCode code);
    };
}


#endif //EQUEUE_V2_GENERALFAILURERESPONSE_H
