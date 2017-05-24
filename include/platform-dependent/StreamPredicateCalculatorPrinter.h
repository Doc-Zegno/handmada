//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_STREAMPREDICATECALCULATORPRINTER_H
#define EQUEUE_V2_STREAMPREDICATECALCULATORPRINTER_H


#include "IPredicateCalculatorVisitor.h"
#include "IStream.h"


namespace Handmada {
    class StreamPredicateCalculatorPrinter : public IPredicateCalculatorVisitor
    {
    private:
        IStream& stream_;

    public:
        StreamPredicateCalculatorPrinter(IStream& stream);

        virtual void visit(const OrBinaryCalculator& calculator) override;
        virtual void visit(const AndBinaryCalculator& calculator) override;
        virtual void visit(const OrMultipleCalculator& calculator) override;
        virtual void visit(const AndMultipleCalculator& calculator) override;
    };
}


#endif //EQUEUE_V2_STREAMPREDICATECALCULATORPRINTER_H
