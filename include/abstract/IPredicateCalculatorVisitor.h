//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IPREDICATECALCULATORVISITOR_H
#define EQUEUE_V2_IPREDICATECALCULATORVISITOR_H


#include "PredicateCalculators.h"


namespace Handmada {
    class IPredicateCalculatorVisitor
    {
    public:
        virtual void visit(const OrBinaryCalculator& calculator) = 0;
        virtual void visit(const AndBinaryCalculator& calculator) = 0;
        virtual void visit(const OrMultipleCalculator& calculator) = 0;
        virtual void visit(const AndMultipleCalculator& calculator) = 0;

        virtual ~IPredicateCalculatorVisitor() { }
    };
}


#endif //EQUEUE_V2_IPREDICATECALCULATORVISITOR_H
