//
// Created by syzegno on 29.04.17.
//


#include "../../include/model/Predicates.h"

#include <cstring>
#include <iostream>

#include "../../include/abstract/IPredicateVisitor.h"


namespace Handmada {
    // N o t P r e d i c a t e
    NotPredicate::NotPredicate(IPredicate* predicate) : predicate_(predicate)
    { }


    NotPredicate::NotPredicate(std::unique_ptr<Handmada::IPredicate>&& predicate)
        : predicate_(std::move(predicate))
    { }


    bool NotPredicate::operator()(const IAttributeContainer& attributes) const
    {
        return !(*predicate_)(attributes);
    }


    void NotPredicate::accept(IPredicateVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IPredicate> NotPredicate::clone() const
    {
        return std::unique_ptr<IPredicate>(new NotPredicate(
                predicate_->clone()
        ));
    }


    std::unique_ptr<IPredicate> NotPredicate::create(
            std::unique_ptr<Handmada::IPredicate>&& predicate
    )
    {
        return std::unique_ptr<IPredicate>(
                new NotPredicate(std::move(predicate))
        );
    }



    // U n i v e r s a l B i n a r y P r e d i c a t e
    BinaryPredicate::BinaryPredicate(
            std::unique_ptr<IBinaryCalculator>&& calculator,
            std::unique_ptr<IPredicate>&& predicateA,
            std::unique_ptr<IPredicate>&& predicateB
    ) : calculator_(std::move(calculator)),
        predicateA_(std::move(predicateA)), predicateB_(std::move(predicateB))
    { }


    bool BinaryPredicate::operator()(const IAttributeContainer& attributes) const
    {
        return (*calculator_)(*predicateA_, *predicateB_, attributes);
    }


    void BinaryPredicate::accept(IPredicateVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IPredicate> BinaryPredicate::clone() const
    {
        return std::unique_ptr<IPredicate>(
                new BinaryPredicate(
                        calculator_->clone(), predicateA_->clone(), predicateB_->clone()
                )
        );
    }


    const IBinaryCalculator& BinaryPredicate::calculator() const
    {
        return *calculator_;
    }


    const IPredicate& BinaryPredicate::predicateA() const
    {
        return *predicateA_;
    }


    const IPredicate& BinaryPredicate::predicateB() const
    {
        return *predicateB_;
    }


    std::unique_ptr<IPredicate> BinaryPredicate::create(
            std::unique_ptr<IBinaryCalculator>&& calculator,
            std::unique_ptr<IPredicate>&& predicateA,
            std::unique_ptr<IPredicate>&& predicateB
    )
    {
        return std::unique_ptr<IPredicate>(
                new BinaryPredicate(
                        std::move(calculator),
                        std::move(predicateA),
                        std::move(predicateB)
                )
        );
    }



    // U n i v e r s a l M u l t i p l e P r e d i c a t e
    MultiplePredicate::MultiplePredicate(
            std::unique_ptr<IMultipleCalculator>&& calculator,
            std::vector<std::unique_ptr<IPredicate>>&& predicates
    ) : calculator_(std::move(calculator)), predicates_(std::move(predicates))
    { }


    bool MultiplePredicate::operator()(const IAttributeContainer& attributes) const
    {
        return (*calculator_)(predicates_, attributes);
    }


    void MultiplePredicate::accept(IPredicateVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IPredicate> MultiplePredicate::clone() const
    {
        decltype(predicates_) copy;
        for (auto& predicate : predicates_) {
            copy.push_back(predicate->clone());
        }
        return std::unique_ptr<IPredicate>(
                new MultiplePredicate(
                        calculator_->clone(),
                        std::move(copy)
                )
        );
    }


    const IMultipleCalculator& MultiplePredicate::calculator() const
    {
        return *calculator_;
    }


    const std::vector<std::unique_ptr<IPredicate>>& MultiplePredicate::predicates() const
    {
        return predicates_;
    }


    std::unique_ptr<IPredicate> MultiplePredicate::create(
            std::unique_ptr<IMultipleCalculator>&& calculator,
            std::vector<std::unique_ptr<IPredicate>>&& predicates
    )
    {
        return std::unique_ptr<IPredicate>(
                new MultiplePredicate(
                        std::move(calculator),
                        std::move(predicates)
                )
        );
    }



    // U n i v e r s a l C o m p a r e P r e d i c a t e
    ComparisonPredicate::ComparisonPredicate(
            ComparisonFlag::Type flag,
            std::unique_ptr<Handmada::IAttribute>&& attribute
    ) : flag_(flag), attribute_(std::move(attribute))
    { }


    bool ComparisonPredicate::operator()(const IAttributeContainer& attributes) const
    {
        auto attribute = attributes.getAttributeByName(attribute_->name());
        if (!attribute) {
            return false;
        } else {
            try {
                auto result = attribute->compareTo(*attribute_);
                return ComparisonFlag::isCompatible(result, flag_);
            } catch (std::exception&) {
                return false;
            }
        }
    }


    void ComparisonPredicate::accept(IPredicateVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const IAttribute& ComparisonPredicate::attribute() const
    {
        return *attribute_;
    }


    const ComparisonFlag::Type ComparisonPredicate::flag() const
    {
        return flag_;
    }


    std::unique_ptr<IPredicate> ComparisonPredicate::clone() const
    {
        return std::unique_ptr<IPredicate>(new ComparisonPredicate(
                flag_,
                attribute_->clone()
        ));
    }


    std::unique_ptr<IPredicate> ComparisonPredicate::create(
            ComparisonFlag::Type flag,
            std::unique_ptr<IAttribute>&& attribute
    )
    {
        return std::unique_ptr<IPredicate>(
                new ComparisonPredicate(flag, std::move(attribute))
        );
    }
}
