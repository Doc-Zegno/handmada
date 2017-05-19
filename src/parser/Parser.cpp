//
// Created by syzegno on 07.05.17.
//

#include "Parser.h"

#include <sstream>

#include "Predicates.h"
#include "PredicateCalculators.h"


namespace Handmada {
    // E x c e p t i o n s
    UnexpectedLexemeException::UnexpectedLexemeException(Lexeme::Type type)
            : info_("Syntax error: unexpected lexeme: ")
    {
        info_ += Lexeme::toString(type);
    }
    const char* UnexpectedLexemeException::what() const noexcept
    {
        return info_.c_str();
    }



    AttributeTypeMismatchException::AttributeTypeMismatchException(const std::string& info)
            : info_(info)
    { }

    const char* AttributeTypeMismatchException::what() const noexcept
    {
        return info_.c_str();
    }



    UnsupportedPredicateException::UnsupportedPredicateException(const std::string& info)
            : runtime_error(info)
    { }



    // P a r s e r
    Parser::Parser(std::istream& input, int endOfSequenceCharacter)
            : input_(&input), endOfSequenceCharacter_(endOfSequenceCharacter) { }


    void Parser::getNext()
    {
        type_ = lexer_.getLex();
    }


    std::unique_ptr<IPredicate> Parser::E()
    {
        std::vector<std::unique_ptr<Handmada::IPredicate>> predicates;
        while (true) {
            predicates.push_back(G());
            if (type_ == Lexeme::OR) {
                getNext();
            } else {
                break;
            }
        }

        switch (predicates.size()) {
        case 1:
            return std::move(predicates[0]);
        case 2:
            return BinaryPredicate::create(
                OrBinaryCalculator::create(),
                std::move(predicates[0]),
                std::move(predicates[1])
            );
        default:
            return MultiplePredicate::create(
                    OrMultipleCalculator::create(),
                    std::move(predicates)
            );
        }
    }


    std::unique_ptr<IPredicate> Parser::G()
    {
        std::vector<std::unique_ptr<Handmada::IPredicate>> predicates;
        while (true) {
            predicates.push_back(C());
            if (type_ == Lexeme::AND) {
                getNext();
            } else {
                break;
            }
        }

        switch (predicates.size()) {
        case 1:
            return std::move(predicates[0]);
        case 2:
            return BinaryPredicate::create(
                    AndBinaryCalculator::create(),
                    std::move(predicates[0]),
                    std::move(predicates[1])
            );
        default:
            return MultiplePredicate::create(
                    AndMultipleCalculator::create(),
                    std::move(predicates)
            );
        }
    }


    std::unique_ptr<IPredicate> Parser::C()
    {
        if (type_ == Lexeme::NOT) {
            getNext();
            if (type_ != Lexeme::OPEN_PARENTHESIS) {
                crash();
            }
            getNext();
            auto predicate = E();
            if (type_ != Lexeme::CLOSE_PARENTHESIS) {
                crash();
            }
            getNext();
            return std::unique_ptr<IPredicate>(new NotPredicate(std::move(predicate)));
        } else if (type_ == Lexeme::OPEN_PARENTHESIS) {
            getNext();
            auto predicate = E();
            if (type_ != Lexeme::CLOSE_PARENTHESIS) {
                crash();
            }
            getNext();
            return std::move(predicate);
        } else {
            return B();
        }
    }


    std::unique_ptr<IPredicate> Parser::B()
    {
        if (!isIdentifier()) {
            crash();
        }
        std::string identifier = lexer_.getString();
        getNext();

        if (!isOperation()) {
            crash();
        }
        ComparisonFlag::Type operation = lexer_.getCompareFlag();
        getNext();

        if (!isLiteral()) {
            crash();
        }
        auto attribute = getAttribute(identifier);
        checkForUnsupportedOperation(operation, attribute->type());
        addIdentifier(identifier, attribute->type());
        getNext();
        return std::unique_ptr<IPredicate>(
                new ComparisonPredicate(operation, std::move(attribute))
        );
    }


    std::unique_ptr<IPredicate> Parser::getPredicate()
    {
        lexer_.reset(*input_, endOfSequenceCharacter_);
        getNext();
        auto predicate = E();
        if (type_ != Lexeme::END_OF_SEQUENCE) {
            crash();
        }
        return std::move(predicate);
    }


    std::unordered_map<std::string, Handmada::AttributeType::Type> Parser::getIdentifiers()
    {
        return std::move(identifiers_);
    }


    void Parser::addIdentifier(const std::string& name, AttributeType::Type type)
    {
        auto iterator = identifiers_.find(name);
        if (iterator == identifiers_.end()) {
            identifiers_.insert(std::make_pair(name, type));
        } else {
            if (type != iterator->second) {
                std::ostringstream sout;
                sout << "Attribute type mismatch for \"" << name << "\": "
                     << AttributeType::toString(type) << " and "
                     << AttributeType::toString(iterator->second);
                lexer_.swallow();
                throw AttributeTypeMismatchException(sout.str());
            }
        }
    }


    void Parser::crash()
    {
        lexer_.swallow();
        throw UnexpectedLexemeException(type_);
    }


    bool Parser::isIdentifier() const
    {
        return type_ == Lexeme::IDENTIFIER;
    }


    bool Parser::isOperation() const
    {
        return type_ == Lexeme::RELATIONAL;
    }


    bool Parser::isLiteral() const
    {
        return type_ == Lexeme::STRING_LITERAL || type_ == Lexeme::NUMBER_LITERAL
               || type_ == Lexeme::BOOLEAN_LITERAL;
    }


    void Parser::reset(std::istream& input, int endOfSequenceCharacter)
    {
        identifiers_.clear();
        input_ = &input;
        endOfSequenceCharacter_ = endOfSequenceCharacter;
    }


    std::unique_ptr<IAttribute> Parser::getAttribute(const std::string& name) const
    {
        if (type_ == Lexeme::STRING_LITERAL) {
            auto literal = lexer_.getString();
            return makeAttribute(name, literal);
        } else if (type_ == Lexeme::NUMBER_LITERAL) {
            auto literal = lexer_.getNumber();
            return makeAttribute(name, literal);
        } else {
            auto literal = lexer_.getBoolean();
            return makeAttribute(name, literal);
        }
    }


    void Parser::checkForUnsupportedOperation(ComparisonFlag::Type flag, AttributeType::Type type) const
    {
        if (type == AttributeType::STRING || type == AttributeType::BOOLEAN) {
            if (flag != ComparisonFlag::EQUAL && flag != ComparisonFlag::NOT_EQUAL) {
                std::string info = AttributeType::toString(type);
                info += " attributes support only equality and inequality tests";
                lexer_.swallow();
                throw UnsupportedPredicateException(info);
            }
        }
    }
}
