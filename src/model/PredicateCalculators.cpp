//
// Created by syzegno on 19.05.17.
//


#include "PredicateCalculators.h"
#include "IPredicateCalculatorVisitor.h"


namespace Handmada {
    // O r B i n a r y
    bool OrBinaryCalculator::operator()(
            const IPredicate& a,
            const IPredicate& b,
            const IAttributeContainer& container
    ) const
    {
        return a(container) || b(container);
    }


    void OrBinaryCalculator::accept(IPredicateCalculatorVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IBinaryCalculator> OrBinaryCalculator::clone() const
    {
        return std::unique_ptr<IBinaryCalculator>(
                new OrBinaryCalculator()
        );
    }


    std::unique_ptr<IBinaryCalculator> OrBinaryCalculator::create()
    {
        return std::unique_ptr<IBinaryCalculator>(new OrBinaryCalculator());
    }



    // A n d B i n a r y
    bool AndBinaryCalculator::operator()(
            const IPredicate& a,
            const IPredicate& b,
            const IAttributeContainer& container
    ) const
    {
        return a(container) && b(container);
    }


    void AndBinaryCalculator::accept(IPredicateCalculatorVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IBinaryCalculator> AndBinaryCalculator::clone() const
    {
        return std::unique_ptr<IBinaryCalculator>(
                new AndBinaryCalculator()
        );
    }


    std::unique_ptr<IBinaryCalculator> AndBinaryCalculator::create()
    {
        return std::unique_ptr<IBinaryCalculator>(new AndBinaryCalculator());
    }



    // O r M u l t i p l e
    bool OrMultipleCalculator::operator()(
            const std::vector<std::unique_ptr<IPredicate>>& predicates,
            const IAttributeContainer& container
    ) const
    {
        for (auto& predicate : predicates) {
            if ((*predicate)(container)) {
                return true;
            }
        }
        return false;
    }


    void OrMultipleCalculator::accept(IPredicateCalculatorVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IMultipleCalculator> OrMultipleCalculator::clone() const
    {
        return std::unique_ptr<IMultipleCalculator>(
                new OrMultipleCalculator()
        );
    }


    std::unique_ptr<IMultipleCalculator> OrMultipleCalculator::create()
    {
        return std::unique_ptr<IMultipleCalculator>(new OrMultipleCalculator());
    }



    // A n d M u l t i p l e
    bool AndMultipleCalculator::operator()(
            const std::vector<std::unique_ptr<IPredicate>>& predicates,
            const IAttributeContainer& container
    ) const
    {
        for (auto& predicate : predicates) {
            if (!(*predicate)(container)) {
                return false;
            }
        }
        return true;
    }


    void AndMultipleCalculator::accept(IPredicateCalculatorVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IMultipleCalculator> AndMultipleCalculator::clone() const
    {
        return std::unique_ptr<IMultipleCalculator>(
                new AndMultipleCalculator()
        );
    }


    std::unique_ptr<IMultipleCalculator> AndMultipleCalculator::create()
    {
        return std::unique_ptr<IMultipleCalculator>(new AndMultipleCalculator());
    }
}
