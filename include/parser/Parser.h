//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_PARSER_H
#define EQUEUE_V2_PARSER_H


#include <memory>
#include <string>
#include <unordered_map>

#include "IPredicate.h"
#include "AttributeType.h"
#include "Lexer.h"


namespace Handmada {
    class UnexpectedLexemeException : public std::exception
    {
    private:
        std::string info_;

    public:
        UnexpectedLexemeException(Lexeme::Type type);
        virtual const char* what() const noexcept override;
    };


    class AttributeTypeMismatchException : public std::exception
    {
    private:
        std::string info_;

    public:
        AttributeTypeMismatchException(const std::string& info);
        virtual const char* what() const noexcept override;
    };


    class UnsupportedPredicateException : public std::runtime_error
    {
    public:
        UnsupportedPredicateException(const std::string& info);
    };



    /**
     * Formal grammar:
     * E -> G { || G }
     * G -> C { && C }
     * C -> B | !(E) | (E)
     * B -> <identifier><operation><literal>
     *
     * where { } denotes an optional sequence (iteration)
     */
    class Parser
    {
    private:
        Lexeme::Type type_;
        Lexer lexer_;
        std::unordered_map<std::string, Handmada::AttributeType::Type> identifiers_;
        std::istream* input_;
        int endOfSequenceCharacter_;

        void getNext();
        bool isIdentifier() const;
        bool isOperation() const;
        bool isLiteral() const;
        void crash();
        void checkForUnsupportedOperation(ComparisonFlag::Type flag, AttributeType::Type type) const;
        std::unique_ptr<IAttribute> getAttribute(const std::string& name) const;
        void addIdentifier(const std::string& name, AttributeType::Type type);
        std::unique_ptr<IPredicate> E();
        std::unique_ptr<IPredicate> G();
        std::unique_ptr<IPredicate> C();
        std::unique_ptr<IPredicate> B();

    public:
        Parser(std::istream& input, int endOfSequenceCharacter = EOF);

        std::unique_ptr<IPredicate> getPredicate();
        std::unordered_map<std::string, Handmada::AttributeType::Type> getIdentifiers();
        void reset(std::istream& input, int endOfSequenceCharacter = EOF);
    };
}


#endif //EQUEUE_V2_PARSER_H
