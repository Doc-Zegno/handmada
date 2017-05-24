//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_IATTRIBUTE_H
#define EQUEUE_V2_IATTRIBUTE_H


#include <string>
#include <memory>

#include "AttributeType.h"


namespace Handmada {
    class IAttributeVisitor;


    class IAttribute
    {
    public:
        virtual const std::string& name() const = 0;
        virtual AttributeType::Type type() const = 0;
        virtual int compareTo(const IAttribute& attribute) const = 0;
        virtual void accept(IAttributeVisitor& visitor) const = 0;
        virtual std::unique_ptr<IAttribute> clone() const = 0;

        virtual ~IAttribute() { }
    };
}

#endif //EQUEUE_V2_IATTRIBUTE_H
