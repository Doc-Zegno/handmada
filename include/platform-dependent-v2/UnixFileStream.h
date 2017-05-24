//
// Created by syzegno on 18.05.17.
//

#ifndef EQUEUE_V2_UNIXFILESTREAM_H
#define EQUEUE_V2_UNIXFILESTREAM_H


#include <stdexcept>

#include "IStream.h"


namespace Handmada {
    /**
     * Handles input/output to Unix files
     */
    class UnixFileStream : public IStream
    {
    private:
        int fd_;

        void check(ssize_t actual, size_t expected);

    public:
        UnixFileStream(int fd = 0);

        virtual void get(char* buffer, size_t size) override;
        virtual void put(const char* buffer, size_t size) override;
        virtual void seek(int offset, Whence whence) override;

        int fd() const;
    };


    class UnixFileStreamException : public std::runtime_error
    {
    public:
        UnixFileStreamException(const std::string& info);
    };
}


#endif //EQUEUE_V2_UNIXFILESTREAM_H
