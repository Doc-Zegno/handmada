//
// Created by syzegno on 08.05.17.
//


#include "StreamPredicatePrinter.h"
#include "MetaNumber.h"
#include "Serializer.h"
#include "StreamPredicateCalculatorPrinter.h"


namespace Handmada {
    StreamPredicatePrinter::StreamPredicatePrinter(IStream& stream)
        : stream_(stream)
    { }


    void StreamPredicatePrinter::visit(const NotPredicate& predicate)
    {
        Serializer::put(stream_, MetaNumber::NOT_PREDICATE);
        predicate.predicate_->accept(*this);
    }


    void StreamPredicatePrinter::visit(const BinaryPredicate& predicate)
    {
        Serializer::put(stream_, MetaNumber::BINARY_PREDICATE);
        StreamPredicateCalculatorPrinter printer(stream_);
        predicate.calculator().accept(printer);
        predicate.predicateA().accept(*this);
        predicate.predicateB().accept(*this);
    }


    void StreamPredicatePrinter::visit(const MultiplePredicate& predicate)
    {
        Serializer::put(stream_, MetaNumber::MULTIPLE_PREDICATE);
        StreamPredicateCalculatorPrinter printer(stream_);
        predicate.calculator().accept(printer);
        Serializer::put(stream_, predicate.predicates().size());
        for (auto& pre : predicate.predicates()) {
            pre->accept(*this);
        }
    }


    void StreamPredicatePrinter::visit(const ComparisonPredicate& predicate)
    {
        Serializer::put(stream_, MetaNumber::COMPARISON_PREDICATE);
        Serializer::put(stream_, predicate.flag());
        StreamAttributePrinter printer(stream_);
        predicate.attribute().accept(printer);
    }
}
