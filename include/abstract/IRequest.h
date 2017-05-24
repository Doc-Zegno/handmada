//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IREQUEST_H
#define EQUEUE_V2_IREQUEST_H


#include <memory>


namespace Handmada {
    class IRequestVisitor;


    /**
     * The main interface in the request-driven system.
     * Encapsulates arguments that should be passed to frontend calls.
     *
     * Each implementation of frontend is free to choose the way of processing
     * received requests. For example, it can retrieve required information
     * from underlying data base. One more option is to redirect received request
     * to another frontend, possibly over the network.
     *
     * The client-side class should assume that the request is idempotent,
     * i.e. the internal state of frontend must not change during
     * request processing if the same type of request is accepted twice
     * (the only possible exception is made for proxy frontend that
     * transfer request over the network)
     */
    class IRequest
    {
    public:
        virtual std::unique_ptr<IRequest> clone() const = 0;
        virtual void accept(IRequestVisitor& visitor) const = 0;

        virtual ~IRequest() { }
    };
}


#endif //EQUEUE_V2_IREQUEST_H
