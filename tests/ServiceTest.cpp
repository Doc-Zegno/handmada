//
// Created by syzegno on 24.04.17.
//


#include <sstream>

#include <gtest/gtest.h>

#include "Service.h"


using namespace Handmada;


TEST(Service, AddUser)
{
    Service service("lawyer", "knows laws", 0);
    ASSERT_TRUE(service.addUser(VALID_USER_ID, true));
    ASSERT_FALSE(service.addUser(VALID_USER_ID, true));
    ASSERT_FALSE(service.addUser(VALID_USER_ID, false));
    ASSERT_FALSE(service.isQueueEmpty());
    ASSERT_EQ(service.usersAmount(), 1U);
}

TEST(Service, PrintQueue)
{
    Service service("doctor", "every good team needs good healer", 0);
    ASSERT_TRUE(service.addUser(1, true));
    ASSERT_TRUE(service.addUser(2, false));
    ASSERT_TRUE(service.addUser(3, true));

    std::ostringstream sout;
    service.printQueue(sout);
    const char* expected = "#1: 1\n#2: 3\n#3: 2\n";
    ASSERT_STREQ(sout.str().c_str(), expected);
}

TEST(Service, AddSpecialist_PrintSpecialists)
{
    Service service("coder", "is not a programmer", 0);
    Specialist coder1("Vasya");
    Specialist coder2("Petya");
    ASSERT_TRUE(service.addSpecialist(1, &coder1));
    ASSERT_TRUE(service.addSpecialist(2, &coder2));
    ASSERT_FALSE(service.addSpecialist(1, &coder1));

    std::ostringstream sout;
    service.printSpecialists(sout);
    const char* expected1 = "ID: 1\nVasya\n\nID: 2\nPetya\n\n";
    const char* expected2 = "ID: 2\nPetya\n\nID: 1\nVasya\n\n";

    std::string actual = sout.str();
    ASSERT_TRUE(actual == expected1 || actual == expected2);
}

