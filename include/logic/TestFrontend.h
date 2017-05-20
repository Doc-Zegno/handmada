//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_TESTFRONTEND_H
#define EQUEUE_V2_TESTFRONTEND_H


#include "BasicFrontend.h"
#include "Serializer.h"
#include "DynamicBufferStream.h"


namespace Handmada {
    /**
     * Test version of frontend
     */
    class TestFrontend : public BasicFrontend
    {
    private:
        DynamicBufferStream stream_;

    public:
        TestFrontend(IDataBaseController* controller);

        virtual std::unique_ptr<IResponse> acceptRequest(const IRequest& request) override;
    };
}


#endif //EQUEUE_V2_TESTFRONTEND_H
