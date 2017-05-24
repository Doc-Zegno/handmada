//
// Created by syzegno on 30.04.17.
//


#include "../../include/model/ConcreteRequirements.h"
#include "../../include/abstract/IRequirementVisitor.h"


namespace Handmada {
    // S t r i n g R e q u i r e m e n t
    StringRequirement::StringRequirement(const std::string& name)
        : name_(name)
    { }


    std::unique_ptr<Handmada::IAttribute> StringRequirement::createAttribute() const
    {
        return std::unique_ptr<Handmada::IAttribute>(new StringAttribute(name(), std::string()));
    }


    void StringRequirement::accept(IRequirementVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IRequirement> StringRequirement::clone() const
    {
        return std::unique_ptr<IRequirement>(new StringRequirement(*this));
    }


    const std::string& StringRequirement::name() const
    {
        return name_;
    }


    AttributeType::Type StringRequirement::type() const
    {
        return AttributeType::STRING;
    }


    std::unique_ptr<IRequirement> StringRequirement::create(const std::string& name)
    {
        return std::unique_ptr<IRequirement>(new StringRequirement(name));
    }



    // N u m b e r R e q u i r e m e n t
    NumberRequirement::NumberRequirement(const std::string& name)
        : name_(name)
    { }


    std::unique_ptr<Handmada::IAttribute> NumberRequirement::createAttribute() const
    {
        return std::unique_ptr<Handmada::IAttribute>(new NumberAttribute(name(), DEFAULT_NUMBER));
    }


    void NumberRequirement::accept(IRequirementVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IRequirement> NumberRequirement::clone() const
    {
        return std::unique_ptr<IRequirement>(new NumberRequirement(*this));
    }


    const std::string& NumberRequirement::name() const
    {
        return name_;
    }


    AttributeType::Type NumberRequirement::type() const
    {
        return AttributeType::NUMBER;
    }


    std::unique_ptr<IRequirement> NumberRequirement::create(const std::string& name)
    {
        return std::unique_ptr<IRequirement>(new NumberRequirement(name));
    }



    // B o o l e a n R e q u i r e m e n t
    BooleanRequirement::BooleanRequirement(const std::string& name, const std::string& question)
        : name_(name), question_(question)
    { }


    std::unique_ptr<IAttribute> BooleanRequirement::createAttribute() const
    {
        return std::unique_ptr<Handmada::IAttribute>(new BooleanAttribute(name(), false));
    }


    const std::string& BooleanRequirement::question() const
    {
        return question_;
    }


    void BooleanRequirement::accept(IRequirementVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IRequirement> BooleanRequirement::clone() const
    {
        return std::unique_ptr<IRequirement>(new BooleanRequirement(*this));
    }


    const std::string& BooleanRequirement::name() const
    {
        return name_;
    }


    AttributeType::Type BooleanRequirement::type() const
    {
        return AttributeType::BOOLEAN;
    }


    std::unique_ptr<IRequirement> BooleanRequirement::create(const std::string& name, const std::string& question)
    {
        return std::unique_ptr<IRequirement>(new BooleanRequirement(name, question));
    }
}

