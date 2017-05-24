//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_PREDICATECALCULATORS_H
#define EQUEUE_V2_PREDICATECALCULATORS_H


#include <vector>
#include <memory>

#include "IPredicateCalculator.h"
#include "IPredicate.h"


namespace Handmada {
    class OrBinaryCalculator : public IBinaryCalculator
    {
    public:
        virtual bool operator()(
                const IPredicate& a,
                const IPredicate& b,
                const IAttributeContainer& container
        ) const override;
        virtual void accept(IPredicateCalculatorVisitor& visitor) const override;
        virtual std::unique_ptr<IBinaryCalculator> clone() const override;

        static std::unique_ptr<IBinaryCalculator> create();
    };


    class AndBinaryCalculator : public IBinaryCalculator
    {
    public:
        virtual bool operator()(
                const IPredicate& a,
                const IPredicate& b,
                const IAttributeContainer& container
        ) const override;
        virtual void accept(IPredicateCalculatorVisitor& visitor) const override;
        virtual std::unique_ptr<IBinaryCalculator> clone() const override;

        static std::unique_ptr<IBinaryCalculator> create();
    };


    class OrMultipleCalculator : public IMultipleCalculator
    {
    public:
        virtual bool operator()(
                const std::vector<std::unique_ptr<IPredicate>>& predicates,
                const IAttributeContainer& container
        ) const override;
        virtual void accept(IPredicateCalculatorVisitor& visitor) const override;
        virtual std::unique_ptr<IMultipleCalculator> clone() const override;

        static std::unique_ptr<IMultipleCalculator> create();
    };


    class AndMultipleCalculator : public IMultipleCalculator
    {
    public:
        virtual bool operator()(
                const std::vector<std::unique_ptr<IPredicate>>& predicates,
                const IAttributeContainer& container
        ) const override;
        virtual void accept(IPredicateCalculatorVisitor& visitor) const override;
        virtual std::unique_ptr<IMultipleCalculator> clone() const override;

        static std::unique_ptr<IMultipleCalculator> create();
    };
}


#endif //EQUEUE_V2_PREDICATECALCULATORS_H
