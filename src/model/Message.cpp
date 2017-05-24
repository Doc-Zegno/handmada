//
// Created by syzegno on 21.05.17.
//


#include "Message.h"


namespace Handmada {
    Message::Message(
            const std::time_t& when,
            const std::string& from,
            const std::string& theme,
            const std::string& text
    ) : when_(when), from_(from), theme_(theme), text_(text)
    { }


    const std::time_t& Message::when() const
    {
        return when_;
    }


    const std::string& Message::from() const
    {
        return from_;
    }


    const std::string& Message::theme() const
    {
        return theme_;
    }


    const std::string& Message::text() const
    {
        return text_;
    }
}
