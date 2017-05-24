//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_FILEPACKERVISITOR_H
#define EQUEUE_V2_FILEPACKERVISITOR_H


#include "IAttributeVisitor.h"
#include "Attributes.h"
#include "MetaNumber.h"
#include "IStream.h"


namespace Handmada {
    class StreamAttributePrinter : public IAttributeVisitor
    {
    private:
        IStream& stream_;

        void prologue(const IAttribute& attribute, MetaNumber::Type meta) const;

    public:
        StreamAttributePrinter(IStream& stream);

        virtual void visit(const StringAttribute& attribute) override;
        virtual void visit(const NumberAttribute& attribute) override;
        virtual void visit(const BooleanAttribute& attribute) override;
    };
}


#endif //EQUEUE_V2_FILEPACKERVISITOR_H
