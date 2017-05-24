//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IPREDICATECALCULATOR_H
#define EQUEUE_V2_IPREDICATECALCULATOR_H


#include <memory>
#include <vector>

#include "IAttributeContainer.h"
#include "IPredicate.h"


namespace Handmada {
    class IPredicateCalculatorVisitor;


    class IBinaryCalculator {
    public:
        virtual bool operator()(
                const IPredicate& a,
                const IPredicate& b,
                const IAttributeContainer& container
        ) const = 0;
        virtual void accept(IPredicateCalculatorVisitor& visitor) const = 0;
        virtual std::unique_ptr<IBinaryCalculator> clone() const = 0;

        virtual ~IBinaryCalculator() { }
    };


    class IMultipleCalculator {
    public:
        virtual bool operator()(
                const std::vector<std::unique_ptr<IPredicate>>& predicates,
                const IAttributeContainer& container
        ) const = 0;
        virtual void accept(IPredicateCalculatorVisitor& visitor) const = 0;
        virtual std::unique_ptr<IMultipleCalculator> clone() const = 0;

        virtual ~IMultipleCalculator() { }
    };
}


#endif //EQUEUE_V2_IPREDICATECALCULATOR_H
