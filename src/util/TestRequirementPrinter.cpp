//
// Created by syzegno on 02.05.17.
//


#include "TestRequirementPrinter.h"


namespace Handmada {
    TestRequirementPrinter::TestRequirementPrinter(std::ostream& output)
        : output_(output)
    { }


    void TestRequirementPrinter::visit(const StringRequirement& requirement)
    {
        output_ << requirement.name() << std::endl;
    }


    void TestRequirementPrinter::visit(const NumberRequirement& requirement)
    {
        output_ << requirement.name() << std::endl;
    }


    void TestRequirementPrinter::visit(const BooleanRequirement& requirement)
    {
        output_ << requirement.question() << std::endl;
    }
}
