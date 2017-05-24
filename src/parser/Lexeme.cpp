//
// Created by syzegno on 10.05.17.
//


#include "../../include/parser/Lexeme.h"


namespace Handmada {
    const char* Lexeme::toString(Lexeme::Type type)
    {
        switch (type) {
        case Lexeme::UNKNOWN:
            return "unknown lexeme";
        case Lexeme::OPEN_PARENTHESIS:
            return "(";
        case Lexeme::CLOSE_PARENTHESIS:
            return ")";
        case Lexeme::OR:
            return "||";
        case Lexeme::AND:
            return "&&";
        case Lexeme::NOT:
            return "!";
        case Lexeme::RELATIONAL:
            return "relational operator";
        case Lexeme::IDENTIFIER:
            return "identifier";
        case Lexeme::STRING_LITERAL:
            return "string literal";
        case Lexeme::NUMBER_LITERAL:
            return "number literal";
        case Lexeme::BOOLEAN_LITERAL:
            return "boolean literal";
        case Lexeme::END_OF_SEQUENCE:
            return "end of sequence";
        default:
            return "";
        }
    }
}
