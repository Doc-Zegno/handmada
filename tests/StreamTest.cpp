//
// Created by syzegno on 19.05.17.
//


#include <gtest/gtest.h>

#include <fcntl.h>

#include "UnixFileStream.h"
#include "DynamicBufferStream.h"

using namespace Handmada;


TEST(Stream, UnixFileStream)
{
    int fd = open("tmp1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
    UnixFileStream stream(fd);
    char expected[] = "Sample Text\nSerious Arguments";
    ASSERT_NO_THROW(stream.put(expected, sizeof(expected)));
    char actual[sizeof(expected)];
    ASSERT_NO_THROW(stream.seek(0, Whence::SET));
    ASSERT_NO_THROW(stream.get(actual, sizeof(actual)));
    ASSERT_STREQ(expected, actual);
    close(fd);
    unlink("tmp1.txt");
}


TEST(Stream, UnixFileStreamFailure)
{
    int fd = open("tmp1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
    UnixFileStream stream(fd);
    char buf[137];
    ASSERT_THROW(stream.get(buf, sizeof(buf)), UnixFileStreamException);
    close(fd);
    unlink("tmp1.txt");
}


TEST(Stream, DynamicBufferStream)
{
    DynamicBufferStream stream(10);
    char lipsum[] = "Lorem ipsum dolor sit amet";

    const int NUM = 10000;
    for (int i = 0; i < NUM; i++) {
        ASSERT_NO_THROW(stream.put(lipsum, sizeof(lipsum)));
    }
    ASSERT_EQ(stream.position(), NUM * sizeof(lipsum));

    ASSERT_NO_THROW(stream.seek(0));
    ASSERT_STREQ(stream.buffer(), lipsum);
}


TEST(Stream, DynamicBufferStreamFailure)
{
    DynamicBufferStream stream(10);
    char buf[137];
    ASSERT_THROW(stream.get(buf, sizeof(buf)), DynamicBufferStreamException);
}

