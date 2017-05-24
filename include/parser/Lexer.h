//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_LEXER_H
#define EQUEUE_V2_LEXER_H


#include <iostream>
#include <string>
#include <stdexcept>

#include "BooleanLiteral.h"
#include "ComparisonFlag.h"
#include "Lexeme.h"


namespace Handmada {
    class UnexpectedCharacterException : public std::exception
    {
    private:
        std::string info_;

    public:
        UnexpectedCharacterException(
                int ch,
                int charNo,
                int endOfSequence,
                const std::string& additionalInfo
        );

        virtual const char* what() const noexcept override;
    };


    class ForbiddenIdentifierException : public std::runtime_error
    {
    public:
        ForbiddenIdentifierException(const std::string& info);
    };


    class Lexer
    {
    private:
        enum class State {
            START,
            IDENTIFIER,
            STRING_LITERAL,
            NUMBER_LITERAL_INTEGER_PART,
            NUMBER_LITERAL_RATIO_PART,
        };

        enum {
            BUF_SIZE = 256,
        };

        int ch_;
        int charNo_ = 0;
        int endOfSequence_ = EOF;

        char buffer_[BUF_SIZE];
        int top_ = 0;

        double number_;
        double multiplier_;
        double sign_;

        bool boolean_;

        ComparisonFlag::Type compareFlag_;

        State state_ = State::START;
        std::istream* input_;

        void crash(const std::string& additional = "no details available");
        void getNext();
        void getDoubleLex(char expected);
        Lexeme::Type checkForKeyword();

    public:
        void swallow() const;
        void reset(std::istream& input, int endOfSequence);
        std::string getString() const;
        double getNumber() const;
        bool getBoolean() const;
        ComparisonFlag::Type getCompareFlag() const;

        Lexeme::Type getLex();
    };
}


#endif //EQUEUE_V2_LEXER_H
