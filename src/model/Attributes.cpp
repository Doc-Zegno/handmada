//
// Created by syzegno on 28.04.17.
//


#include <iostream>
#include <cstring>
#include "Attributes.h"
#include "IAttributeVisitor.h"

namespace Handmada {
    // S t r i n g
    void StringAttribute::accept(IAttributeVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    StringAttribute::StringAttribute(const std::string& name, const std::string& value)
        : name_(name), value(value)
    { }


    const std::string& StringAttribute::name() const
    {
        return name_;
    }


    AttributeType::Type StringAttribute::type() const
    {
        return AttributeType::STRING;
    }


    int StringAttribute::compareTo(const IAttribute& attribute) const
    {
        auto& stringAttribute = dynamic_cast<const StringAttribute&>(attribute);
        return std::strcmp(value.c_str(), stringAttribute.value.c_str());
    }


    std::unique_ptr<IAttribute> StringAttribute::clone() const
    {
        return std::unique_ptr<IAttribute>(new StringAttribute(name_, value));
    }



    // N u m b e r
    void NumberAttribute::accept(IAttributeVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    NumberAttribute::NumberAttribute(const std::string& name, Number value)
        : name_(name), value(value)
    { }


    const std::string& NumberAttribute::name() const
    {
        return name_;
    }


    AttributeType::Type NumberAttribute::type() const
    {
        return AttributeType::NUMBER;
    }


    int NumberAttribute::compareTo(const IAttribute& attribute) const
    {
        auto& numberAttribute = dynamic_cast<const NumberAttribute&>(attribute);
        return compareNumbers(value, numberAttribute.value);
    }


    std::unique_ptr<IAttribute> NumberAttribute::clone() const
    {
        return std::unique_ptr<IAttribute>(new NumberAttribute(name_, value));
    }



    // B o o l e a n
    void BooleanAttribute::accept(IAttributeVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    BooleanAttribute::BooleanAttribute(const std::string& name, bool value)
        : name_(name), value(value)
    { }


    const std::string& BooleanAttribute::name() const
    {
        return name_;
    }


    AttributeType::Type BooleanAttribute::type() const
    {
        return AttributeType::BOOLEAN;
    }


    int BooleanAttribute::compareTo(const IAttribute& attribute) const
    {
        auto& booleanAttribute = dynamic_cast<const BooleanAttribute&>(attribute);
        int a = value;
        int b = booleanAttribute.value;
        return a - b;
    }


    std::unique_ptr<IAttribute> BooleanAttribute::clone() const
    {
        return std::unique_ptr<IAttribute>(new BooleanAttribute(name_, value));
    }



    // H e l p e r s
    int compareNumbers(Number a, Number b)
    {
        const Number EQUALITY_EPSILON = 0.00001;

        Number diff = a - b;
        if (diff < EQUALITY_EPSILON && diff > -EQUALITY_EPSILON) {
            return 0;
        } else if (diff > 0.0) {
            return 1;
        } else {
            return -1;
        }
    }



    std::unique_ptr<Handmada::StringAttribute> makeAttribute(const std::string& name, const char* value)
    {
        return std::unique_ptr<StringAttribute>(new StringAttribute(name, value));
    }


    std::unique_ptr<Handmada::StringAttribute> makeAttribute(const std::string& name, const std::string& value)
    {
        return std::unique_ptr<StringAttribute>(new StringAttribute(name, value));
    }


    std::unique_ptr<Handmada::NumberAttribute> makeAttribute(const std::string& name, Number value)
    {
        return std::unique_ptr<NumberAttribute>(new NumberAttribute(name, value));
    }


    std::unique_ptr<Handmada::NumberAttribute> makeAttribute(const std::string& name, int value)
    {
        return std::unique_ptr<NumberAttribute>(new NumberAttribute(name, value));
    }


    std::unique_ptr<Handmada::BooleanAttribute> makeAttribute(const std::string& name, bool value)
    {
        return std::unique_ptr<BooleanAttribute>(new BooleanAttribute(name, value));
    }
}
