//
// Created by syzegno on 15.05.17.
//


#include "SingleProcessFrontend.h"


namespace Handmada {
    SingleProcessFrontend::SingleProcessFrontend(IDataBaseController* controller)
            : BasicFrontend(controller)
    { }


    std::unique_ptr<IResponse> SingleProcessFrontend::acceptRequest(const IRequest& request)
    {
        runServices();
        return BasicFrontend::acceptRequest(request);
    }
}

