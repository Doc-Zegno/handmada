//
// Created by syzegno on 30.04.17.
//

#ifndef EQUEUE_V2_REQUIREMENT_H
#define EQUEUE_V2_REQUIREMENT_H


#include <memory>

#include "IAttribute.h"
#include "AttributeType.h"


namespace Handmada {
    class IRequirementVisitor;


    /**
     * Requirements represent information about missing attributes
     * That means that user gets the list of requirements (and not the list of attributes)
     * when he tries to book a service.
     * Additionally, this implies that requirement object should contain information
     * enough to make building of missing attribute possible
     */
    class IRequirement
    {
    public:
        virtual const std::string& name() const = 0;
        virtual AttributeType::Type type() const = 0;
        virtual std::unique_ptr<Handmada::IRequirement> clone() const = 0;
        virtual void accept(IRequirementVisitor& visitor) const = 0;

        virtual ~IRequirement() { }
    };
}


#endif //EQUEUE_V2_REQUIREMENT_H
