//
// Created by syzegno on 13.05.17.
//

#ifndef EQUEUE_V2_ADDREQUEST_H
#define EQUEUE_V2_ADDREQUEST_H


#include <string>

#include "IRequest.h"


namespace Handmada {
    class AddServiceRequest : public IRequest
    {
    private:
        std::string name_;
        std::string description_;

    public:
        AddServiceRequest(const std::string& name, const std::string& description);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        const std::string& name() const;
        const std::string& description() const;
    };
}


#endif //EQUEUE_V2_ADDREQUEST_H
