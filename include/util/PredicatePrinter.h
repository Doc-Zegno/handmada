//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_PREDICATEPRINTER_H
#define EQUEUE_V2_PREDICATEPRINTER_H


#include <iostream>

#include "IPredicateVisitor.h"


namespace Handmada {
    class PredicatePrinter : public IPredicateVisitor
    {
    private:
        std::ostream& output_;
        int shift_;

    public:
        PredicatePrinter(std::ostream& output, int shift = 0);

        virtual void visit(const NotPredicate& predicate) override;
        virtual void visit(const BinaryPredicate& predicate) override;
        virtual void visit(const MultiplePredicate& predicate) override;
        virtual void visit(const ComparisonPredicate& predicate) override;
    };
}


#endif //EQUEUE_V2_PREDICATEPRINTER_H
