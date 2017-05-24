//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_IPREDICATEVISITOR_H
#define EQUEUE_V2_IPREDICATEVISITOR_H


#include "Predicates.h"


namespace Handmada {
    class IPredicateVisitor
    {
    public:
        virtual void visit(const NotPredicate& predicate) = 0;
        virtual void visit(const ComparisonPredicate& predicate) = 0;
        virtual void visit(const BinaryPredicate& predicate) = 0;
        virtual void visit(const MultiplePredicate& predicate) = 0;

        virtual ~IPredicateVisitor() { }
    };
}


#endif //EQUEUE_V2_IPREDICATEVISITOR_H
