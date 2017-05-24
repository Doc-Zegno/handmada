//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_PRINTERVISITOR_H
#define EQUEUE_V2_PRINTERVISITOR_H


#include <iostream>

#include "abstract/IAttributeVisitor.h"
#include "../model/Attributes.h"


namespace Handmada {
    class AttributePrinter : public IAttributeVisitor
    {
    private:
        std::ostream& output_;

    public:
        AttributePrinter(std::ostream& output);

        virtual void visit(const StringAttribute& attribute) override;
        virtual void visit(const NumberAttribute& attribute) override;
        virtual void visit(const BooleanAttribute& attribute) override;
    };
}


#endif //EQUEUE_V2_PRINTERVISITOR_H
