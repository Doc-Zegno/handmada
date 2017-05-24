//
// Created by syzegno on 20.05.17.
//


#include <gtest/gtest.h>

#include "TestFrontend.h"
#include "SimpleController.h"
#include "Responses.h"

using namespace Handmada;


TEST(TestFrontend, RegisterUserRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    auto response = frontend.acceptRequest(RegisterUserRequest("user"));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userId;
    ASSERT_NO_THROW(userId = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userId));
    ASSERT_TRUE(controller.containsUserId(userId));

    response = frontend.acceptRequest(RegisterUserRequest("user"));
    ASSERT_EQ(response->code(), OpCode::ALREADY_REGISTERED);
}


TEST(TestFrontend, SignInRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    auto response = frontend.acceptRequest(SignInRequest("user"));
    ASSERT_EQ(response->code(), OpCode::NOT_REGISTERED);
    response = frontend.acceptRequest(RegisterUserRequest("user"));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userId;
    ASSERT_NO_THROW(userId = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userId));
    ASSERT_FALSE(controller.isUserIdActive(userId));

    response = frontend.acceptRequest(SignInRequest("user"));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userId2;
    ASSERT_NO_THROW(userId2 = dynamic_cast<SignInResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userId2));
    ASSERT_EQ(userId, userId2);
    ASSERT_TRUE(controller.isUserIdActive(userId));

    response = frontend.acceptRequest(SignInRequest("user"));
    ASSERT_EQ(response->code(), OpCode::ALREADY_SIGN_IN);
}


TEST(TestFrontend, SignOutRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    auto response = frontend.acceptRequest(SignOutRequest(UserId(0)));
    ASSERT_EQ(response->code(), OpCode::ALREADY_SIGN_OUT);
    response = frontend.acceptRequest(RegisterUserRequest("user"));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    response = frontend.acceptRequest(SignOutRequest(UserId(0)));
    ASSERT_EQ(response->code(), OpCode::ALREADY_SIGN_OUT);
    response = frontend.acceptRequest(SignInRequest("user"));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    response = frontend.acceptRequest(SignOutRequest(UserId(0)));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ASSERT_FALSE(controller.isUserIdActive(UserId(0)));
}


TEST(TestFrontend, AddServiceRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    AddServiceRequest request("coder", "not a programmer");
    auto response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ServiceId serviceId;
    ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
    ASSERT_TRUE(isServiceIdValid(serviceId));
    ASSERT_TRUE(controller.containsServiceId(serviceId));
    ASSERT_STREQ(controller.getServiceById(serviceId).name.c_str(), "coder");
    ASSERT_STREQ(controller.getServiceById(serviceId).description.c_str(), "not a programmer");

    response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::SERVICE_EXISTS);
}


TEST(TestFrontend, AddSpecialistRequest)
{
    SimpleController controller;
    BasicFrontend frontend(&controller);

    AddSpecialistRequest request("Alberto Syvsow");
    auto response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    SpecialistId specialistId;
    ASSERT_NO_THROW(specialistId = dynamic_cast<AddSpecialistResponse&>(*response).specialistId());
    ASSERT_TRUE(isSpecialistIdValid(specialistId));
    ASSERT_TRUE(controller.containsSpecialist("Alberto Syvsow"));

    response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::SPECIALIST_EXISTS);
}

