//
// Created by syzegno on 13.05.17.
//

#ifndef EQUEUE_V2_ISYSTEM_H
#define EQUEUE_V2_ISYSTEM_H


#include <memory>

#include "IResponse.h"
#include "IRequest.h"


namespace Handmada {
    /**
     * Frontend is the core of the system.
     * There are two different concepts of frontend:
     * 1. Main frontend (instance of BasicFrontend) that relies on underlying data base
     * 2. Proxy frontend which is aimed to redirect requests from remote machines to
     * the main frontend
     */
    class IFrontend
    {
    public:
        virtual std::unique_ptr<IResponse> acceptRequest(const IRequest& request) = 0;

        virtual ~IFrontend() { }
    };
}


#endif //EQUEUE_V2_ISYSTEM_H
