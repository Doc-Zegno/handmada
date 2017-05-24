//
// Created by syzegno on 21.05.17.
//

#ifndef EQUEUE_V2_MISSINGATTRIBUTERESPONSE_H
#define EQUEUE_V2_MISSINGATTRIBUTERESPONSE_H


#include "IResponse.h"
#include "IRequirement.h"
#include "PolyVector.h"


namespace Handmada {
    class MissingAttributeResponse : public IResponse
    {
    private:
        PolyVector<IRequirement> requirements_;

    public:
        MissingAttributeResponse(PolyVector<IRequirement>&& requirements);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const PolyVector<IRequirement>& requirements() const;
        static std::unique_ptr<IResponse> create(PolyVector<IRequirement>&& requirements);
    };
}


#endif //EQUEUE_V2_MISSINGATTRIBUTERESPONSE_H
