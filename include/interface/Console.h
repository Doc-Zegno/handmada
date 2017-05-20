//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_CONSOLE_H
#define EQUEUE_V2_CONSOLE_H


#include <iostream>
#include <vector>
#include <string>
#include <climits>

#include "WidthLiteral.h"


namespace Handmada {
    /**
     * Provides a kit of methods of interacting with underlying input/output streams.
     * The methods can be used to transparently handle possible input/output errors
     */
    class Console
    {
    private:
        std::istream& in_;
        std::ostream& out_;
        std::ostream& err_;

        template<typename T>
        void put(std::ostream& out, const T& t) const;

        template<typename T, typename ...TArgs>
        void put(std::ostream& out, const T& t, const TArgs& ...args) const;

        template<typename T>
        void put(std::ostream& out, const Literal::WidthLiteral& width, const T& t) const;

        template<typename T, typename ...TArgs>
        void put(
                std::ostream& out,
                const Literal::WidthLiteral& width,
                const T& t,
                const TArgs& ...args
        ) const;

    public:
        Console(std::istream& in, std::ostream& out, std::ostream& err);

        std::ostream& outStream() const;
        std::istream& inStream() const;

        template<typename T>
        void get(T& t) const;

        template<typename T>
        void input(const std::string& prompt, T& t) const;

        void out() const;
        template<typename ...TArgs>
        void out(const TArgs& ...args) const;
        template<typename ...TArgs>
        void err(const TArgs& ...args) const;

        void err() const;
        template<typename ...TArgs>
        void outNoLine(const TArgs& ...args) const;
        template<typename ...TArgs>
        void errNoLine(const TArgs& ...args) const;

        std::vector<std::string> getArgs(const std::string& prompt);
    };


    template<typename T>
    void Console::get(T& t) const
    {
        while (true) {
            in_ >> t;
            if (in_) {
                in_.ignore(INT_MAX, '\n');
                break;
            } else {
                in_.clear();
                in_.ignore(INT_MAX, '\n');
                err_ << "Incorrect input! Try again\n";
            }
        }
    }


    template<> inline void Console::get(std::string& str) const
    {
        std::getline(in_, str);
    }


    template<typename T>
    void Console::input(const std::string& prompt, T& t) const
    {
        out_ << prompt;
        get(t);
    }


    template<typename ...TArgs>
    void Console::out(const TArgs& ...args) const
    {
        put(out_, args..., '\n');
    }


    template<typename ...TArgs>
    void Console::err(const TArgs& ...args) const
    {
        put(err_, "<!> ", args..., '\n');
    }


    template<typename ...TArgs>
    void Console::outNoLine(const TArgs& ...args) const
    {
        put(out_, args...);
    }


    template<typename ...TArgs>
    void Console::errNoLine(const TArgs& ...args) const
    {
        put(err_, "<!> ", args...);
    }


    template<typename T>
    void Console::put(std::ostream& out, const T& t) const
    {
        out << t;
    }


    template<typename T, typename ...TArgs>
    void Console::put(std::ostream& out, const T& t, const TArgs& ...args) const
    {
        out << t;
        put(out, args...);
    }


    template<typename T>
    void Console::put(std::ostream& out, const Literal::WidthLiteral& width, const T& t) const
    {
        out.width(width.width());
        out << t;
    }


    template<typename T, typename ...TArgs>
    void Console::put(
            std::ostream& out,
            const Literal::WidthLiteral& width,
            const T& t,
            const TArgs& ... args
    ) const
    {
        out.width(width.width());
        out << t;
        put(out, args...);
    }
}


#endif //EQUEUE_V2_CONSOLE_H
