//
// Created by syzegno on 17.05.17.
//


#include "ConsoleAttributeListBuilder.h"


namespace Handmada {
    ConsoleAttributeListBuilder::ConsoleAttributeListBuilder(Console* console)
            : console_(console)
    { }


    PolyVector<IAttribute> ConsoleAttributeListBuilder::build(const PolyVector<IRequirement>& requirements)
    {
        for (auto& requirement : requirements) {
            requirement->accept(*this);
        }
        return std::move(attributes_);
    }


    void ConsoleAttributeListBuilder::visit(const StringRequirement& requirement)
    {
        std::string value;
        console_->outNoLine("Enter your ", requirement.name(), ": ");
        console_->get(value);
        attributes_.push_back(makeAttribute(requirement.name(), value));
    }


    void ConsoleAttributeListBuilder::visit(const NumberRequirement& requirement)
    {
        Number value;
        console_->outNoLine("Enter your ", requirement.name(), ": ");
        console_->get(value);
        attributes_.push_back(makeAttribute(requirement.name(), value));
    }


    void ConsoleAttributeListBuilder::visit(const BooleanRequirement& requirement)
    {
        bool value;
        char choice;
        console_->outNoLine(requirement.question(), " (y/n): ");
        console_->get(choice);
        value = (choice == 'y' || choice == 'Y');
        attributes_.push_back(makeAttribute(requirement.name(), value));
    }
}

