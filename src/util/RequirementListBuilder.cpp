//
// Created by syzegno on 07.05.17.
//


#include "RequirementListBuilder.h"
#include "ConcreteRequirements.h"


namespace Handmada {
    RequirementListBuilder::RequirementListBuilder(std::ostream& output, std::istream& input)
        : output_(output), input_(input)
    { }


    void RequirementListBuilder::buildFrom(
            const std::unordered_map<std::string, Handmada::AttributeType::Type>& identifiers
    )
    {
        for (const auto& pair : identifiers) {
            if (pair.second == AttributeType::STRING) {
                requirements_.push_back(std::unique_ptr<IRequirement>(new StringRequirement(pair.first)));
            } else if (pair.second == AttributeType::NUMBER) {
                requirements_.push_back(std::unique_ptr<IRequirement>(new NumberRequirement(pair.first)));
            } else {
                output_ << "Enter a question for boolean attribute \""
                        << pair.first << "\":\n>> ";
                std::string question;
                std::getline(input_, question);
                requirements_.push_back(
                        std::unique_ptr<IRequirement>(new BooleanRequirement(pair.first, question))
                );
            }
        }
    }


    std::vector<std::unique_ptr<Handmada::IRequirement>> RequirementListBuilder::getRequirementList()
    {
        return std::move(requirements_);
    }
}

