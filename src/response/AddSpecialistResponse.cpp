//
// Created by syzegno on 14.05.17.
//


#include "AddSpecialistResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    AddSpecialistResponse::AddSpecialistResponse(SpecialistId specialistId)
            : specialistId_(specialistId)
    { }


    OpCode AddSpecialistResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void AddSpecialistResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    SpecialistId AddSpecialistResponse::specialistId() const
    {
        return specialistId_;
    }


    std::unique_ptr<IResponse> AddSpecialistResponse::create(SpecialistId specialistId)
    {
        return std::unique_ptr<IResponse>(new AddSpecialistResponse(specialistId));
    }
}
