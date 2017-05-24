//
// Created by syzegno on 24.04.17.
//


#include <sstream>

#include <gtest/gtest.h>

#include "Service.h"
#include "BasicFrontend.h"
#include "Types.h"
#include "Specialist.h"
#include "IInfoContainer.h"


using namespace Handmada;


class Container : public IInfoContainer
{
public:
    std::vector<std::tuple<UserId, ServiceId, Specialist*>> infoVec;
    virtual void addInfo(UserId userId, ServiceId serviceId, Specialist* specialist) override
    {
        infoVec.push_back(std::make_tuple(userId, serviceId, specialist));
    }
};


TEST(Service, AddUser)
{
    Service service("lawyer", "knows laws", 0);
    ASSERT_TRUE(service.addUser(VALID_USER_ID, true));
    ASSERT_FALSE(service.addUser(VALID_USER_ID, true));
    ASSERT_FALSE(service.addUser(VALID_USER_ID, false));
    ASSERT_FALSE(service.isQueueEmpty());
    ASSERT_EQ(service.usersAmount(), 1);
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

//TODO: service uses hash table now, so this test should be rewritten
/*TEST(Service, RunService)
{
    Service service("hard worker", "working hard", 0);
    Specialist worker1("Earnest Ernest");
    Specialist worker2("Serious Sirius");
    Container container;
    ASSERT_TRUE(service.addSpecialist(1, &worker1));
    ASSERT_TRUE(service.addSpecialist(2, &worker2));

    ASSERT_TRUE(service.addUser(0, true));
    ASSERT_TRUE(service.addUser(3, false));
    ASSERT_TRUE(service.addUser(1, true));
    ASSERT_TRUE(service.addUser(4, false));
    ASSERT_TRUE(service.addUser(2, true));

    Container expected;
    UserId id = 0;
    ServiceId serviceId = 0;
    expected.addInfo(id, serviceId, &worker1);
    id = 1;
    expected.addInfo(id, serviceId, &worker2);
    id = 2;
    expected.addInfo(id, serviceId, &worker1);
    id = 3;
    expected.addInfo(id, serviceId, &worker2);
    id = 4;
    expected.addInfo(id, serviceId, &worker1);

    service.run(container);
    ASSERT_FALSE(service.isQueueEmpty());
    service.run(container);
    ASSERT_FALSE(service.isQueueEmpty());
    service.run(container);
    ASSERT_TRUE(service.isQueueEmpty());
    service.run(container);

    std::ostringstream souts[2];
    Container* containers[] = { &container, &expected };
    for (int i = 0; i < 2; i++) {
        for (const auto& tuple : containers[i]->infoVec) {
            souts[i] << std::get<0>(tuple)
                << "; " << std::get<1>(tuple)
                << "; " << std::get<2>(tuple)
                << std::endl;
        }
    }

    ASSERT_STREQ(souts[0].str().c_str(), souts[1].str().c_str());
}*/

