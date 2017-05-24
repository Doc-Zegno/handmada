//
// Created by syzegno on 30.04.17.
//


#include "StreamRequirementPrinter.h"
#include "Serializer.h"


namespace Handmada {
    StreamRequirementPrinter::StreamRequirementPrinter(IStream& stream)
        : stream_(stream)
    { }


    void StreamRequirementPrinter::prologue(
            MetaNumber::Type meta,
            const IRequirement& requirement
    ) const
    {
        Serializer::put(stream_, meta);
        Serializer::put(stream_, requirement.name());
    }


    void StreamRequirementPrinter::visit(const StringRequirement& requirement)
    {
        prologue(MetaNumber::STRING_REQUIREMENT, requirement);
    }


    void StreamRequirementPrinter::visit(const NumberRequirement& requirement)
    {
        prologue(MetaNumber::NUMBER_REQUIREMENT, requirement);
    }


    void StreamRequirementPrinter::visit(const BooleanRequirement& requirement)
    {
        prologue(MetaNumber::BOOLEAN_REQUIREMENT, requirement);
        Serializer::put(stream_, requirement.question());
    }
}

