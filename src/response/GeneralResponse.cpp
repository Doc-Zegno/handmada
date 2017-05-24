//
// Created by syzegno on 19.05.17.
//


#include "GeneralResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GeneralResponse::GeneralResponse(OpCode code)
            : code_(code)
    { }


    OpCode GeneralResponse::code() const
    {
        return code_;
    }


    void GeneralResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    std::unique_ptr<IResponse> GeneralResponse::create(OpCode code)
    {
        return std::unique_ptr<IResponse>(new GeneralResponse(code));
    }
}
