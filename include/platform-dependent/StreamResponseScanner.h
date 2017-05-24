//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_STREAMRESPONSESCANNER_H
#define EQUEUE_V2_STREAMRESPONSESCANNER_H


#include <memory>
#include <stdexcept>

#include "IResponse.h"
#include "IStream.h"


namespace Handmada {
    class StreamResponseScannerException : public std::runtime_error
    {
    public:
        StreamResponseScannerException(const std::string& info);
    };


    class StreamResponseScanner
    {
    private:
        IStream& stream_;

        std::unique_ptr<IResponse> getAddPriorityRuleResponse() const;
        std::unique_ptr<IResponse> getAddServiceResponse() const;
        std::unique_ptr<IResponse> getAddSpecialistResponse() const;
        std::unique_ptr<IResponse> getAddUserAttributeResponse() const;
        std::unique_ptr<IResponse> getRemoveUserAttributeResponse() const;
        std::unique_ptr<IResponse> getAttachSpecialistResponse() const;
        std::unique_ptr<IResponse> getGeneralResponse() const;
        std::unique_ptr<IResponse> getGetMessageResponse() const;
        std::unique_ptr<IResponse> getGetPriorityRuleResponse() const;
        std::unique_ptr<IResponse> getGetServiceDescriptorResponse() const;
        std::unique_ptr<IResponse> getGetSpecialistDescriptorResponse() const;
        std::unique_ptr<IResponse> getGetUserAttributeResponse() const;
        std::unique_ptr<IResponse> getGetUserDescriptorResponse() const;
        std::unique_ptr<IResponse> getMakeAppointmentResponse() const;
        std::unique_ptr<IResponse> getMissingAttributeResponse() const;
        std::unique_ptr<IResponse> getRegisterUserResponse() const;
        std::unique_ptr<IResponse> getRequirementCollisionResponse() const;
        std::unique_ptr<IResponse> getSignInResponse() const;
        std::unique_ptr<IResponse> getSignOutResponse() const;

    public:
        StreamResponseScanner(IStream& stream);

        std::unique_ptr<IResponse> getNext() const;
    };
}


#endif //EQUEUE_V2_STREAMRESPONSESCANNER_H
