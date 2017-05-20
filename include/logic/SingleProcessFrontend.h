//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_SINGLEPROCESSFRONTEND_H
#define EQUEUE_V2_SINGLEPROCESSFRONTEND_H


#include "BasicFrontend.h"


namespace Handmada {
    /**
     * Test version of frontend
     */
    class SingleProcessFrontend : public BasicFrontend
    {
    public:
        SingleProcessFrontend(IDataBaseController* controller);

        virtual std::unique_ptr<IResponse> acceptRequest(const IRequest& request) override;
    };
}


#endif //EQUEUE_V2_SINGLEPROCESSFRONTEND_H
