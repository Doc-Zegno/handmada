//
// Created by syzegno on 14.05.17.
//


#include "AddSpecialistRequest.h"
#include "IRequestVisitor.h"


namespace Handmada {
    AddSpecialistRequest::AddSpecialistRequest(const std::string& name)
            : name_(name)
    { }


    std::unique_ptr<IRequest> AddSpecialistRequest::clone() const
    {
        return std::unique_ptr<IRequest>(new AddSpecialistRequest(name_));
    }


    void AddSpecialistRequest::accept(IRequestVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::string& AddSpecialistRequest::name() const
    {
        return name_;
    }
}
