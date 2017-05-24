//
// Created by syzegno on 10.05.17.
//

#ifndef EQUEUE_V2_LEXEME_H
#define EQUEUE_V2_LEXEME_H


namespace Handmada {
    class Lexeme
    {
    public:
        enum Type {
            UNKNOWN,
            OPEN_PARENTHESIS,
            CLOSE_PARENTHESIS,

            OR,
            AND,
            NOT,

            RELATIONAL,

            IDENTIFIER,
            STRING_LITERAL,
            NUMBER_LITERAL,
            BOOLEAN_LITERAL,
            END_OF_SEQUENCE,
        };

        static const char* toString(Lexeme::Type type);
    };
}


#endif //EQUEUE_V2_LEXEME_H
