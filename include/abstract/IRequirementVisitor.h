//
// Created by syzegno on 30.04.17.
//

#ifndef EQUEUE_V2_IREQUIREMENTVISITOR_H
#define EQUEUE_V2_IREQUIREMENTVISITOR_H


#include "ConcreteRequirements.h"


namespace Handmada {
    class IRequirementVisitor
    {
    public:
        virtual void visit(const StringRequirement& requirement) = 0;
        virtual void visit(const NumberRequirement& requirement) = 0;
        virtual void visit(const BooleanRequirement& requirement) = 0;

        virtual ~IRequirementVisitor() { }
    };
}


#endif //EQUEUE_V2_IREQUIREMENTVISITOR_H
