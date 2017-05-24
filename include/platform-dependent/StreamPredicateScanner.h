//
// Created by syzegno on 08.05.17.
//

#ifndef EQUEUE_V2_FILEPREDICATESCANNER_H
#define EQUEUE_V2_FILEPREDICATESCANNER_H


#include <memory>
#include <stdexcept>

#include "IPredicate.h"
#include "IStream.h"


namespace Handmada {
    class StreamPredicateScannerException : public std::runtime_error
    {
    public:
        StreamPredicateScannerException(const std::string& info);
    };


    class StreamPredicateScanner
    {
    private:
        IStream& stream_;


        std::unique_ptr<IPredicate> getNot() const;
        std::unique_ptr<IPredicate> getBinary() const;
        std::unique_ptr<IPredicate> getMultiple() const;
        std::unique_ptr<IPredicate> getComparison() const;

        std::vector<std::unique_ptr<IPredicate>> getVector() const;

    public:
        StreamPredicateScanner(IStream& stream);

        std::unique_ptr<IPredicate> getNext() const;
    };
}


#endif //EQUEUE_V2_FILEPREDICATESCANNER_H
