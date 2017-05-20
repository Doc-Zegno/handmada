//
// Created by syzegno on 23.04.17.
//

#ifndef EQUEUE_V2_SYSTEM_H
#define EQUEUE_V2_SYSTEM_H


#include "IFrontend.h"
#include "IRequestVisitor.h"
#include "IDataBaseController.h"
#include "IAttribute.h"
#include "Types.h"


namespace Handmada {
    /**
     * The main implementor of IFrontend interface.
     * Processes requests and interacts with data base through controller
     */
    class BasicFrontend : public IFrontend, public IRequestVisitor
    {
    private:
        IDataBaseController* controller_;
        std::unique_ptr<IResponse> response_;

        ServiceId generateServiceId() const;
        SpecialistId generateSpecialistId() const;
        PredicateId generatePredicateId(ServiceId id) const;
        void addMessageForUser(UserId userId, ServiceId serviceId, Specialist* specialist);

    public:
        BasicFrontend(IDataBaseController* controller);

        virtual std::unique_ptr<IResponse> acceptRequest(
                const IRequest& request
        ) override;

        virtual void visit(const SignInRequest& request) override;
        virtual void visit(const RegisterUserRequest& request) override;
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

        void runServices();
    };
}


#endif //EQUEUE_V2_SYSTEM_H
