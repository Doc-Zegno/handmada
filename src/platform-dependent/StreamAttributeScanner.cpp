//
// Created by syzegno on 28.04.17.
//

#include "StreamAttributeScanner.h"

#include <cstring>

#include "Serializer.h"


namespace Handmada {
    StreamAttributeScannerException::StreamAttributeScannerException(const std::string& info)
            : runtime_error(info)
    { }


    StreamAttributeScanner::StreamAttributeScanner(IStream& stream) : stream_(stream)
    { }


    std::unique_ptr<Handmada::IAttribute> StreamAttributeScanner::getNext() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);

        std::string name;
        Serializer::get(stream_, name);
        switch (meta) {
        case MetaNumber::STRING_ATTRIBUTE: {
            std::string value;
            Serializer::get(stream_, value);
            return std::unique_ptr<IAttribute>(
                    new StringAttribute(name, value)
            );
        }

        case MetaNumber::NUMBER_ATTRIBUTE: {
            Number value;
            Serializer::get(stream_, value);
            return std::unique_ptr<IAttribute>(
                    new NumberAttribute(name, value)
            );
        }

        case MetaNumber::BOOLEAN_ATTRIBUTE: {
            bool value;
            Serializer::get(stream_, value);
            return std::unique_ptr<IAttribute>(
                    new BooleanAttribute(name, value)
            );
        }

        default:
            throw StreamAttributeScannerException("unknown meta");
        }
    }
}
