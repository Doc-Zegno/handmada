//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_ATTRIBUTES_H
#define EQUEUE_V2_ATTRIBUTES_H


#include <memory>
#include "IAttribute.h"


namespace Handmada {
    class StringAttribute : public IAttribute
    {
    private:
        std::string name_;

    public:
        std::string value;

        StringAttribute(const std::string& name, const std::string& value);
        virtual const std::string& name() const override;
        virtual AttributeType::Type type() const override;
        virtual int compareTo(const IAttribute& attribute) const override;
        virtual void accept(IAttributeVisitor& visitor) const override;
        virtual std::unique_ptr<IAttribute> clone() const override;
    };


    using Number = double;
    const Number DEFAULT_NUMBER = 0.0;

    int compareNumbers(Number a, Number b);

    class NumberAttribute : public IAttribute
    {
    private:
        std::string name_;

    public:
        Number value;

        NumberAttribute(const std::string& name, Number value);
        virtual const std::string& name() const override;
        virtual AttributeType::Type type() const override;
        virtual int compareTo(const IAttribute& attribute) const override;
        virtual void accept(IAttributeVisitor& visitor) const override;
        virtual std::unique_ptr<IAttribute> clone() const override;
    };


    class BooleanAttribute : public IAttribute
    {
    private:
        std::string name_;

    public:
        bool value;

        BooleanAttribute(const std::string& name, bool value);
        virtual const std::string& name() const override;
        virtual AttributeType::Type type() const override;
        virtual int compareTo(const IAttribute& attribute) const override;
        virtual void accept(IAttributeVisitor& visitor) const override;

        virtual std::unique_ptr<IAttribute> clone() const override;
    };


    std::unique_ptr<Handmada::StringAttribute> makeAttribute(const std::string& name, const char* value);
    std::unique_ptr<Handmada::StringAttribute> makeAttribute(const std::string& name, const std::string& value);
    std::unique_ptr<Handmada::NumberAttribute> makeAttribute(const std::string& name, Number value);
    std::unique_ptr<Handmada::NumberAttribute> makeAttribute(const std::string& name, int value);
    std::unique_ptr<Handmada::BooleanAttribute> makeAttribute(const std::string& name, bool value);
}


#endif //EQUEUE_V2_ATTRIBUTES_H
