//
// Created by syzegno on 14.05.17.
//


#include "RequirementCollisionResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    RequirementCollisionResponse::RequirementCollisionResponse(
            decltype(collisions_)&& collisions
    ) : collisions_(std::move(collisions))
    { }


    OpCode RequirementCollisionResponse::code() const
    {
        return OpCode::REQUIREMENT_TYPE_COLLISION;
    }


    void RequirementCollisionResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::unordered_map<std::string, AttributeType::Type>&
    RequirementCollisionResponse::collisions() const
    {
        return collisions_;
    }


    std::unique_ptr<IResponse> RequirementCollisionResponse::create(
            std::unordered_map<std::string, AttributeType::Type>&& collisions
    )
    {
        return std::unique_ptr<IResponse>(new RequirementCollisionResponse(std::move(collisions)));
    }
}
