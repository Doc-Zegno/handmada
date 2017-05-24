//
// Created by syzegno on 15.05.17.
//


#include <gtest/gtest.h>

#include "TestFrontend.h"
#include "SimpleController.h"
#include "Predicates.h"
#include "ConcreteRequirements.h"
#include "SnapShooter.h"
#include "Responses.h"

using namespace Handmada;


TEST(TestFrontend, GetMessageResponse)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    GetMessageRequest getMessageRequest(UserId(0));
    auto response = frontend.acceptRequest(getMessageRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_USER);

    RegisterUserRequest registerUserRequest("User");
    response = frontend.acceptRequest(registerUserRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userId;
    ASSERT_NO_THROW(userId = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userId));

    response = frontend.acceptRequest(getMessageRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const std::vector<Message>* messages;
    ASSERT_NO_THROW(messages = &dynamic_cast<GetMessageResponse&>(*response).messages());
    ASSERT_EQ(messages->size(), 0U);

    std::string info[][3] = {
            { "Make debugger", "Serious business", "Alberto Syvsow" },
            { "Code academic", "Keeps waaagh", "Otto Lille" },
            { "Ubuntu name designer", "All good things start with the same letter", "Serious Sirius" },
    };

    for (int i = 0; i < 3; i++) {
        AddServiceRequest addServiceRequest(info[i][0], info[i][1]);
        response = frontend.acceptRequest(addServiceRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        ServiceId serviceId;
        ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
        ASSERT_TRUE(isServiceIdValid(serviceId));

        AddSpecialistRequest addSpecialistRequest(info[i][2]);
        response = frontend.acceptRequest(addSpecialistRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        SpecialistId specialistId;
        ASSERT_NO_THROW(specialistId = dynamic_cast<AddSpecialistResponse&>(*response).specialistId());
        ASSERT_TRUE(isSpecialistIdValid(specialistId));

        AttachSpecialistRequest attachSpecialistRequest(specialistId, serviceId);
        response = frontend.acceptRequest(attachSpecialistRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);

        MakeAppointmentRequest makeAppointmentRequest(userId, serviceId);
        response = frontend.acceptRequest(makeAppointmentRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        bool hasPriority;
        ASSERT_NO_THROW(hasPriority = dynamic_cast<MakeAppointmentResponse&>(*response).hasPriority());
        ASSERT_TRUE(hasPriority);

        auto& service = controller.getServiceById(serviceId);
        ASSERT_EQ(service.usersAmount(), 1U);
        frontend.runServices();
        frontend.runServices();
        ASSERT_EQ(service.usersAmount(), 0U);
    }

    response = frontend.acceptRequest(getMessageRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ASSERT_NO_THROW(messages = &dynamic_cast<GetMessageResponse&>(*response).messages());
    ASSERT_EQ(messages->size(), 3U);
    for (int i = 0; i < 3; i++) {
        auto& message = (*messages)[i];
        ASSERT_STREQ(message.from().c_str(), info[2 - i][2].c_str());
        ASSERT_STREQ(message.theme().c_str(), info[2 - i][0].c_str());
    }
}


TEST(TestFrontend, GetServiceDescriptorRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    std::map<std::string, std::string> info = {
            { "Make debugger", "Serious business" },
            { "Code academic", "Keeps waaagh" },
            { "Ubuntu name designer", "All good things start with the same letter" },
            { "Moral support", "We call it MORPOD" },
    };

    GetServiceDescriptorRequest getServiceDescriptorRequest;
    auto response = frontend.acceptRequest(getServiceDescriptorRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const std::vector<ServiceDescriptor>* descriptors;
    ASSERT_NO_THROW(descriptors = &dynamic_cast<GetServiceDescriptorResponse&>(*response).descriptors());
    ASSERT_TRUE(descriptors->empty());

    for (auto& pair : info) {
        AddServiceRequest addServiceRequest(pair.first, pair.second);
        response = frontend.acceptRequest(addServiceRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
    }

    response = frontend.acceptRequest(getServiceDescriptorRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ASSERT_NO_THROW(descriptors = &dynamic_cast<GetServiceDescriptorResponse&>(*response).descriptors());
    ASSERT_EQ(descriptors->size(), info.size());

    for (auto& descriptor : *descriptors) {
        auto iterator = info.find(descriptor.name());
        ASSERT_TRUE(iterator != info.end());
        ASSERT_STREQ(descriptor.description().c_str(), iterator->second.c_str());
        info.erase(iterator);
    }
}


TEST(TestFrontend, GetSpecialistDescriptorRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    GetSpecialistDescriptorRequest getSpecialistDescriptorRequest;
    auto response = frontend.acceptRequest(getSpecialistDescriptorRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const std::vector<SpecialistDescriptor>* descriptors;
    ASSERT_NO_THROW(descriptors = &dynamic_cast<GetSpecialistDescriptorResponse&>(*response).descriptors());
    ASSERT_TRUE(descriptors->empty());

    getSpecialistDescriptorRequest = GetSpecialistDescriptorRequest(ServiceId(0));
    response = frontend.acceptRequest(getSpecialistDescriptorRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SERVICE);

    std::map<std::string, SpecialistId> specialists = {
            { "Earnest Ernest", INVALID_SPECIALIST_ID },
            { "Serious Sirius", INVALID_SPECIALIST_ID },
            { "Even Evan", INVALID_SPECIALIST_ID },
            { "Alberto Syvsow", INVALID_SPECIALIST_ID },
            { "Otto Lille", INVALID_SPECIALIST_ID },
            { "James Maxwell", INVALID_SPECIALIST_ID },
            { "Jean Baptiste Joseph Fourier", INVALID_SPECIALIST_ID },
    };

    decltype(specialists) groups[3];
    ServiceId serviceIds[3];
    serviceIds[0] = INVALID_SERVICE_ID;

    std::map<std::string, std::string> services = {
            { "Alpha Testers", "With every line of code comes honor" },
            { "Beta Testers", "With honor comes redemption" },
    };

    int i = 1;
    for (auto& pair : services) {
        AddServiceRequest addServiceRequest(pair.first, pair.second);
        response = frontend.acceptRequest(addServiceRequest);
        ServiceId serviceId;
        ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
        ASSERT_TRUE(isServiceIdValid(serviceId));
        serviceIds[i] = serviceId;
        i++;
    }

    srand(time(nullptr));
    for (auto& pair : specialists) {
        AddSpecialistRequest addSpecialistRequest(pair.first);
        response = frontend.acceptRequest(addSpecialistRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        SpecialistId specialistId;
        ASSERT_NO_THROW(specialistId = dynamic_cast<AddSpecialistResponse&>(*response).specialistId());
        ASSERT_TRUE(isSpecialistIdValid(specialistId));
        pair.second = specialistId;

        int choice = rand()%3;
        bool attach[2] = { 0 };
        if (choice == 0) {
            attach[0] = attach[1] = true;
        } else if (choice == 1) {
            attach[0] = true;
        } else {
            attach[1] = true;
        }

        for (int j = 0; j < 2; j++) {
            if (attach[j]) {
                AttachSpecialistRequest attachSpecialistRequest(specialistId, serviceIds[j + 1]);
                response = frontend.acceptRequest(attachSpecialistRequest);
                ASSERT_EQ(response->code(), OpCode::SUCCESS);
                groups[j + 1].insert(std::make_pair(pair.first, specialistId));
            }
        }
    }
    groups[0] = specialists;


    for (int i = 0; i < 3; i++) {
        getSpecialistDescriptorRequest = GetSpecialistDescriptorRequest(serviceIds[i]);
        response = frontend.acceptRequest(getSpecialistDescriptorRequest);
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        ASSERT_NO_THROW(descriptors = &dynamic_cast<GetSpecialistDescriptorResponse&>(*response).descriptors());
        ASSERT_EQ(descriptors->size(), groups[i].size());

        decltype(specialists) copy;
        for (auto& descriptor : *descriptors) {
            copy.insert(std::make_pair(descriptor.name(), descriptor.id()));
        }
        ASSERT_TRUE(copy == groups[i]);
    }
}


TEST(TestFrontend, GetUserAttributeRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    GetUserAttributeRequest getUserAttributeRequest(UserId(0));
    auto response = frontend.acceptRequest(getUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_USER);

    RegisterUserRequest registerUserRequest("User");
    response = frontend.acceptRequest(registerUserRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userId;
    ASSERT_NO_THROW(userId = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userId));

    getUserAttributeRequest = GetUserAttributeRequest(userId);
    response = frontend.acceptRequest(getUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const PolyVector<IAttribute>* attributes;
    ASSERT_NO_THROW(attributes = &dynamic_cast<GetUserAttributeResponse&>(*response).attributes());
    ASSERT_EQ(attributes->size(), 1U);
    ASSERT_STREQ((*attributes)[0]->name().c_str(), "login");

    PolyVector<IAttribute> added;
    added.push_back(makeAttribute("country", "DE"));
    added.push_back(makeAttribute("age", 37));
    AddUserAttributeRequest addUserAttributeRequest(userId, std::move(added));
    response = frontend.acceptRequest(addUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    response = frontend.acceptRequest(getUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ASSERT_NO_THROW(attributes = &dynamic_cast<GetUserAttributeResponse&>(*response).attributes());
    ASSERT_EQ(attributes->size(), 3U);

    std::string names[] = { "login", "country", "age" };
    for (auto& name : names) {
        bool hasAttribute = false;
        for (auto& attribute : *attributes) {
            if (attribute->name() == name) {
                hasAttribute = true;
            }
        }
        ASSERT_TRUE(hasAttribute);
    }
}


TEST(TestFrontend, GetUserDescriptorRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    GetUserDescriptorRequest getUserDescriptorRequest(ServiceId(0));
    auto response = frontend.acceptRequest(getUserDescriptorRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SERVICE);

    AddServiceRequest addServiceRequest("Sample Text", "Serious Arguments");
    response = frontend.acceptRequest(addServiceRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ServiceId serviceId;
    ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
    ASSERT_TRUE(isServiceIdValid(serviceId));

    auto predicate = ComparisonPredicate::create(
            ComparisonFlag::EQUAL,
            makeAttribute("login", "UserA")
    );
    PolyVector<IRequirement> requirements;
    requirements.push_back(StringRequirement::create("login"));
    AddPriorityRuleRequest addPriorityRuleRequest(serviceId, std::move(predicate), std::move(requirements));
    response = frontend.acceptRequest(addPriorityRuleRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    RegisterUserRequest registerUserRequest("UserA");
    response = frontend.acceptRequest(registerUserRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userA;
    ASSERT_NO_THROW(userA = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userA));

    registerUserRequest = RegisterUserRequest("UserB");
    response = frontend.acceptRequest(registerUserRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userB;
    ASSERT_NO_THROW(userB = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userB));

    response = frontend.acceptRequest(MakeAppointmentRequest(userA, serviceId));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    response = frontend.acceptRequest(MakeAppointmentRequest(userB, serviceId));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    response = frontend.acceptRequest(getUserDescriptorRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const std::vector<UserDescriptor>* descriptors;
    ASSERT_NO_THROW(descriptors = &dynamic_cast<GetUserDescriptorResponse&>(*response).descriptors());
    ASSERT_EQ(descriptors->size(), 2U);

    UserDescriptor expected[] = {
            UserDescriptor(userA, "UserA", true),
            UserDescriptor(userB, "UserB", false)
    };
    for (int i = 0; i < 2; i++) {
        ASSERT_EQ(expected[i].id(), (*descriptors)[i].id());
        ASSERT_STREQ(expected[i].login().c_str(), (*descriptors)[i].login().c_str());
        ASSERT_EQ(expected[i].hasPriority(), (*descriptors)[i].hasPriority());
    }
}
