//
// Created by syzegno on 30.04.17.
//

#ifndef EQUEUE_V2_REQUIREMENT_H
#define EQUEUE_V2_REQUIREMENT_H


#include <memory>

#include "IAttribute.h"
#include "../misc/AttributeType.h"


namespace Handmada {
    class IRequirementVisitor;


    class IRequirement
    {
    public:
        virtual const std::string& name() const = 0;
        virtual AttributeType::Type type() const = 0;
        virtual std::unique_ptr<Handmada::IAttribute> createAttribute() const = 0;
        virtual std::unique_ptr<Handmada::IRequirement> clone() const = 0;
        virtual void accept(IRequirementVisitor& visitor) const = 0;

        virtual ~IRequirement() { }
    };
}


#endif //EQUEUE_V2_REQUIREMENT_H
