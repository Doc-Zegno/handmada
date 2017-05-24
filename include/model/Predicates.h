//
// Created by syzegno on 29.04.17.
//

#ifndef EQUEUE_V2_PREDICATES_H
#define EQUEUE_V2_PREDICATES_H


#include <memory>
#include <exception>

#include "IPredicate.h"
#include "Attributes.h"
#include "ComparisonFlag.h"
#include "IPredicateCalculator.h"


namespace Handmada {
    /**
     * Imitates logical NOT
     * Keeping in mind that there is NOT_EQUAL compare flag
     * I can't believe the system really needs this predicate
     *
     * However its presence makes (formally) the logical predicates system complete,
     * according to Post's Theorem. At least, this implies I don't have to to implement
     * such relationship as "implies" (pun intended)
     */
    class NotPredicate : public IPredicate
    {
    private:
        std::unique_ptr<Handmada::IPredicate> predicate_;

        friend class PredicatePrinter;
        friend class StreamPredicatePrinter;

    public:
        /// \deprecated consider using create() instead
        NotPredicate(IPredicate* predicate);
        /// \deprecated consider using create() instead
        NotPredicate(std::unique_ptr<Handmada::IPredicate>&& predicate);

        virtual bool operator()(const IAttributeContainer& attributes) const override;
        virtual void accept(IPredicateVisitor& visitor) const override;
        virtual std::unique_ptr<IPredicate> clone() const override;

        static std::unique_ptr<IPredicate> create(
                std::unique_ptr<Handmada::IPredicate>&& predicate
        );
    };


    // U n i v e r s a l    v e r s i o n s
    class BinaryPredicate : public IPredicate
    {
    private:
        std::unique_ptr<IBinaryCalculator> calculator_;
        std::unique_ptr<IPredicate> predicateA_;
        std::unique_ptr<IPredicate> predicateB_;

    public:
        /// \deprecated consider using create() instead
        BinaryPredicate(
                std::unique_ptr<IBinaryCalculator>&& calculator,
                std::unique_ptr<IPredicate>&& predicateA,
                std::unique_ptr<IPredicate>&& predicateB
        );

        virtual bool operator()(const IAttributeContainer& attributes) const override;
        virtual void accept(IPredicateVisitor& visitor) const override;
        virtual std::unique_ptr<IPredicate> clone() const override;

        const IBinaryCalculator& calculator() const;
        const IPredicate& predicateA() const;
        const IPredicate& predicateB() const;

        static std::unique_ptr<IPredicate> create(
                std::unique_ptr<IBinaryCalculator>&& calculator,
                std::unique_ptr<IPredicate>&& predicateA,
                std::unique_ptr<IPredicate>&& predicateB
        );
    };


    class MultiplePredicate : public IPredicate
    {
    private:
        std::unique_ptr<IMultipleCalculator> calculator_;
        std::vector<std::unique_ptr<IPredicate>> predicates_;

    public:
        /// \deprecated consider using create() instead
        MultiplePredicate(
                std::unique_ptr<IMultipleCalculator>&& calculator,
                std::vector<std::unique_ptr<IPredicate>>&& predicates
        );

        virtual bool operator()(const IAttributeContainer& attributes) const override;
        virtual void accept(IPredicateVisitor& visitor) const override;
        virtual std::unique_ptr<IPredicate> clone() const override;

        const IMultipleCalculator& calculator() const;
        const std::vector<std::unique_ptr<IPredicate>>& predicates() const;

        static std::unique_ptr<IPredicate> create(
                std::unique_ptr<IMultipleCalculator>&& calculator,
                std::vector<std::unique_ptr<IPredicate>>&& predicates
        );
    };





    class ComparisonPredicate : public IPredicate
    {
    private:
        ComparisonFlag::Type flag_;
        std::unique_ptr<Handmada::IAttribute> attribute_;

    public:
        ComparisonPredicate(
                ComparisonFlag::Type flag,
                std::unique_ptr<Handmada::IAttribute>&& attribute
        );

        virtual bool operator()(const IAttributeContainer& attributes) const override;
        virtual void accept(IPredicateVisitor& visitor) const override;
        virtual std::unique_ptr<IPredicate> clone() const override;

        const IAttribute& attribute() const;
        const ComparisonFlag::Type flag() const;

        static std::unique_ptr<IPredicate> create(
                ComparisonFlag::Type flag,
                std::unique_ptr<IAttribute>&& attribute
        );
    };
}


#endif //EQUEUE_V2_PREDICATES_H
