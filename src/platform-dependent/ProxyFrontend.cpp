//
// Created by syzegno on 17.05.17.
//


#include "ProxyFrontend.h"

#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
#include <cstring>

#include "Serializer.h"


namespace Handmada {
    ProxyFrontendException::ProxyFrontendException(const std::string& info)
            : runtime_error(info)
    { }


    ProxyFrontend::ProxyFrontend(const char* portName, uint16_t portNo)
    {
        struct sockaddr_in serverAddress;
        struct hostent *server;

        int sockFd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockFd < 0) {
            throw ProxyFrontendException(strerror(errno));
        }

        server = gethostbyname(portName);
        if (server == NULL) {
            throw ProxyFrontendException("no such host");
        }

        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        bcopy(server->h_addr, &serverAddress.sin_addr.s_addr, static_cast<size_t>(server->h_length));
        serverAddress.sin_port = htons(portNo);

        if (connect(sockFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            throw ProxyFrontendException(strerror(errno));
        }
        fileStream_ = UnixFileStream(sockFd);
    }


    ProxyFrontend::~ProxyFrontend()
    {
        close(fileStream_.fd());
    }


    std::unique_ptr<IResponse> ProxyFrontend::acceptRequest(const IRequest& request)
    {
        bufferStream_.seek(0);
        size_t size = 0;
        Serializer::put(bufferStream_, size);
        Serializer::put(bufferStream_, request);
        size = bufferStream_.position();
        bufferStream_.seek(0);
        Serializer::put(bufferStream_, size - sizeof(size));
        fileStream_.put(bufferStream_.buffer(), size);

        Serializer::get(fileStream_, size);
        bufferStream_.reserve(size);
        fileStream_.get(bufferStream_.buffer(), size);

        std::unique_ptr<IResponse> response;
        Serializer::get(bufferStream_, response);
        return std::move(response);
    }
}
