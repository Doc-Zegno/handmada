//
// Created by syzegno on 02.05.17.
//

#ifndef EQUEUE_V2_REQUIREMENTPRINTER_H
#define EQUEUE_V2_REQUIREMENTPRINTER_H


#include <iostream>

#include "../abstract/IRequirementVisitor.h"


namespace Handmada {
    /**
     * Just for testing purposes
     * RequirementScanner will combine printing responsibilities with scanning
     */
    class TestRequirementPrinter : public IRequirementVisitor
    {
    private:
        std::ostream& output_;

    public:
        TestRequirementPrinter(std::ostream& output);

        virtual void visit(const StringRequirement& requirement) override;
        virtual void visit(const NumberRequirement& requirement) override;
        virtual void visit(const BooleanRequirement& requirement) override;
    };
}


#endif //EQUEUE_V2_REQUIREMENTPRINTER_H
