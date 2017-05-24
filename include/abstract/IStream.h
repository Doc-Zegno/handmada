//
// Created by syzegno on 18.05.17.
//

#ifndef EQUEUE_V2_ISTREAM_H
#define EQUEUE_V2_ISTREAM_H


#include <cstddef>


namespace Handmada {
    enum class Whence {
        SET,
        CUR,
        END,
    };


    /**
     * Multipurpose interface, originally was introduced to supply
     * a necessary level of abstraction for serializers.
     * Two main implementors are UnixFileStream and DynamicBufferStream
     */
    class IStream
    {
    public:
        /**
         * Retrieves a byte sequence of desirable size from underlying stream buffer.
         * Client-side classes should assume that this method performs necessary checks
         * during operation and thus may throw
         * @param buffer destination buffer
         * @param size length of byte sequence to be retrieved
         */
        virtual void get(char* buffer, size_t size) = 0;

        /**
         * Writes a byte sequence to underlying stream buffer.
         * Client-side classes should assume that this method performs necessary checks
         * during operation and thus may throw
         * @param buffer buffer with input data
         * @param size buffer's length
         */
        virtual void put(const char* buffer, size_t size) = 0;

        /**
         * Reset the current position of stream's pointer.
         * Originally was introduced to take advantage of using Unix function "lseek".
         * Ironically enough, it is primarily used for DynamicBufferStream
         * @param offset shift that will be added to the current position of pointer
         * @param whence introduced for compatibility with "lseek" function
         */
        virtual void seek(int offset, Whence whence = Whence::SET) = 0;

        virtual ~IStream() { }
    };
}


#endif //EQUEUE_V2_ISTREAM_H
