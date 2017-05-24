//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_STREAMREQUESTSCANNER_H
#define EQUEUE_V2_STREAMREQUESTSCANNER_H


#include <memory>
#include <stdexcept>

#include "IRequest.h"
#include "IStream.h"


namespace Handmada {
    class StreamRequestScannerException : public std::runtime_error
    {
    public:
        StreamRequestScannerException(const std::string& info);
    };


    class StreamRequestScanner
    {
    private:
        IStream& stream_;

    public:
        StreamRequestScanner(IStream& stream);

        std::unique_ptr<IRequest> getNext() const;
    };
}


#endif //EQUEUE_V2_STREAMREQUESTSCANNER_H
