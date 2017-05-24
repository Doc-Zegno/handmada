//
// Created by syzegno on 14.05.17.
//


#include "AddServiceResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    AddServiceResponse::AddServiceResponse(ServiceId serviceId) : serviceId_(serviceId)
    { }


    OpCode AddServiceResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void AddServiceResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    ServiceId AddServiceResponse::serviceId() const
    {
        return serviceId_;
    }


    std::unique_ptr<IResponse> AddServiceResponse::create(ServiceId serviceId)
    {
        return std::unique_ptr<IResponse>(new AddServiceResponse(serviceId));
    }
}


