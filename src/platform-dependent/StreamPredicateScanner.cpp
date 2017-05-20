//
// Created by syzegno on 08.05.17.
//


#include "StreamPredicateScanner.h"

#include <cstring>

#include "Predicates.h"
#include "StreamAttributeScanner.h"
#include "StreamPredicateCalculatorScanner.h"
#include "Serializer.h"


namespace Handmada {
    StreamPredicateScannerException::StreamPredicateScannerException(const std::string& info)
            : runtime_error(info)
    { }


    StreamPredicateScanner::StreamPredicateScanner(IStream& stream)
            : stream_(stream)
    { }


    std::unique_ptr<Handmada::IPredicate> StreamPredicateScanner::getNext() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);

        switch (meta) {
        case MetaNumber::COMPARISON_PREDICATE:
            return getComparison();

        case MetaNumber::NOT_PREDICATE:
            return getNot();

        case MetaNumber::BINARY_PREDICATE:
            return getBinary();

        case MetaNumber::MULTIPLE_PREDICATE:
            return getMultiple();

        default:
            throw StreamPredicateScannerException("unknown meta");
        }
    }



    std::unique_ptr<Handmada::IPredicate> StreamPredicateScanner::getNot() const
    {
        auto predicate = getNext();
        return std::unique_ptr<IPredicate>(new NotPredicate(std::move(predicate)));
    }


    std::vector<std::unique_ptr<Handmada::IPredicate>> StreamPredicateScanner::getVector() const
    {
        size_t size;
        Serializer::get(stream_, size);
        std::vector<std::unique_ptr<Handmada::IPredicate>> predicates;
        for (size_t i = 0; i < size; i++) {
            predicates.push_back(getNext());
        }
        return std::move(predicates);
    }


    std::unique_ptr<Handmada::IPredicate> StreamPredicateScanner::getComparison() const
    {
        ComparisonFlag::Type flag;
        Serializer::get(stream_, flag);

        StreamAttributeScanner scanner(stream_);
        auto attribute = scanner.getNext();
        return ComparisonPredicate::create(flag, std::move(attribute));
    }

    std::unique_ptr<IPredicate> StreamPredicateScanner::getBinary() const
    {
        StreamPredicateCalculatorScanner scanner(stream_);
        auto calculator = scanner.getBinary();

        auto a = getNext();
        auto b = getNext();

        return BinaryPredicate::create(std::move(calculator), std::move(a), std::move(b));
    }

    std::unique_ptr<IPredicate> StreamPredicateScanner::getMultiple() const
    {
        StreamPredicateCalculatorScanner scanner(stream_);
        auto calculator = scanner.getMultiple();

        return MultiplePredicate::create(std::move(calculator), getVector());
    }
}

