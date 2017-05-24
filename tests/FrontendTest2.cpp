//
// Created by syzegno on 14.05.17.
//


#include <gtest/gtest.h>

#include "TestFrontend.h"
#include "SimpleController.h"
#include "Predicates.h"
#include "ConcreteRequirements.h"
#include "SnapShooter.h"
#include "Responses.h"

using namespace Handmada;


TEST(TestFrontend, AddPriorityRuleRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);


    auto predicate = ComparisonPredicate::create(
            ComparisonFlag::GREATER_OR_EQUAL,
            makeAttribute("age", 18)
    );
    PolyVector<IRequirement> requirements;
    requirements.push_back(NumberRequirement::create("age"));

    AddPriorityRuleRequest request(
            ServiceId(0),
            predicate->clone(),
            SnapShooter::copy(requirements)
    );
    auto response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SERVICE);

    response = frontend.acceptRequest(AddServiceRequest("sample text", "serious arguments"));
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ServiceId serviceId;
    ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
    ASSERT_TRUE(isServiceIdValid(serviceId));

    AddPriorityRuleRequest request2(
            serviceId,
            predicate->clone(),
            SnapShooter::copy(requirements)
    );
    response = frontend.acceptRequest(request2);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    PredicateId predicateId;
    ASSERT_NO_THROW(predicateId = dynamic_cast<AddPriorityRuleResponse&>(*response).predicateId());
    ASSERT_TRUE(isPredicateIdValid(predicateId));
    ASSERT_EQ(controller.servicePredicatesAmount(serviceId), 1U);

    predicate = ComparisonPredicate::create(
            ComparisonFlag::EQUAL,
            makeAttribute("age", "18")
    );
    requirements = PolyVector<IRequirement>();
    requirements.push_back(StringRequirement::create("age"));

    AddPriorityRuleRequest request3(
            serviceId,
            predicate->clone(),
            SnapShooter::copy(requirements)
    );
    response = frontend.acceptRequest(request3);
    ASSERT_EQ(response->code(), OpCode::REQUIREMENT_TYPE_COLLISION);
    const std::unordered_map<std::string, AttributeType::Type>* collisions;
    ASSERT_NO_THROW(collisions = &dynamic_cast<RequirementCollisionResponse&>(*response).collisions());
    ASSERT_EQ(collisions->size(), 1U);
    auto iterator = collisions->begin();
    ASSERT_STREQ(iterator->first.c_str(), "age");
    ASSERT_EQ(iterator->second, AttributeType::NUMBER);
}


TEST(TestFrontend, AddUserAttributeRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    PolyVector<IAttribute> attributes;
    attributes.push_back(makeAttribute("login", "User"));
    attributes.push_back(makeAttribute("age", 37));
    attributes.push_back(makeAttribute("loves coffee", true));

    AddUserAttributeRequest request(UserId(0), SnapShooter::copy(attributes));
    auto response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_USER);

    RegisterUserRequest request2("User");
    response = frontend.acceptRequest(request2);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    UserId userId;
    ASSERT_NO_THROW(userId = dynamic_cast<RegisterUserResponse&>(*response).userId());
    ASSERT_TRUE(isUserIdValid(userId));

    AddUserAttributeRequest request3(userId, SnapShooter::copy(attributes));
    response = frontend.acceptRequest(request);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    const std::vector<std::string>* added;
    ASSERT_NO_THROW(added = &dynamic_cast<AddUserAttributeResponse&>(*response).attributes());
    ASSERT_EQ(added->size(), 2U);
    ASSERT_STREQ((*added)[0].c_str(), "age");
    ASSERT_STREQ((*added)[1].c_str(), "loves coffee");

    auto container = controller.getUserAttributes(userId);
    ASSERT_FALSE(container->getAttributeByName("age") == nullptr);
    ASSERT_FALSE(container->getAttributeByName("loves coffee") == nullptr);

    auto copy = *added;
    RemoveUserAttributeRequest removeUserAttributeRequest(userId, std::move(copy));
    response = frontend.acceptRequest(removeUserAttributeRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    const PolyVector<IAttribute>* deleted;
    ASSERT_NO_THROW(deleted = &dynamic_cast<RemoveUserAttributeResponse&>(*response).attributes());

    bool hasAge = (*deleted)[0]->name() == "age" || (*deleted)[1]->name() == "age";
    ASSERT_TRUE(hasAge);
    bool hasLovesCoffee = (*deleted)[0]->name() == "loves coffee" || (*deleted)[1]->name() == "loves coffee";
    ASSERT_TRUE(hasLovesCoffee);

    container = controller.getUserAttributes(userId);
    ASSERT_TRUE(container->getAttributeByName("age") == nullptr);
    ASSERT_TRUE(container->getAttributeByName("loves coffee") == nullptr);
}


TEST(TestFrontend, AttachSpecialistRequest)
{
    SimpleController controller;
    TestFrontend frontend(&controller);

    AttachSpecialistRequest attachSpecialistRequest(SpecialistId(0), ServiceId(0));
    auto response = frontend.acceptRequest(attachSpecialistRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SPECIALIST);

    AddSpecialistRequest addSpecialistRequest("Alberto Syvsow");
    response = frontend.acceptRequest(addSpecialistRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    SpecialistId specialistId;
    ASSERT_NO_THROW(specialistId = dynamic_cast<AddSpecialistResponse&>(*response).specialistId());
    ASSERT_TRUE(isSpecialistIdValid(specialistId));

    attachSpecialistRequest = AttachSpecialistRequest(specialistId, ServiceId(0));
    response = frontend.acceptRequest(attachSpecialistRequest);
    ASSERT_EQ(response->code(), OpCode::NO_SUCH_SERVICE);

    AddServiceRequest addServiceRequest("coder", "not a programmer");
    response = frontend.acceptRequest(addServiceRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);
    ServiceId serviceId;
    ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
    ASSERT_TRUE(isServiceIdValid(serviceId));

    attachSpecialistRequest = AttachSpecialistRequest(specialistId, serviceId);
    response = frontend.acceptRequest(attachSpecialistRequest);
    ASSERT_EQ(response->code(), OpCode::SUCCESS);

    Service& service = controller.getServiceById(serviceId);
    auto iterator = service.getSpecialistsIterator();
    ASSERT_TRUE(iterator->hasNext());
    auto pair = iterator->next();
    ASSERT_EQ(pair->first, specialistId);
    ASSERT_STREQ(pair->second->name().c_str(), "Alberto Syvsow");

    response = frontend.acceptRequest(attachSpecialistRequest);
    ASSERT_EQ(response->code(), OpCode::ALREADY_ATTACHED);
}


