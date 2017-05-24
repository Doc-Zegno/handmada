//
// Created by syzegno on 18.05.17.
//


#include "DynamicBufferStream.h"

#include <cstring>


namespace Handmada {
    DynamicBufferStream::DynamicBufferStream(size_t initialCapacity)
            : capacity_(initialCapacity)
    {
        begin_ = new char[initialCapacity];
        ptr_ = begin_;
    }


    DynamicBufferStream::~DynamicBufferStream()
    {
        delete[] begin_;
    }


    void DynamicBufferStream::get(char* buffer, size_t size)
    {
        check(size);
        std::memcpy(buffer, ptr_, size);
        ptr_ += size;
    }


    void DynamicBufferStream::put(const char* buffer, size_t size)
    {
        checkAndResize(size);
        std::memcpy(ptr_, buffer, size);
        ptr_ += size;
    }


    void DynamicBufferStream::seek(int offset, Whence whence)
    {
        switch (whence) {
        case Whence::SET:
            ptr_ = begin_;
            break;
        case Whence::END:
            ptr_ = begin_ + capacity_;
            break;
        default:
            break;
        }

        ptr_ += offset;
        size_t diff = ptr_ - begin_;
        if (diff > capacity_ || ptr_ < begin_) {
            throw DynamicBufferStreamException("out of range");
        }
    }


    void DynamicBufferStream::check(size_t size) const
    {
        size_t diff = ptr_ - begin_;
        if (diff + size > capacity_) {
            throw DynamicBufferStreamException("out of range");
        }
    }


    void DynamicBufferStream::checkAndResize(size_t size)
    {
        size_t diff = ptr_ - begin_;
        if (diff + size > capacity_) {
            auto newCapacity = (capacity_ > size) ? capacity_ * 2 : capacity_ + size;
            auto buf = new char[newCapacity];
            std::memcpy(buf, begin_, diff);
            delete[] begin_;
            begin_ = buf;
            ptr_ = buf + diff;
            capacity_ = newCapacity;
        }
    }


    char* DynamicBufferStream::buffer() const
    {
        return begin_;
    }


    size_t DynamicBufferStream::position() const
    {
        return ptr_ - begin_;
    }


    void DynamicBufferStream::reserve(size_t size)
    {
        if (capacity_ < size) {
            delete[] begin_;
            begin_ = new char[size];
            capacity_ = size;
        }
        ptr_ = begin_;
    }



    DynamicBufferStreamException::DynamicBufferStreamException(const std::string& info)
            : runtime_error(info)
    { }
}