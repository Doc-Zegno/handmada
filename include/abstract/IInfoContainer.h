//
// Created by syzegno on 03.05.17.
//

#ifndef EQUEUE_V2_IINFOCONTAINER_H
#define EQUEUE_V2_IINFOCONTAINER_H


#include "Specialist.h"


namespace Handmada {
    /**
     * The special interface which is used only by BasicFrontend to interact with its services.
     * This interface is aimed to hide the underlying info container from services
     */
    class IInfoContainer
    {
    public:
        virtual void addInfo(UserId userId, ServiceId serviceId, Specialist* specialist) = 0;
    };
}


#endif //EQUEUE_V2_IINFOCONTAINER_H
