//
// Created by syzegno on 18.05.17.
//

#ifndef EQUEUE_V2_DYNAMICBUFFERSTREAM_H
#define EQUEUE_V2_DYNAMICBUFFERSTREAM_H


#include <stdexcept>

#include "IStream.h"


namespace Handmada {
    /**
     * Provides client-side classes with automatically resizing buffer
     * that can be treated as input/output stream.
     * Useful for building requests that can be transferred over network
     */
    class DynamicBufferStream : public IStream
    {
    private:
        char* begin_;
        char* ptr_;
        size_t capacity_;

        void check(size_t size) const;
        void checkAndResize(size_t size);

    public:
        DynamicBufferStream(size_t initialCapacity = 1024);
        DynamicBufferStream(const DynamicBufferStream& stream) = delete;
        DynamicBufferStream(DynamicBufferStream&& stream) = delete;
        ~DynamicBufferStream();

        virtual void get(char* buffer, size_t size) override;
        virtual void put(const char* buffer, size_t size) override;
        virtual void seek(int offset, Whence whence = Whence::SET) override;

        /**
         * Can be used to get built request
         * @return a pointer to the beginning of internal buffer
         */
        char* buffer() const;

        /**
         * Effectively returns the current size of request
         * @return the index of character in the internal buffer that will be used
         * by the next "get"/"put" call
         */
        size_t position() const;

        /**
         * Resets internal pointer to the beginning of the underlying buffer
         * and reallocates memory if buffer capacity is not sufficient
         * @param size minimal buffer capacity required
         */
        void reserve(size_t size);
    };


    class DynamicBufferStreamException : public std::runtime_error
    {
    public:
        DynamicBufferStreamException(const std::string& info);
    };
}


#endif //EQUEUE_V2_DYNAMICBUFFERSTREAM_H
