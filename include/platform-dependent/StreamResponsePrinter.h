//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_STREAMRESPONSEPRINTER_H
#define EQUEUE_V2_STREAMRESPONSEPRINTER_H


#include "IResponseVisitor.h"
#include "IStream.h"


namespace Handmada {
    class StreamResponsePrinter : public IResponseVisitor
    {
    private:
        IStream& stream_;

    public:
        StreamResponsePrinter(IStream& stream);

        virtual void visit(const GeneralResponse& response) override;
        virtual void visit(const RegisterUserResponse& response) override;
        virtual void visit(const SignInResponse& response) override;
        virtual void visit(const SignOutResponse& response) override;
        virtual void visit(const AddServiceResponse& response) override;
        virtual void visit(const AddSpecialistResponse& response) override;
        virtual void visit(const AddPriorityRuleResponse& response) override;
        virtual void visit(const AddUserAttributeResponse& response) override;
        virtual void visit(const RemoveUserAttributeResponse& response) override;
        virtual void visit(const AttachSpecialistResponse& response) override;
        virtual void visit(const RequirementCollisionResponse& response) override;
        virtual void visit(const MakeAppointmentResponse& response) override;
        virtual void visit(const MissingAttributeResponse& response) override;
        virtual void visit(const GetMessageResponse& response) override;
        virtual void visit(const GetServiceDescriptorResponse& response) override;
        virtual void visit(const GetSpecialistDescriptorResponse& response) override;
        virtual void visit(const GetUserAttributeResponse& response) override;
        virtual void visit(const GetUserDescriptorResponse& response) override;
        virtual void visit(const GetPriorityRuleResponse& response) override;
    };
}


#endif //EQUEUE_V2_STREAMRESPONSEPRINTER_H
