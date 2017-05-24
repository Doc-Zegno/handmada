//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IREQUESTVISITOR_H
#define EQUEUE_V2_IREQUESTVISITOR_H


#include "Requests.h"


namespace Handmada {
    class IRequestVisitor
    {
    public:
        virtual void visit(const RegisterUserRequest& request) = 0;

        virtual void visit(const SignInRequest& request) = 0;
        virtual void visit(const SignOutRequest& request) = 0;

        virtual void visit(const AddServiceRequest& request) = 0;
        virtual void visit(const AddSpecialistRequest& request) = 0;
        virtual void visit(const AddPriorityRuleRequest& request) = 0;

        virtual void visit(const AddUserAttributeRequest& request) = 0;
        virtual void visit(const RemoveUserAttributeRequest& request) = 0;

        virtual void visit(const AttachSpecialistRequest& request) = 0;

        virtual void visit(const MakeAppointmentRequest& request) = 0;

        virtual void visit(const GetMessageRequest& request) = 0;
        virtual void visit(const GetServiceDescriptorRequest& request) = 0;
        virtual void visit(const GetSpecialistDescriptorRequest& request) = 0;
        virtual void visit(const GetUserAttributeRequest& request) = 0;
        virtual void visit(const GetUserDescriptorRequest& request) = 0;
        virtual void visit(const GetPriorityRuleRequest& request) = 0;

        virtual ~IRequestVisitor() { }
    };
}


#endif //EQUEUE_V2_IREQUESTVISITOR_H
