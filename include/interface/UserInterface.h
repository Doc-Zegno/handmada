//
// Created by syzegno on 20.05.17.
//

#ifndef EQUEUE_V2_USERINTERFACE_H
#define EQUEUE_V2_USERINTERFACE_H


#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "IFrontend.h"
#include "IResponseVisitor.h"
#include "IRequirementVisitor.h"
#include "IUndoList.h"
#include "Console.h"
#include "Requests.h"
#include "Types.h"
#include "SimpleUndoList.h"
#include "NullUndoList.h"


namespace Handmada {
    class UserInterface : public IResponseVisitor
    {
    private:
        Console console_;

        IFrontend* frontend_;
        UserId userId_;
        std::string login_;
        ServiceId serviceId_;
        std::vector<std::string> args_;
        const char* usage_;

        IUndoList* undoList_;
        Prefab::SimpleUndoList simpleUndoList_;
        Prefab::NullUndoList nullUndoList_;


        static std::unordered_map<
                std::string, std::pair<std::string, void (UserInterface::*)(void)>
        > signedOutCommands_;
        static std::unordered_map<
                std::string, std::pair<std::string, void (UserInterface::*)(void)>
        > signedInCommands_;

        const decltype(signedOutCommands_)* commands_;

        void sign();
        void makeSignRequest(const IRequest& request, bool isSignedIn, const std::string& failureMessage);
        void get();
        void add();
        void addAttributes();
        void remove();
        void removeAttributes();
        void book();
        void undo();
        void help();
        void usage();

    public:
        UserInterface(IFrontend* frontend, std::istream& in, std::ostream& out, std::ostream& err);

        void run();

        virtual void visit(const GeneralResponse& response) override;
        virtual void visit(const RegisterUserResponse& response) override;
        virtual void visit(const SignInResponse& response) override;
        virtual void visit(const SignOutResponse& response) override;

        virtual void visit(const AddUserAttributeResponse& response) override;
        virtual void visit(const RemoveUserAttributeResponse& response) override;

        virtual void visit(const MakeAppointmentResponse& response) override;
        virtual void visit(const MissingAttributeResponse& response) override;
        virtual void visit(const GetMessageResponse& response) override;
        virtual void visit(const GetServiceDescriptorResponse& response) override;
        virtual void visit(const GetUserAttributeResponse& response) override;
        virtual void visit(const GetUserDescriptorResponse& response) override;
        virtual void visit(const GetPriorityRuleResponse& response) override;

        virtual void visit(const GetSpecialistDescriptorResponse& response) override;
    };
}


#endif //EQUEUE_V2_USERINTERFACE_H
