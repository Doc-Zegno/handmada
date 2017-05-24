//
// Created by syzegno on 21.05.17.
//

#ifndef EQUEUE_V2_MESSAGE_H
#define EQUEUE_V2_MESSAGE_H


#include <string>
#include <ctime>


namespace Handmada {
    class Message
    {
    private:
        std::time_t when_;
        std::string from_;
        std::string theme_;
        std::string text_;

    public:
        Message() = default;
        Message(
                const std::time_t& when,
                const std::string& from,
                const std::string& theme,
                const std::string& text
        );

        const std::time_t& when() const;
        const std::string& from() const;
        const std::string& theme() const;
        const std::string& text() const;
    };
}


#endif //EQUEUE_V2_MESSAGE_H
