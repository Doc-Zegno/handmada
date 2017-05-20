//
// Created by syzegno on 07.05.17.
//


#include "AttributeType.h"


namespace Handmada {
    const char* AttributeType::toString(AttributeType::Type type)
    {
        switch (type) {
        case AttributeType::STRING:
            return "string";
        case AttributeType::NUMBER:
            return "number";
        case AttributeType::BOOLEAN:
            return "boolean";
        default:
            return "";
        }
    }
}
