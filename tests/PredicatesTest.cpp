//
// Created by syzegno on 29.04.17.
//


#include <gtest/gtest.h>

#include "Predicates.h"
#include "PredicateCalculators.h"

using namespace Handmada;


class SimpleContainer : public IAttributeContainer
{
private:
    std::vector<std::unique_ptr<Handmada::IAttribute>> attributes_;

public:
    virtual IAttribute* getAttributeByName(const std::string& name) override
    {
        for (const auto& attribute : attributes_) {
            if (attribute->name() == name) {
                return &(*attribute);
            }
        }
        return nullptr;
    }

    virtual const IAttribute* getAttributeByName(const std::string& name) const override
    {
        for (const auto& attribute : attributes_) {
            if (attribute->name() == name) {
                return &(*attribute);
            }
        }
        return nullptr;
    }

    template<typename T>
    void add(T&& attribute)
    {
        attributes_.push_back(std::forward<T>(attribute));
    }
};


TEST(Predicates, String)
{
    SimpleContainer container;
    container.add(makeAttribute("login", "User"));
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));
    container.add(makeAttribute("job", "coder"));
    container.add(makeAttribute("approved?", true));

    ComparisonPredicate predicateA(ComparisonFlag::EQUAL, makeAttribute("country", "Russia"));
    ComparisonPredicate predicateB(ComparisonFlag::NOT_EQUAL, makeAttribute("age", "random word"));
    ComparisonPredicate predicateC(ComparisonFlag::NOT_EQUAL, makeAttribute("job", "programmer"));
    ComparisonPredicate predicateD(ComparisonFlag::EQUAL, makeAttribute("approved?", "true"));
    ComparisonPredicate predicateE(ComparisonFlag::EQUAL, makeAttribute("there cannot be", "such attribute"));

    ASSERT_TRUE(predicateA(container));
    ASSERT_FALSE(predicateB(container));
    ASSERT_TRUE(predicateC(container));
    ASSERT_FALSE(predicateD(container));
    ASSERT_FALSE(predicateE(container));
}


TEST(Predicates, Number)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));
    container.add(makeAttribute("proven theorems", 800));
    container.add(makeAttribute("approved?", true));

    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::GREATER, makeAttribute("country", 77))(container));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::LESS_OR_EQUAL, makeAttribute("age", 38))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::LESS, makeAttribute("age", 37))(container));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::NOT_EQUAL, makeAttribute("age", 137))(container));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("age", 37))(container));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::GREATER, makeAttribute("proven theorems", 799))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("approved?", 1))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("NAN", 0.0))(container));

    container.add(makeAttribute("NAN", 0.0));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("NAN", 0.0))(container));
}


TEST(Predicates, Boolean)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("unique", true));
    container.add(makeAttribute("proven theorems", 800));
    container.add(makeAttribute("approved?", true));

    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("country", false))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::NOT_EQUAL, makeAttribute("country", false))(container));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("unique", true))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::NOT_EQUAL, makeAttribute("unique", true))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("unique", false))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::EQUAL, makeAttribute("proven theorems", false))(container));
    ASSERT_TRUE(ComparisonPredicate(ComparisonFlag::NOT_EQUAL, makeAttribute("approved?", false))(container));
    ASSERT_FALSE(ComparisonPredicate(ComparisonFlag::NOT_EQUAL, makeAttribute("no such field", false))(container));
}


TEST(Predicates, OrBinary)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));
    container.add(makeAttribute("proven theorems", 800));
    container.add(makeAttribute("approved?", true));

    ASSERT_TRUE(BinaryPredicate(
            OrBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("age", 37)),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("proven theorems", 800))
    )(container));

    ASSERT_TRUE(BinaryPredicate(
            OrBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("age", 37)),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("proven theorems", 799))
    )(container));

    ASSERT_TRUE(BinaryPredicate(
            OrBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("age", 137)),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("proven theorems", 800))
    )(container));

    ASSERT_FALSE(BinaryPredicate(
            OrBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("age", 137)),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("proven theorems", 799))
    )(container));

    ASSERT_TRUE(BinaryPredicate(
            OrBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("country", "Russia")),
            ComparisonPredicate::create(ComparisonFlag::LESS, makeAttribute("proven theorems", 799))
    )(container));

    ASSERT_FALSE(BinaryPredicate(
            OrBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::NOT_EQUAL, makeAttribute("country", "Russia")),
            ComparisonPredicate::create(ComparisonFlag::LESS, makeAttribute("proven theorems", 799))
    )(container));
}


TEST(Predicates, Not)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));
    container.add(makeAttribute("has a car", true));

    ASSERT_FALSE(NotPredicate(ComparisonPredicate::create(
            ComparisonFlag::EQUAL, makeAttribute("country", "Russia")
    ))(container));
    ASSERT_TRUE(NotPredicate(ComparisonPredicate::create(
            ComparisonFlag::NOT_EQUAL, makeAttribute("country", "Russia")
    ))(container));
    ASSERT_TRUE(NotPredicate(ComparisonPredicate::create(
            ComparisonFlag::EQUAL, makeAttribute("country", "England")
    ))(container));
    ASSERT_TRUE(NotPredicate(ComparisonPredicate::create(
            ComparisonFlag::NOT_EQUAL, makeAttribute("age", 37)
    ))(container));
    ASSERT_FALSE(NotPredicate(ComparisonPredicate::create(
            ComparisonFlag::EQUAL, makeAttribute("has a car", true)
    ))(container));
}


TEST(Predicates, AndBinary)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));

    ASSERT_TRUE(BinaryPredicate(
            AndBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("country", "Russia")),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("age", 37))
    )(container));

    ASSERT_FALSE(BinaryPredicate(
            AndBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::LESS, makeAttribute("age", 37)),
            ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("country", "Russia"))
    )(container));

    ASSERT_FALSE(BinaryPredicate(
            AndBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::GREATER_OR_EQUAL, makeAttribute("age", 37)),
            ComparisonPredicate::create(ComparisonFlag::NOT_EQUAL, makeAttribute("country", "Russia"))
    )(container));

    ASSERT_FALSE(BinaryPredicate(
            AndBinaryCalculator::create(),
            ComparisonPredicate::create(ComparisonFlag::NOT_EQUAL, makeAttribute("country", "Russia")),
            ComparisonPredicate::create(ComparisonFlag::LESS, makeAttribute("age", 37))
    )(container));
}

TEST(Predicates, Misc)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));
    container.add(makeAttribute("has a car", true));

    ASSERT_TRUE(BinaryPredicate(
            AndBinaryCalculator::create(),
            NotPredicate::create(
                    ComparisonPredicate::create(
                            ComparisonFlag::NOT_EQUAL, makeAttribute("country", "Russia")
                    )
            ),
            ComparisonPredicate::create(ComparisonFlag::LESS, makeAttribute("age", 38))
    )(container));

    ASSERT_FALSE(NotPredicate(
            BinaryPredicate::create(
                    AndBinaryCalculator::create(),
                    ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("country", "Russia")),
                    ComparisonPredicate::create(ComparisonFlag::GREATER_OR_EQUAL, makeAttribute("age", 37))
            )
    )(container));
}

TEST(Predicates, Multiple)
{
    SimpleContainer container;
    container.add(makeAttribute("country", "Russia"));
    container.add(makeAttribute("age", 37));
    container.add(makeAttribute("has a car", true));

    std::vector<std::unique_ptr<IPredicate>> predicates1;
    predicates1.push_back(ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("country", "Russia")));
    predicates1.push_back(ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("age", 37)));
    predicates1.push_back(ComparisonPredicate::create(ComparisonFlag::EQUAL, makeAttribute("has a car", false)));

    decltype(predicates1) predicates2, predicates3, predicates4;
    for (auto& predicate : predicates1) {
        predicates2.push_back(predicate->clone());
        predicates3.push_back(predicate->clone());
        predicates4.push_back(predicate->clone());
    }

    ASSERT_TRUE(MultiplePredicate(
            OrMultipleCalculator::create(),
            std::move(predicates1)
    )(container));

    ASSERT_FALSE(MultiplePredicate(
            AndMultipleCalculator::create(),
            std::move(predicates2)
    )(container));

    predicates3[2] = ComparisonPredicate::create(ComparisonFlag::NOT_EQUAL, makeAttribute("has a car", false));
    ASSERT_TRUE(MultiplePredicate(
            AndMultipleCalculator::create(),
            std::move(predicates3)
    )(container));

    predicates4[0] = ComparisonPredicate::create(ComparisonFlag::NOT_EQUAL, makeAttribute("country", "Russia"));
    predicates4[1] = ComparisonPredicate::create(ComparisonFlag::NOT_EQUAL, makeAttribute("age", 37));
    ASSERT_FALSE(MultiplePredicate(
            OrMultipleCalculator::create(),
            std::move(predicates4)
    )(container));
}
