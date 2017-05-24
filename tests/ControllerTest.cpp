//
// Created by syzegno on 17.05.17.
//


#include <gtest/gtest.h>

#include "SimpleController.h"
#include "TestFrontend.h"
#include "PredicateCalculators.h"
#include "PredicatePrinter.h"
#include "SnapShooter.h"

using namespace Handmada;


TEST(Controller, Swapping)
{
    const char* const testDir = "testDir";

    ASSERT_GE(mkdir(testDir, 0777), 0);
    ASSERT_GE(chmod(testDir, 0777), 0);
    ASSERT_GE(chdir(testDir), 0);

    std::string serviceName = "test service";
    std::string serviceDescription = "test description";
    std::string specialistName = "test tester";

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

    ServiceId serviceId;
    SpecialistId specialistId;

    {
        SimpleController controller;
        ASSERT_NO_THROW(controller.checkOut());
        TestFrontend frontend(&controller);

        auto response = frontend.acceptRequest(AddServiceRequest(serviceName, serviceDescription));
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        ASSERT_NO_THROW(serviceId = dynamic_cast<AddServiceResponse&>(*response).serviceId());
        ASSERT_TRUE(isServiceIdValid(serviceId));

        response = frontend.acceptRequest(AddSpecialistRequest(specialistName));
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        ASSERT_NO_THROW(specialistId = dynamic_cast<AddSpecialistResponse&>(*response).specialistId());
        ASSERT_TRUE(isSpecialistIdValid(specialistId));

        response = frontend.acceptRequest(AttachSpecialistRequest(specialistId, serviceId));
        ASSERT_EQ(response->code(), OpCode::SUCCESS);

        response = frontend.acceptRequest(
                AddPriorityRuleRequest(
                        serviceId, predicate->clone(), SnapShooter::copy(requirements)
                )
        );
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        ASSERT_NO_THROW(controller.swap());
    }

    {
        SimpleController controller;
        ASSERT_NO_THROW(controller.checkOut());
        TestFrontend frontend(&controller);

        auto response = frontend.acceptRequest(GetServiceDescriptorRequest());
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        const std::vector<ServiceDescriptor>* descriptors;
        ASSERT_NO_THROW(descriptors = &dynamic_cast<GetServiceDescriptorResponse&>(*response).descriptors());
        ASSERT_EQ(descriptors->size(), 1U);
        ASSERT_EQ((*descriptors)[0].id(), serviceId);
        ASSERT_STREQ((*descriptors)[0].name().c_str(), serviceName.c_str());
        ASSERT_STREQ((*descriptors)[0].description().c_str(), serviceDescription.c_str());

        response = frontend.acceptRequest(GetSpecialistDescriptorRequest(serviceId));
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        const std::vector<SpecialistDescriptor>* descriptors2;
        ASSERT_NO_THROW(descriptors2 = &dynamic_cast<GetSpecialistDescriptorResponse&>(*response).descriptors());
        ASSERT_EQ(descriptors2->size(), 1U);
        ASSERT_EQ((*descriptors2)[0].id(), specialistId);
        ASSERT_STREQ((*descriptors2)[0].name().c_str(), specialistName.c_str());

        response = frontend.acceptRequest(GetPriorityRuleRequest(serviceId));
        ASSERT_EQ(response->code(), OpCode::SUCCESS);
        const std::vector<SmallPredicateDescriptor>* descriptors3;
        ASSERT_NO_THROW(descriptors3 = &dynamic_cast<GetPriorityRuleResponse&>(*response).descriptors());
        ASSERT_EQ(descriptors3->size(), 1U);

        std::ostringstream actual;
        PredicatePrinter printer(actual);
        (*descriptors3)[0].predicate().accept(printer);

        std::ostringstream expected;
        PredicatePrinter printer2(expected);
        predicate->accept(printer2);
        ASSERT_STREQ(actual.str().c_str(), expected.str().c_str());

        ASSERT_NO_THROW(controller.swap());
        ASSERT_NO_THROW(controller.removeDump());
    }

    ASSERT_GE(chdir(".."), 0);
    ASSERT_GE(rmdir(testDir), 0);
}


