//
// Created by syzegno on 16.05.17.
//

#ifndef EQUEUE_V2_CONSOLEREQUIREMENTLISTBUILDER_H
#define EQUEUE_V2_CONSOLEREQUIREMENTLISTBUILDER_H


#include <unordered_map>

#include "IRequirement.h"
#include "PolyVector.h"
#include "AttributeType.h"
#include "Console.h"


namespace Handmada {
    class ConsoleRequirementListBuilder
    {
    public:
        static PolyVector<IRequirement> build(
                Console* console,
                const std::unordered_map<std::string, AttributeType::Type>& table
        );
    };
}


#endif //EQUEUE_V2_CONSOLEREQUIREMENTLISTBUILDER_H
