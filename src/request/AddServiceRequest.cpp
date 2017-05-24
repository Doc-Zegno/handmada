//
// Created by syzegno on 13.05.17.
//


#include "AddServiceRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    AddServiceRequest::AddServiceRequest(const std::string& name, const std::string& description)
            : name_(name), description_(description)
    { }


    std::unique_ptr<IRequest> AddServiceRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new AddServiceRequest(name_, description_));
    }


    void AddServiceRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::string& AddServiceRequest::name() const
    {
        return name_;
    }


    const std::string& AddServiceRequest::description() const
    {
        return description_;
    }
}
