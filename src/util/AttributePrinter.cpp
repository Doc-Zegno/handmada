//
// Created by syzegno on 28.04.17.
//


#include "util/AttributePrinter.h"
#include "../../include/misc/literal/BooleanLiteral.h"


namespace Handmada {
    AttributePrinter::AttributePrinter(std::ostream& output) : output_(output)
    { }


    void AttributePrinter::visit(const StringAttribute& attribute)
    {
        output_ << attribute.name() << ": \"" << attribute.value << "\"\n";
    }


    void AttributePrinter::visit(const NumberAttribute& attribute)
    {
        output_ << attribute.name() << ": " << attribute.value << std::endl;
    }


    void AttributePrinter::visit(const BooleanAttribute& attribute)
    {
        output_ << attribute.name() << ": "
                << (attribute.value ? Literal::strTrueLiteral : Literal::strFalseLiteral)
                << std::endl;
    }
}
