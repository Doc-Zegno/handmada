//
// Created by syzegno on 30.04.17.
//


#include "StreamRequirementScanner.h"

#include <unistd.h>
#include <cstring>

#include "ConcreteRequirements.h"
#include "MetaNumber.h"
#include "Serializer.h"


namespace Handmada {
    StreamRequirementScannerException::StreamRequirementScannerException(const std::string& info)
            : runtime_error(info)
    { }


    StreamRequirementScanner::StreamRequirementScanner(IStream& stream)
            : stream_(stream)
    { }


    std::unique_ptr<Handmada::IRequirement> StreamRequirementScanner::getNext() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);

        std::string name;
        Serializer::get(stream_, name);
        switch (meta) {
        case MetaNumber::STRING_REQUIREMENT:
            return std::unique_ptr<IRequirement>(new StringRequirement(name));

        case MetaNumber::NUMBER_REQUIREMENT:
            return std::unique_ptr<IRequirement>(new NumberRequirement(name));

        case MetaNumber::BOOLEAN_REQUIREMENT: {
            std::string question;
            Serializer::get(stream_, question);
            return std::unique_ptr<IRequirement>(
                    new BooleanRequirement(name, question)
            );
        }

        default:
            throw StreamRequirementScannerException("unknown meta");
        }
    }
}
