//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDUSERATTRIBUTERESPONSE_H
#define EQUEUE_V2_ADDUSERATTRIBUTERESPONSE_H


#include "IResponse.h"
#include "IAttribute.h"
#include "PolyVector.h"
#include "Types.h"


namespace Handmada {
    class AddUserAttributeResponse : public IResponse
    {
    private:
        UserId userId_;
        std::vector<std::string> attributes_;

    public:
        AddUserAttributeResponse(UserId userId, std::vector<std::string>&& attributes);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        UserId userId() const;
        const std::vector<std::string>& attributes() const;
        static std::unique_ptr<IResponse> create(
                UserId userId, std::vector<std::string>&& attributes
        );
    };


    class RemoveUserAttributeResponse : public IResponse
    {
    private:
        UserId userId_;
        PolyVector<IAttribute> attributes_;

    public:
        RemoveUserAttributeResponse(UserId userId, PolyVector<IAttribute>&& attributes);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        UserId userId() const;
        const PolyVector<Handmada::IAttribute>& attributes() const;
        static std::unique_ptr<IResponse> create(
                UserId userId, PolyVector<IAttribute>&& attributes
        );
    };
}


#endif //EQUEUE_V2_ADDUSERATTRIBUTERESPONSE_H
