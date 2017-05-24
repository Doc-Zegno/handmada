//
// Created by syzegno on 17.05.17.
//


#include "TestFrontend.h"


namespace Handmada {
    TestFrontend::TestFrontend(IDataBaseController* controller)
            : BasicFrontend(controller)
    { }


    std::unique_ptr<IResponse> TestFrontend::acceptRequest(const IRequest& request)
    {
        stream_.seek(0);
        Serializer::put(stream_, request);

        stream_.seek(0);
        std::unique_ptr<IRequest> copyRequest;
        Serializer::get(stream_, copyRequest);

        auto response = BasicFrontend::acceptRequest(*copyRequest);
        stream_.seek(0);
        Serializer::put(stream_, response);

        stream_.seek(0);
        std::unique_ptr<IResponse> copyResponse;
        Serializer::get(stream_, copyResponse);

        return std::move(copyResponse);
    }
}
