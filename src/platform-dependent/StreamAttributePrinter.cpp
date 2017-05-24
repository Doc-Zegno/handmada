//
// Created by syzegno on 28.04.17.
//


#include "StreamAttributePrinter.h"
#include "Serializer.h"


namespace Handmada {
    StreamAttributePrinter::StreamAttributePrinter(IStream& stream)
            : stream_(stream)
    { }


    void StreamAttributePrinter::prologue(const IAttribute& attribute, MetaNumber::Type meta) const
    {
        Serializer::put(stream_, meta);
        Serializer::put(stream_, attribute.name());
    }


    void StreamAttributePrinter::visit(const StringAttribute& attribute)
    {
        prologue(attribute, MetaNumber::STRING_ATTRIBUTE);
        Serializer::put(stream_, attribute.value);
    }


    void StreamAttributePrinter::visit(const NumberAttribute& attribute)
    {
        prologue(attribute, MetaNumber::NUMBER_ATTRIBUTE);
        Serializer::put(stream_, attribute.value);
    }


    void StreamAttributePrinter::visit(const BooleanAttribute& attribute)
    {
        prologue(attribute, MetaNumber::BOOLEAN_ATTRIBUTE);
        Serializer::put(stream_, attribute.value);
    }
}
