//
// Created by syzegno on 24.04.17.
//

#ifndef EQUEUE_V2_SPECIALIST_H
#define EQUEUE_V2_SPECIALIST_H


#include <string>

#include "../misc/Types.h"

namespace Handmada {
    class Specialist
    {
    private:
        friend class Service;

        std::string name_;
        bool busy_;
        UserId currentUserId_;
        ServiceId currentServiceId_;


    public:
        Specialist() = default;
        Specialist(
                const std::string& name,
                bool busy = false,
                UserId currentUserId = INVALID_USER_ID,
                ServiceId currentServiceId = INVALID_SERVICE_ID
        ) : name_(name), busy_(busy), currentUserId_(currentUserId),
            currentServiceId_(currentServiceId) { }

        const std::string& name() const { return name_; }
        bool isBusy() const { return busy_; }
        UserId currentUserId() const { return currentUserId_; }
        ServiceId currentServiceId() const { return currentServiceId_; }
    };
}


#endif //EQUEUE_V2_SPECIALIST_H
