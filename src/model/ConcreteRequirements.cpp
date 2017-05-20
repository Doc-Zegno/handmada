//
// Created by syzegno on 30.04.17.
//


#include "ConcreteRequirements.h"
#include "IRequirementVisitor.h"


namespace Handmada {
    // S t r i n g R e q u i r e m e n t
    StringRequirement::StringRequirement(const std::string& name)
        : name_(name)
    { }


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

