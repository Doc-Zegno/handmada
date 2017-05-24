//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETUSERATTRIBUTERESPONSE_H
#define EQUEUE_V2_GETUSERATTRIBUTERESPONSE_H


#include "IResponse.h"
#include "PolyVector.h"
#include "IAttribute.h"


namespace Handmada {
    class GetUserAttributeResponse : public IResponse
    {
    private:
        PolyVector<IAttribute> attributes_;

    public:
        GetUserAttributeResponse(PolyVector<IAttribute>&& attributes);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const PolyVector<Handmada::IAttribute>& attributes() const;
        static std::unique_ptr<IResponse> create(PolyVector<IAttribute>&& attributes);
    };
}


#endif //EQUEUE_V2_GETUSERATTRIBUTERESPONSE_H
