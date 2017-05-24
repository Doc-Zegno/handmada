//
// Created by syzegno on 08.05.17.
//


#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "Parser.h"
#include "IAttribute.h"
#include "IPredicate.h"
#include "IAttributeContainer.h"
#include "Attributes.h"
#include "PredicatePrinter.h"


using namespace Handmada;


class AttributeContainerAdapter : public Handmada::IAttributeContainer
{
private:
    std::unordered_map<std::string, std::unique_ptr<Handmada::IAttribute>> attributes_;

public:
    virtual Handmada::IAttribute* getAttributeByName(const std::string& name) override
    {
        auto item = attributes_.find(name);
        if (item == attributes_.end()) {
            return nullptr;
        } else {
            return item->second.get();
        }
    }
    virtual const Handmada::IAttribute* getAttributeByName(const std::string& name) const override
    {
        auto item = attributes_.find(name);
        if (item == attributes_.end()) {
            return nullptr;
        } else {
            return item->second.get();
        }
    }

    void addAttribute(std::unique_ptr<Handmada::IAttribute>&& attribute)
    {
        attributes_.insert(std::make_pair(attribute->name(), std::move(attribute)));
    }
};


TEST(Parser, Simple)
{
    std::istringstream sin("age >= 18");
    Parser parser(sin);
    std::unique_ptr<Handmada::IPredicate> predicate;
    ASSERT_NO_THROW(predicate = parser.getPredicate());

    AttributeContainerAdapter adapter;
    ASSERT_FALSE((*predicate)(adapter));
    adapter.addAttribute(makeAttribute("age", 17));
    ASSERT_FALSE((*predicate)(adapter));

    AttributeContainerAdapter adapter2;
    adapter2.addAttribute(makeAttribute("age", 37));
    ASSERT_TRUE((*predicate)(adapter2));
}


TEST(Parser, Complex)
{
    std::istringstream sin("(age >= 18 && age < 60) && drinksCoffee == yes && has_a_car == yes"
                                   "|| name == \"Nick\" && !(favouriteNumber == 3.14)");
    Parser parser(sin);
    std::unique_ptr<Handmada::IPredicate> predicate;
    ASSERT_NO_THROW(predicate = parser.getPredicate());

    AttributeContainerAdapter adapter;
    adapter.addAttribute(makeAttribute("age", 37));
    adapter.addAttribute(makeAttribute("drinks coffee", true));

    ASSERT_FALSE((*predicate)(adapter));
    adapter.addAttribute(makeAttribute("has a car", true));
    ASSERT_TRUE((*predicate)(adapter));

    AttributeContainerAdapter adapter2;
    adapter2.addAttribute(makeAttribute("name", "Nick"));
    ASSERT_TRUE((*predicate)(adapter2));
    adapter2.addAttribute(makeAttribute("favourite number", 3.14));
    ASSERT_FALSE((*predicate)(adapter2));
}


TEST(Parser, Failures)
{
    std::string strings[] = {
            "Age >= 18",                           // only lowercase, "age" is OK
            "age >= \"sample text\"",              // >= is not defined for strings (and booleans)
            "age < 50.",                           // 50. is not valid, 50.0 is valid
            "age_ != 50",                          // there must be a letter after underscore
            "?",                                   // unknown lexeme
            "age > age",                           // must be <identifier><relational><literal>
            "!age",                                // "age" is not expression
            "(age > 18",                           // missing close parenthesis
            "age == 37 || age == \"sample text\"", // type mismatch
    };

    Parser parser(std::cin);

    for (auto& nextStr : strings) {
        std::istringstream sin(nextStr);
        parser.reset(sin);

        ASSERT_THROW(parser.getPredicate(), std::exception);
    }
}


TEST(Parser, Requirements)
{
    std::istringstream sin("(age >= 18 && age < 60) && drinksCoffee == yes && has_a_car == yes"
                                   "|| name == \"Nick\" && !(favouriteNumber == 3.14)");
    Parser parser(sin);
    ASSERT_NO_THROW(parser.getPredicate());

    auto requirements = parser.getIdentifiers();
    std::unordered_map<std::string, Handmada::AttributeType::Type> expected = {
            { "age", AttributeType::NUMBER },
            { "drinks coffee", AttributeType::BOOLEAN },
            { "has a car", AttributeType::BOOLEAN },
            { "name", AttributeType::STRING },
            { "favourite number", AttributeType::NUMBER },
    };

    ASSERT_TRUE(requirements == expected);
}

