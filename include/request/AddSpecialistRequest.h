//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDSPECIALISTREQUEST_H
#define EQUEUE_V2_ADDSPECIALISTREQUEST_H


#include <string>

#include "IRequest.h"


namespace Handmada {
    class AddSpecialistRequest : public IRequest
    {
    private:
        std::string name_;

    public:
        AddSpecialistRequest(const std::string& name);

        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;

        const std::string& name() const;
    };
}


#endif //EQUEUE_V2_ADDSPECIALISTREQUEST_H
