//
// Created by syzegno on 18.05.17.
//


#include "platform-dependent-v2/UnixFileStream.h"

#include <unistd.h>
#include <cstring>


namespace Handmada {
    UnixFileStream::UnixFileStream(int fd)
            : fd_(fd)
    { }



    void UnixFileStream::get(char* buffer, size_t size)
    {
        auto haveRead = read(fd_, buffer, size);
        check(haveRead, size);
    }


    void UnixFileStream::put(const char* buffer, size_t size)
    {
        auto haveWritten = write(fd_, buffer, size);
        check(haveWritten, size);
    }


    void UnixFileStream::check(ssize_t actual, size_t expected)
    {
        if (actual < 0) {
            throw UnixFileStreamException(std::strerror(errno));
        } else if (static_cast<size_t>(actual) < expected) {
            throw UnixFileStreamException("bytes were definitely lost");
        }
    }


    void UnixFileStream::seek(int offset, Whence whence)
    {
        int seekWhence;
        switch (whence) {
        case Whence::SET:
            seekWhence = SEEK_SET;
            break;
        case Whence::CUR:
            seekWhence = SEEK_CUR;
            break;
        case Whence::END:
            seekWhence = SEEK_END;
            break;
        }

        lseek(fd_, offset, seekWhence);
    }


    int UnixFileStream::fd() const
    {
        return fd_;
    }



    UnixFileStreamException::UnixFileStreamException(const std::string& info)
            : runtime_error(info)
    { }
}
