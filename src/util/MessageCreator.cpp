//
// Created by syzegno on 15.05.17.
//


#include "MessageCreator.h"


namespace Handmada {
    std::vector<std::string> MessageCreator::hello_ = {
            "Hi, ",
            "Hello there, Mr ",
            "Hello, ",
    };
    std::vector<std::string> MessageCreator::texts_ = {
            "It wasn't easy at all but, fortunately, we did it.\nYou were fantastic!",
            "Wow! It was the most interesting case ever! I hope you enjoyed it too.",
            "Now that you become familiar with our service you can be sure that it is the best one.",
            "Nice to work with you! Remember that with our services it's easy to get the best solution."
                " Don't forget that you can also buy a $5 DLC to get the SUPERSOLUTION.",
            "That was much easier than tuning a makefile, huh? :D"
    };
    std::vector<std::string> MessageCreator::endings_ = {
            "Yours, ",
            "Best wishes, ",
            "Sincerely, ",
            "Have a nice day, ",
    };

    Message MessageCreator::create(
            const std::time_t& when,
            const std::string& from,
            const std::string& to,
            const std::string& theme
    )
    {
        auto hello = rand() % hello_.size();
        auto text = rand() % texts_.size();
        auto ending = rand() % endings_.size();

        std::string buf = hello_[hello];
        buf += to;
        buf += "!\n";
        buf += texts_[text];
        buf += "\n\t";
        buf += endings_[ending];
        buf += from;
        return Message(when, from, theme, buf);
    }
}
