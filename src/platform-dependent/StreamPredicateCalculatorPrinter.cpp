//
// Created by syzegno on 19.05.17.
//


#include "StreamPredicateCalculatorPrinter.h"
#include "Serializer.h"
#include "MetaNumber.h"


namespace Handmada {
    StreamPredicateCalculatorPrinter::StreamPredicateCalculatorPrinter(IStream& stream)
            : stream_(stream)
    { }


    void StreamPredicateCalculatorPrinter::visit(const OrBinaryCalculator& calculator)
    {
        Serializer::put(stream_, MetaNumber::OR_BINARY_CALCULATOR);
    }


    void StreamPredicateCalculatorPrinter::visit(const AndBinaryCalculator& calculator)
    {
        Serializer::put(stream_, MetaNumber::AND_BINARY_CALCULATOR);
    }


    void StreamPredicateCalculatorPrinter::visit(const OrMultipleCalculator& calculator)
    {
        Serializer::put(stream_, MetaNumber::OR_MULTIPLE_CALCULATOR);
    }


    void StreamPredicateCalculatorPrinter::visit(const AndMultipleCalculator& calculator)
    {
        Serializer::put(stream_, MetaNumber::AND_MULTIPLE_CALCULATOR);
    }
}
