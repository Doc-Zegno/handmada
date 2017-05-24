//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_PREDICATECALCULATORPRINTER_H
#define EQUEUE_V2_PREDICATECALCULATORPRINTER_H


#include <iostream>

#include "IPredicateCalculatorVisitor.h"


namespace Handmada {
    class PredicateCalculatorPrinter : public IPredicateCalculatorVisitor
    {
    private:
        std::ostream& out_;

    public:
        PredicateCalculatorPrinter(std::ostream& out);

        virtual void visit(const OrBinaryCalculator& calculator) override;
        virtual void visit(const AndBinaryCalculator& calculator) override;
        virtual void visit(const OrMultipleCalculator& calculator) override;
        virtual void visit(const AndMultipleCalculator& calculator) override;
    };
}


#endif //EQUEUE_V2_PREDICATECALCULATORPRINTER_H
