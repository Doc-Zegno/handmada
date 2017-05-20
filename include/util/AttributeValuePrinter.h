//
// Created by syzegno on 11.05.17.
//

#ifndef EQUEUE_V2_ATTRIBUTEVALUEPRINTER_H
#define EQUEUE_V2_ATTRIBUTEVALUEPRINTER_H


#include <iostream>

#include "IAttributeVisitor.h"


namespace Handmada {
    class AttributeValuePrinter : public IAttributeVisitor
    {
    private:
        std::ostream& output_;

    public:
        AttributeValuePrinter(std::ostream& output);

        virtual void visit(const StringAttribute& attribute) override;
        virtual void visit(const NumberAttribute& attribute) override;
        virtual void visit(const BooleanAttribute& attribute) override;
    };
}


#endif //EQUEUE_V2_ATTRIBUTEVALUEPRINTER_H
