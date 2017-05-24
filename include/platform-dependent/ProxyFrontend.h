//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_PROXYFRONTEND_H
#define EQUEUE_V2_PROXYFRONTEND_H


#include <stdexcept>
#include <cstdint>

#include "IFrontend.h"
#include "UnixFileStream.h"
#include "DynamicBufferStream.h"


namespace Handmada {
    class ProxyFrontendException : public std::runtime_error
    {
    public:
        ProxyFrontendException(const std::string& info);
    };


    class ProxyFrontend : public IFrontend
    {
    private:
        UnixFileStream fileStream_;
        DynamicBufferStream bufferStream_;

    public:
        ProxyFrontend(const char* portName, uint16_t portNo);
        ~ProxyFrontend();

        virtual std::unique_ptr<IResponse> acceptRequest(const IRequest& request) override;
    };
}


#endif //EQUEUE_V2_PROXYFRONTEND_H
