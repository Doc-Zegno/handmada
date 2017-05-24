//
// Created by syzegno on 14.05.17.
//


#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "TestFrontend.h"
#include "SimpleController.h"
#include "Predicates.h"
#include "ConcreteRequirements.h"
#include "SnapShooter.h"
#include "Responses.h"
#include "PredicateCalculators.h"
#include "PredicatePrinter.h"

using namespace Handmada;


TEST(TestFrontend, MakeAppointmentRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    MakeAppointmentRequest makeAppointmentRequest(UserId(0), ServiceId(0));
    auto response = frontend.acceptRequest(makeAppointmentRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_USER);

    RegisterUserRequest registerUserRequest("Maxwell");
    response = frontend.acceptRequest(registerUserRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId maxwell;
    ASSERT_NO_THROW(maxwell = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(maxwell));

    makeAppointmentRequest = MakeAppointmentRequest(maxwell, ServiceId(0));
    response = frontend.acceptRequest(makeAppointmentRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SERVICE);

    AddServiceRequest addServiceRequest("Test Service", "Specially for Maxwell");
    response = frontend.acceptRequest(addServiceRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ServiceId serviceId;
    ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
    ASSERT_TRUE(isServiceIdValid(serviceId));

    auto predicate = ComparisonPredicate::create(
            ComparisonFlag::GREATER,
            makeAttribute("money", 100000)
    );
    PolyVector<IRequirement> requirements;
    requirements.push_back(NumberRequirement::create("money"));
    AddPriorityRuleRequest addPriorityRuleRequest(
            serviceId, std::move(predicate), std::move(requirements)
    );
    response = frontend.acceptRequest(addPriorityRuleRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    predicate = ComparisonPredicate::create(
            ComparisonFlag::EQUAL,
            makeAttribute("country", "random")
    );
    requirements.clear();
    requirements.push_back(StringRequirement::create("country"));
    addPriorityRuleRequest = AddPriorityRuleRequest(
            serviceId, std::move(predicate), std::move(requirements)
    );
    response = frontend.acceptRequest(addPriorityRuleRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    predicate = ComparisonPredicate::create(
            ComparisonFlag::EQUAL,
            makeAttribute("is maxwell", true)
    );
    requirements.clear();
    requirements.push_back(BooleanRequirement::create("is maxwell", "Are you Maxwell?"));
    addPriorityRuleRequest = AddPriorityRuleRequest(
            serviceId, std::move(predicate), std::move(requirements)
    );
    response = frontend.acceptRequest(addPriorityRuleRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    PolyVector<IAttribute> attributes;
    attributes.push_back(makeAttribute("money", 100001));
    AddUserAttributeRequest addUserAttributeRequest(maxwell, std::move(attributes));
    response = frontend.acceptRequest(addUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    makeAppointmentRequest = MakeAppointmentRequest(maxwell, serviceId);
    response = frontend.acceptRequest(makeAppointmentRequest);
    ASSERT_EQ(response->code(), OpCode::MISSING_ATTRIBUTES);
    const PolyVector<IRequirement>* missing;
    ASSERT_NO_THROW(missing = &dynamic_cast<MissingAttributeResponse&>(*response).requirements());
    ASSERT_EQ(missing->size(), 2U);
    bool hasCountry = false;
    for (auto& req : *missing) {
        if (req->name() == "country") {
            hasCountry = true;
            break;
        }
    }
    ASSERT_TRUE(hasCountry);
    bool hasIsMaxwell = false;
    for (auto& req : *missing) {
        if (req->name() == "is maxwell") {
            hasIsMaxwell = true;
            break;
        }
    }
    ASSERT_TRUE(hasIsMaxwell);

    attributes.clear();
    attributes.push_back(makeAttribute("country", "random"));
    attributes.push_back(makeAttribute("is maxwell", true));
    addUserAttributeRequest = AddUserAttributeRequest(maxwell, std::move(attributes));
    response = frontend.acceptRequest(addUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    makeAppointmentRequest = MakeAppointmentRequest(maxwell, serviceId);
    response = frontend.acceptRequest(makeAppointmentRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    bool hasPriority;
    ASSERT_NO_THROW(hasPriority = dynamic_cast<MakeAppointmentResponse&>(*response).hasPriority());
    ASSERT_TRUE(hasPriority);
    auto& service = controller.getServiceById(serviceId);
    ASSERT_TRUE(service.hasUser(maxwell));

    registerUserRequest = RegisterUserRequest("Fourier");
    response = frontend.acceptRequest(registerUserRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId fourier;
    ASSERT_NO_THROW(fourier = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(fourier));

    attributes.clear();
    attributes.push_back(makeAttribute("money", 100001));
    attributes.push_back(makeAttribute("country", "random"));
    attributes.push_back(makeAttribute("is maxwell", false));
    addUserAttributeRequest = AddUserAttributeRequest(fourier, std::move(attributes));
    response = frontend.acceptRequest(addUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    makeAppointmentRequest = MakeAppointmentRequest(fourier, serviceId);
    response = frontend.acceptRequest(makeAppointmentRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ASSERT_NO_THROW(hasPriority = dynamic_cast<MakeAppointmentResponse&>(*response).hasPriority());
    ASSERT_FALSE(hasPriority);
    ASSERT_TRUE(service.hasUser(fourier));
}


TEST(TestFrontend, GetPriorityRuleRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    auto response = frontend.acceptRequest(GetPriorityRuleRequest(ServiceId(0)));
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SERVICE);

    AddServiceRequest addServiceRequest("Test Service", "Description in development");
    response = frontend.acceptRequest(addServiceRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ServiceId serviceId;
    ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
    ASSERT_TRUE(isServiceIdValid(serviceId));

    auto predicate = BinaryPredicate::create(
            AndBinaryCalculator::create(),
            ComparisonPredicate::create(
                    ComparisonFlag::GREATER_OR_EQUAL,
                    makeAttribute("age", 18)
            ),
            ComparisonPredicate::create(
                    ComparisonFlag::LESS,
                    makeAttribute("age", 60)
            )
    );
    PolyVector<IRequirement> requirements;
    requirements.push_back(NumberRequirement::create("age"));

    response = frontend.acceptRequest(
            AddPriorityRuleRequest(serviceId, predicate->clone(), std::move(requirements))
    );
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    PredicateId predicateId;
    ASSERT_NO_THROW(predicateId = dynamic_cast<AddPriorityRuleResponse&>(*response).predicateId());
    ASSERT_TRUE(isPredicateIdValid(predicateId));

    response = frontend.acceptRequest(GetPriorityRuleRequest(serviceId));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const std::vector<SmallPredicateDescriptor>* descriptors;
    ASSERT_NO_THROW(descriptors = &dynamic_cast<GetPriorityRuleResponse&>(*response).descriptors());
    ASSERT_EQ(descriptors->size(), 1U);

    std::ostringstream expected;
    PredicatePrinter printerA(expected);
    predicate->accept(printerA);

    std::ostringstream actual;
    PredicatePrinter printerB(actual);
    (*descriptors)[0].predicate().accept(printerB);

    ASSERT_STREQ(actual.str().c_str(), expected.str().c_str());
}

