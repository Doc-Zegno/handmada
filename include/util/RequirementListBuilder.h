//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_REQUIREMENTLISTBUILDER_H
#define EQUEUE_V2_REQUIREMENTLISTBUILDER_H


#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "IRequirement.h"


namespace Handmada {
    class RequirementListBuilder
    {
    private:
        std::ostream& output_;
        std::istream& input_;
        std::vector<std::unique_ptr<Handmada::IRequirement>> requirements_;

    public:
        RequirementListBuilder(std::ostream& output, std::istream& input);
        void buildFrom(const std::unordered_map<std::string, Handmada::AttributeType::Type>& identifiers);
        std::vector<std::unique_ptr<Handmada::IRequirement>> getRequirementList();
    };
}


#endif //EQUEUE_V2_REQUIREMENTLISTBUILDER_H
