//
// Created by syzegno on 30.04.17.
//

#ifndef EQUEUE_V2_FILEREQUIREMENTPRINTER_H
#define EQUEUE_V2_FILEREQUIREMENTPRINTER_H


#include "IRequirementVisitor.h"
#include "MetaNumber.h"
#include "IStream.h"


namespace Handmada {
    class StreamRequirementPrinter : public IRequirementVisitor
    {
    private:
        IStream& stream_;

        void prologue(MetaNumber::Type meta, const IRequirement& requirement) const;

    public:
        StreamRequirementPrinter(IStream& stream);

        virtual void visit(const StringRequirement& requirement) override;
        virtual void visit(const NumberRequirement& requirement) override;
        virtual void visit(const BooleanRequirement& requirement) override;
    };
}


#endif //EQUEUE_V2_FILEREQUIREMENTPRINTER_H
