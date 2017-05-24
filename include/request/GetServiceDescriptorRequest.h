//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_GETSERVICEDESCRIPTORREQUEST_H
#define EQUEUE_V2_GETSERVICEDESCRIPTORREQUEST_H


#include "IRequest.h"
#include "Types.h"


namespace Handmada {
    class GetServiceDescriptorRequest : public IRequest
    {
    public:
        virtual std::unique_ptr<IRequest> clone() const override;
        virtual void accept(IRequestVisitor& visitor) const override;
    };
}


#endif //EQUEUE_V2_GETSERVICEDESCRIPTORREQUEST_H
