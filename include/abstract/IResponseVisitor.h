//
// Created by syzegno on 19.05.17.
//

#ifndef EQUEUE_V2_IRESPONSEVISITOR_H
#define EQUEUE_V2_IRESPONSEVISITOR_H


#include "Responses.h"


namespace Handmada {
    class IResponseVisitor
    {
    public:
        virtual void visit(const GeneralResponse& response) { }

        virtual void visit(const RegisterUserResponse& response) { }

        virtual void visit(const SignInResponse& response) { }
        virtual void visit(const SignOutResponse& response) { }

        virtual void visit(const AddServiceResponse& response) { }
        virtual void visit(const AddSpecialistResponse& response) { }
        virtual void visit(const AddPriorityRuleResponse& response) { }

        virtual void visit(const AddUserAttributeResponse& response) { }
        virtual void visit(const RemoveUserAttributeResponse& response) { }

        virtual void visit(const AttachSpecialistResponse& response) { }

        virtual void visit(const RequirementCollisionResponse& response) { }

        virtual void visit(const MakeAppointmentResponse& response) { }

        virtual void visit(const MissingAttributeResponse& response) { }

        virtual void visit(const GetMessageResponse& response) { }
        virtual void visit(const GetServiceDescriptorResponse& response) { }
        virtual void visit(const GetSpecialistDescriptorResponse& response) { }
        virtual void visit(const GetUserAttributeResponse& response) { }
        virtual void visit(const GetUserDescriptorResponse& response) { }
        virtual void visit(const GetPriorityRuleResponse& response) { }

        virtual ~IResponseVisitor() { }
    };
}


#endif //EQUEUE_V2_IRESPONSEVISITOR_H
