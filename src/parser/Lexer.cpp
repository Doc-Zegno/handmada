//
// Created by syzegno on 07.05.17.
//


#include "Lexer.h"

#include <cstring>
#include <sstream>


namespace Handmada {
    // E x c e p t i o n
    UnexpectedCharacterException::UnexpectedCharacterException(
            int ch,
            int charNo,
            int endOfSequence,
            const std::string& additionalInfo
    )
    {
        std::ostringstream sout;
        sout << "Lexical error: unexpected character in column #" << charNo << ": ";
        if (ch == endOfSequence) {
            sout << "<end of sequence>";
        } else if (std::isspace(ch)) {
            sout << "<white space>";
        } else {
            sout << static_cast<char>(ch);
        }
        sout << "\n\t";
        sout << additionalInfo;
        info_ = sout.str();
    }


    const char* UnexpectedCharacterException::what() const noexcept
    {
        return info_.c_str();
    }



    ForbiddenIdentifierException::ForbiddenIdentifierException(const std::string& info)
            : runtime_error(info)
    { }



    // L e x e r
    void Lexer::reset(std::istream& input, int endOfSequence)
    {
        endOfSequence_ = endOfSequence;

        charNo_ = 0;
        top_ = 0;
        state_ = State::START;

        boolean_ = false;
        number_ = 0.0;
        sign_ = 1.0;
        buffer_[0] = '\0';

        input_ = &input;
        getNext();
    }


    void Lexer::swallow() const
    {
        if (ch_ != endOfSequence_) {
            int ch;
            do {
                ch = input_->get();
            } while (ch != endOfSequence_);
        }
    }


    Lexeme::Type Lexer::getLex()
    {
        while (true) {
            switch (state_) {
                // S T A R T
            case State::START:
                if (ch_ == endOfSequence_) {
                    return Lexeme::END_OF_SEQUENCE;
                }

                while (std::isspace(ch_)) {
                    getNext();
                }

                if (std::isalpha(ch_)) {
                    if (std::islower(ch_)) {
                        state_ = State::IDENTIFIER;
                        top_ = 0;
                        continue;
                    } else {
                        crash("identifier must be started with lowercase character");
                    }
                }

                if (std::isdigit(ch_)) {
                    state_ = State::NUMBER_LITERAL_INTEGER_PART;
                    number_ = 0.0;
                    sign_ = 1.0;
                    top_ = 0;
                    continue;
                }

                switch (ch_) {
                case '\"':
                    getNext();
                    state_ = State::STRING_LITERAL;
                    top_ = 0;
                    continue;
                case '(':
                    getNext();
                    return Lexeme::OPEN_PARENTHESIS;
                case ')':
                    getNext();
                    return Lexeme::CLOSE_PARENTHESIS;
                case '&':
                    getDoubleLex('&');
                    return Lexeme::AND;
                case '|':
                    getDoubleLex('|');
                    return Lexeme::OR;
                case '!':
                    getNext();
                    if (ch_ == '=') {
                        getNext();
                        compareFlag_ = ComparisonFlag::NOT_EQUAL;
                        return Lexeme::RELATIONAL;
                    } else {
                        return Lexeme::NOT;
                    }
                case '>':
                    getNext();
                    if (ch_ == '=') {
                        getNext();
                        compareFlag_ = ComparisonFlag::GREATER_OR_EQUAL;
                        return Lexeme::RELATIONAL;
                    } else {
                        compareFlag_ = ComparisonFlag::GREATER;
                        return Lexeme::RELATIONAL;
                    }
                case '<':
                    getNext();
                    if (ch_ == '=') {
                        getNext();
                        compareFlag_ = ComparisonFlag::LESS_OR_EQUAL;
                        return Lexeme::RELATIONAL;
                    } else {
                        compareFlag_ = ComparisonFlag::LESS;
                        return Lexeme::RELATIONAL;
                    }
                case '=':
                    getDoubleLex('=');
                    compareFlag_ = ComparisonFlag::EQUAL;
                    return Lexeme::RELATIONAL;
                case '+':
                case '-': {
                    auto copy = ch_;
                    getNext();
                    if (!std::isdigit(ch_)) {
                        std::string additional = "digit was expected after * sign";
                        additional[25] = static_cast<char>(copy);
                        crash(additional);
                    }
                    state_ = State::NUMBER_LITERAL_INTEGER_PART;
                    top_ = 0;
                    buffer_[top_++] = static_cast<char>(copy);
                    number_ = 0.0;
                    sign_ = (copy == '+') ? 1.0 : -1.0;
                    continue;
                }
                default:
                    crash("unable to recognize lexeme");
                }


                // I D E N T I F I E R
            case State::IDENTIFIER:
                if (std::isupper(ch_)) {
                    buffer_[top_] = ' ';
                    top_++;
                    ch_ = std::tolower(ch_);
                } else if (ch_ == '_') {
                    buffer_[top_] = ' ';
                    top_++;
                    getNext();
                    if (!std::isalpha(ch_)) {
                        buffer_[top_ - 1] = '\0';
                        std::string additional = "a letter was expected after underscore in identifier \"";
                        additional += buffer_;
                        additional += '\"';
                        crash(additional);
                    } else if (std::isupper(ch_)) {
                        buffer_[top_ - 1] = '\0';
                        std::string additional = "underscore must be followed by lowercase in identifier \"";
                        additional += buffer_;
                        additional += '\"';
                        crash(additional);
                    }
                    continue;
                }
                buffer_[top_] = (char)ch_;
                top_++;
                getNext();
                if (!std::isalpha(ch_) && ch_ != '_') {
                    buffer_[top_] = '\0';
                    state_ = State::START;
                    return checkForKeyword();
                }
                continue;


                // S T R I N G     L I T E R A L
            case State::STRING_LITERAL:
                buffer_[top_] = (char)ch_;
                top_++;
                getNext();
                if (ch_ == '\"') {
                    buffer_[top_] = '\0';
                    getNext();
                    state_ = State::START;
                    return Lexeme::STRING_LITERAL;
                } else if (ch_ == endOfSequence_) {
                    buffer_[top_] = '\0';
                    std::string additional = "a close quote was expected in \"";
                    additional += buffer_;
                    crash(additional);
                }
                continue;


                // N U M B E R    L I T E R A L    I N T E G E R    P A R T
            case State::NUMBER_LITERAL_INTEGER_PART:
                number_ = number_ * 10 + ch_ - '0';
                buffer_[top_++] = static_cast<char>(ch_);
                getNext();
                if (ch_ == '.') {
                    buffer_[top_++] = static_cast<char>(ch_);
                    getNext();
                    if (!std::isdigit(ch_)) {
                        buffer_[top_] = '\0';
                        std::string additional = "a digit was expected after dot in ";
                        additional += buffer_;
                        crash(additional);
                    }
                    multiplier_ = 0.1;
                    state_ = State::NUMBER_LITERAL_RATIO_PART;
                    continue;
                } else if (!std::isdigit(ch_)) {
                    state_ = State::START;
                    number_ *= sign_;
                    return Lexeme::NUMBER_LITERAL;
                } else {
                    continue;
                }


                // N U M B E R    L I T E R A L    R A T I O    P A R T
            case State::NUMBER_LITERAL_RATIO_PART:
                number_ = number_ + (ch_ - '0') * multiplier_;
                multiplier_ *= 0.1;
                getNext();
                if (!std::isdigit(ch_)) {
                    state_ = State::START;
                    number_ *= sign_;
                    return Lexeme::NUMBER_LITERAL;
                } else {
                    continue;
                }
            }
        }
    }


    void Lexer::getNext()
    {
        ch_ = input_->get();
        charNo_++;
    }


    void Lexer::getDoubleLex(char expected)
    {
        getNext();
        if (ch_ != expected) {
            std::string additional = "lexeme ** was expected";
            additional[7] = expected;
            additional[8] = expected;
            crash(additional);
        }
        getNext();

        buffer_[0] = expected;
        buffer_[1] = expected;
        buffer_[2] = '\0';
    }


    std::string Lexer::getString() const
    {
        return std::string(buffer_);
    }


    double Lexer::getNumber() const
    {
        return number_;
    }


    void Lexer::crash(const std::string& additional)
    {
        swallow();
        throw UnexpectedCharacterException(ch_, charNo_, endOfSequence_, additional);
    }


    Lexeme::Type Lexer::checkForKeyword()
    {
        if (!std::strcmp(buffer_, Literal::strTrueLiteral)) {
            boolean_ = true;
            return Lexeme::BOOLEAN_LITERAL;
        } else if (!std::strcmp(buffer_, Literal::strFalseLiteral)) {
            boolean_ = false;
            return Lexeme::BOOLEAN_LITERAL;
        } else if (!std::strcmp(buffer_, "login")) {
            swallow();
            throw ForbiddenIdentifierException("Lexical error: \"login\" identifier is forbidden");
        } else {
            return Lexeme::IDENTIFIER;
        }
    }


    bool Lexer::getBoolean() const
    {
        return boolean_;
    }


    ComparisonFlag::Type Lexer::getCompareFlag() const
    {
        return compareFlag_;
    }
}
