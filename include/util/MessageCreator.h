//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_MESSAGEMAKER_H
#define EQUEUE_V2_MESSAGEMAKER_H


#include <vector>

#include "Message.h"


namespace Handmada {
    class MessageCreator
    {
    private:
        static std::vector<std::string> hello_;
        static std::vector<std::string> texts_;
        static std::vector<std::string> endings_;

    public:
        static Message create(
                const std::time_t& when,
                const std::string& from,
                const std::string& to,
                const std::string& theme
        );
    };
}


#endif //EQUEUE_V2_MESSAGEMAKER_H
