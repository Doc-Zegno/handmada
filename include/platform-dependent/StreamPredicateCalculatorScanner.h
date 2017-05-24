//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_STREAMPREDICATECALCULATORSCANNER_H
#define EQUEUE_V2_STREAMPREDICATECALCULATORSCANNER_H


#include <stdexcept>
#include <memory>

#include "PredicateCalculators.h"
#include "IStream.h"


namespace Handmada {
    class StreamPredicateCalculatorScannerException : public std::runtime_error
    {
    public:
        StreamPredicateCalculatorScannerException(const std::string& info);
    };


    class StreamPredicateCalculatorScanner
    {
    private:
        IStream& stream_;

    public:
        StreamPredicateCalculatorScanner(IStream& stream);

        std::unique_ptr<IBinaryCalculator> getBinary() const;
        std::unique_ptr<IMultipleCalculator> getMultiple() const;
    };
}


#endif //EQUEUE_V2_STREAMPREDICATECALCULATORSCANNER_H
