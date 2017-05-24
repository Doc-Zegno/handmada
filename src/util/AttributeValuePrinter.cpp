//
// Created by syzegno on 11.05.17.
//


#include "../../include/util/AttributeValuePrinter.h"

#include "../../include/misc/literal/BooleanLiteral.h"


namespace Handmada {
    AttributeValuePrinter::AttributeValuePrinter(std::ostream& output)
            : output_(output)
    { }


    void AttributeValuePrinter::visit(const StringAttribute& attribute)
    {
        output_ << '\"' << attribute.value << '\"' << std::endl;
    }


    void AttributeValuePrinter::visit(const NumberAttribute& attribute)
    {
        output_ << attribute.value << std::endl;
    }


    void AttributeValuePrinter::visit(const BooleanAttribute& attribute)
    {
        if (attribute.value) {
            output_ << Literal::strTrueLiteral;
        } else {
            output_ << Literal::strFalseLiteral;
        }
        output_ << std::endl;
    }
}
