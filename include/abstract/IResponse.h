//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IRESPONSE_H
#define EQUEUE_V2_IRESPONSE_H


#include "OpCode.h"


namespace Handmada {
    class IResponseVisitor;

    /**
     * The counterpart of IRequest.
     * The frontend has to return an appropriate instance of IResponse
     * after request processing
     */
    class IResponse
    {
    public:
        virtual OpCode code() const = 0;
        virtual void accept(IResponseVisitor& visitor) const = 0;

        virtual ~IResponse() { }
    };
}


#endif //EQUEUE_V2_IRESPONSE_H
