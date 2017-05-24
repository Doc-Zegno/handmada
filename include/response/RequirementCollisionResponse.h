//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_REQUIREMENTCOLLISIONRESPONSE_H
#define EQUEUE_V2_REQUIREMENTCOLLISIONRESPONSE_H


#include <unordered_map>
#include <memory>
#include <string>

#include "IResponse.h"
#include "AttributeType.h"


namespace Handmada {
    class RequirementCollisionResponse : public IResponse
    {
    private:
        std::unordered_map<std::string, AttributeType::Type> collisions_;

    public:
        RequirementCollisionResponse(decltype(collisions_)&& collisions);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::unordered_map<std::string, AttributeType::Type>& collisions() const;
        static std::unique_ptr<IResponse> create(decltype(collisions_)&& collisions);
    };
}


#endif //EQUEUE_V2_REQUIREMENTCOLLISIONRESPONSE_H
