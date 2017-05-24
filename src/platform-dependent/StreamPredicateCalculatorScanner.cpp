//
// Created by syzegno on 19.05.17.
//


#include "StreamPredicateCalculatorScanner.h"
#include "MetaNumber.h"
#include "Serializer.h"


namespace Handmada {
    StreamPredicateCalculatorScannerException::StreamPredicateCalculatorScannerException(
            const std::string& info
    ) : runtime_error(info)
    { }



    StreamPredicateCalculatorScanner::StreamPredicateCalculatorScanner(IStream& stream)
            : stream_(stream)
    { }


    std::unique_ptr<IBinaryCalculator> StreamPredicateCalculatorScanner::getBinary() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);
        if (meta == MetaNumber::OR_BINARY_CALCULATOR) {
            return OrBinaryCalculator::create();
        } else if (meta == MetaNumber::AND_BINARY_CALCULATOR){
            return AndBinaryCalculator::create();
        } else {
            throw StreamPredicateCalculatorScannerException("unknown meta");
        }
    }


    std::unique_ptr<IMultipleCalculator> StreamPredicateCalculatorScanner::getMultiple() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);
        if (meta == MetaNumber::OR_MULTIPLE_CALCULATOR) {
            return OrMultipleCalculator::create();
        } else if (meta == MetaNumber::AND_MULTIPLE_CALCULATOR){
            return AndMultipleCalculator::create();
        } else {
            throw StreamPredicateCalculatorScannerException("unknown meta");
        }
    }
}
