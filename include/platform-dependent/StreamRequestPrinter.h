//
// Created by syzegno on 17.05.17.
//

#ifndef EQUEUE_V2_STREAMREQUESTPRINTER_H
#define EQUEUE_V2_STREAMREQUESTPRINTER_H


#include "IRequestVisitor.h"
#include "IStream.h"


namespace Handmada {
    class StreamRequestPrinter : public IRequestVisitor
    {
    private:
        IStream& stream_;

    public:
        StreamRequestPrinter(IStream& stream);

        virtual void visit(const RegisterUserRequest& request) override;
        virtual void visit(const SignInRequest& request) override;
        virtual void visit(const SignOutRequest& request) override;
        virtual void visit(const AddServiceRequest& request) override;
        virtual void visit(const AddSpecialistRequest& request) override;
        virtual void visit(const AddPriorityRuleRequest& request) override;
        virtual void visit(const AddUserAttributeRequest& request) override;
        virtual void visit(const RemoveUserAttributeRequest& request) override;
        virtual void visit(const AttachSpecialistRequest& request) override;
        virtual void visit(const MakeAppointmentRequest& request) override;
        virtual void visit(const GetMessageRequest& request) override;
        virtual void visit(const GetServiceDescriptorRequest& request) override;
        virtual void visit(const GetSpecialistDescriptorRequest& request) override;
        virtual void visit(const GetUserAttributeRequest& request) override;
        virtual void visit(const GetUserDescriptorRequest& request) override;
        virtual void visit(const GetPriorityRuleRequest& request) override;
    };
}


#endif //EQUEUE_V2_STREAMREQUESTPRINTER_H
