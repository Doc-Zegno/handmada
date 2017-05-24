//
// Created by syzegno on 16.05.17.
//


#include "ConsoleRequirementListBuilder.h"
#include "ConcreteRequirements.h"


namespace Handmada {
    PolyVector<IRequirement> ConsoleRequirementListBuilder::build(
            Console* console,
            const std::unordered_map<std::string, AttributeType::Type>& table
    )
    {
        PolyVector<IRequirement> requirements;
        for (auto& pair : table) {
            if (pair.second == AttributeType::STRING) {
                requirements.push_back(StringRequirement::create(pair.first));
            } else if (pair.second == AttributeType::NUMBER) {
                requirements.push_back(NumberRequirement::create(pair.first));
            } else {
                std::string question;
                console->out("Enter question for Yes/No attribute \"", pair.first, '\"');
                console->input(">> ", question);
                requirements.push_back(BooleanRequirement::create(pair.first, question));
            }
        }

        return std::move(requirements);
    }
}
