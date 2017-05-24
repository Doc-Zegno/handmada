//
// Created by syzegno on 30.04.17.
//

#ifndef EQUEUE_V2_CONCRETEREQUIREMENTS_H
#define EQUEUE_V2_CONCRETEREQUIREMENTS_H


#include "IRequirement.h"
#include "Attributes.h"


namespace Handmada {
    class StringRequirement : public IRequirement
    {
    private:
        std::string name_;

    public:
        StringRequirement(const std::string& name);

        virtual const std::string& name() const override;
        virtual AttributeType::Type type() const override;
        virtual std::unique_ptr<Handmada::IAttribute> createAttribute() const override;
        virtual std::unique_ptr<IRequirement> clone() const override;
        virtual void accept(IRequirementVisitor& visitor) const override;

        static std::unique_ptr<IRequirement> create(const std::string& name);
    };


    class NumberRequirement : public IRequirement
    {
    private:
        std::string name_;

    public:
        NumberRequirement(const std::string& name);

        virtual const std::string& name() const override;
        virtual AttributeType::Type type() const override;
        virtual std::unique_ptr<Handmada::IAttribute> createAttribute() const override;
        virtual std::unique_ptr<IRequirement> clone() const override;
        virtual void accept(IRequirementVisitor& visitor) const override;

        static std::unique_ptr<IRequirement> create(const std::string& name);
    };


    class BooleanRequirement : public IRequirement
    {
    private:
        std::string name_;
        std::string question_;

    public:
        BooleanRequirement(const std::string& name, const std::string& question);

        const std::string& question() const;

        virtual const std::string& name() const override;
        virtual AttributeType::Type type() const override;
        virtual std::unique_ptr<IAttribute> createAttribute() const override;
        virtual std::unique_ptr<IRequirement> clone() const override;
        virtual void accept(IRequirementVisitor& visitor) const override;

        static std::unique_ptr<IRequirement> create(
                const std::string& name,
                const std::string& question
        );
    };
}


#endif //EQUEUE_V2_CONCRETEREQUIREMENTS_H
