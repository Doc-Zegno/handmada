//
// Created by syzegno on 15.05.17.
//


#include "Console.h"

#include <cstring>


namespace Handmada {
    Console::Console(std::istream& in, std::ostream& out, std::ostream& err)
            : in_(in), out_(out), err_(err)
    {
        out_.setf(std::ios::left);
        err_.setf(std::ios::left);
    }


    std::vector<std::string> Console::getArgs(const std::string& prompt)
    {
        const int MAX_PROMPT_LEN = 256;
        char promptBuf[MAX_PROMPT_LEN];

        while (true) {
            out_ << prompt << ":\\> ";
            in_.getline(promptBuf, MAX_PROMPT_LEN - 1);

            std::vector<std::string> args;
            char* token = strtok(promptBuf, " ");
            while (token) {
                args.push_back(std::string(token));
                token = strtok(nullptr, " ");
            }

            if (args.size() == 0) {
                err_ << "No arguments were passed to console. Try again\n";
                continue;
            }
            return std::move(args);
        }
    }


    void Console::out() const
    {
        put(out_, '\n');
    }


    void Console::err() const
    {
        put(err_, "<!>\n");
    }


    std::ostream& Console::outStream() const
    {
        return out_;
    }


    std::istream& Console::inStream() const
    {
        return in_;
    }
}
