//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_CONSOLEATTRIBUTELISTBUILDER_H
#define EQUEUE_V2_CONSOLEATTRIBUTELISTBUILDER_H


#include "IRequirementVisitor.h"
#include "Console.h"
#include "PolyVector.h"
#include "Attributes.h"


namespace Handmada {
    class ConsoleAttributeListBuilder : public IRequirementVisitor
    {
    private:
        PolyVector<IAttribute> attributes_;
        Console* console_;

    public:
        ConsoleAttributeListBuilder(Console* console);

        PolyVector<IAttribute> build(const PolyVector<IRequirement>& requirements);

        virtual void visit(const StringRequirement& requirement) override;
        virtual void visit(const NumberRequirement& requirement) override;
        virtual void visit(const BooleanRequirement& requirement) override;
    };
}


#endif //EQUEUE_V2_CONSOLEATTRIBUTELISTBUILDER_H
