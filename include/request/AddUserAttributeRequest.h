//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDUSERATTRIBUTEREQUEST_H
#define EQUEUE_V2_ADDUSERATTRIBUTEREQUEST_H


#include "IRequest.h"
#include "IAttribute.h"
#include "PolyVector.h"
#include "Types.h"


namespace Handmada {
    class AddUserAttributeRequest : public IRequest
    {
    private:
        UserId userId_;
        PolyVector<IAttribute> attributes_;

    public:
        AddUserAttributeRequest(
                UserId userId,
                PolyVector<IAttribute>&& attributes
        );

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        UserId userId() const;
        const PolyVector<IAttribute>& attributes() const;
    };


    class RemoveUserAttributeRequest : public IRequest
    {
    private:
        UserId userId_;
        std::vector<std::string> attributes_;

    public:
        RemoveUserAttributeRequest(
                UserId userId,
                std::vector<std::string>&& attributes
        );

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        UserId userId() const;
        const std::vector<std::string>& attributes() const;
    };
}


#endif //EQUEUE_V2_ADDUSERATTRIBUTEREQUEST_H
