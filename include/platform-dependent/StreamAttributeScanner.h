//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_FILEATTRIBUTESCANNER_H
#define EQUEUE_V2_FILEATTRIBUTESCANNER_H


#include <memory>
#include <stdexcept>

#include "MetaNumber.h"
#include "Attributes.h"
#include "IStream.h"


namespace Handmada {
    class StreamAttributeScannerException : public std::runtime_error
    {
    public:
        StreamAttributeScannerException(const std::string& info);
    };


    class StreamAttributeScanner
    {
    private:
        IStream& stream_;

    public:
        StreamAttributeScanner(IStream& stream);

        std::unique_ptr<Handmada::IAttribute> getNext() const;
    };
}


#endif //EQUEUE_V2_FILEATTRIBUTESCANNER_H
