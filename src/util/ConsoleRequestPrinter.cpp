//
// Created by syzegno on 15.05.17.
//


#include "ConsoleRequestPrinter.h"
#include "PredicatePrinter.h"
#include "AttributePrinter.h"


namespace Handmada {
    ConsoleRequestPrinter::ConsoleRequestPrinter(Console* console) : console_(console)
    { }


    void ConsoleRequestPrinter::visit(const RegisterUserRequest& request)
    {
        console_->out("register ", request.login());
    }


    void ConsoleRequestPrinter::visit(const SignInRequest& request)
    {
        console_->out("sign in ", request.login());
    }


    void ConsoleRequestPrinter::visit(const SignOutRequest& request)
    {
        console_->out("sign out");
    }


    void ConsoleRequestPrinter::visit(const AddServiceRequest& request)
    {
        console_->out("add service");
        console_->out("\tname: ", request.name());
        console_->out("\tdescription: ", request.description());
    }


    void ConsoleRequestPrinter::visit(const AddSpecialistRequest& request)
    {
        console_->out("add specialist");
        console_->out("\tname: ", request.name());
    }


    void ConsoleRequestPrinter::visit(const AddPriorityRuleRequest& request)
    {
        console_->out("add rule");
        PredicatePrinter printer(console_->outStream(), 1);
        request.predicate().accept(printer);
    }


    void ConsoleRequestPrinter::visit(const AddUserAttributeRequest& request)
    {
        console_->out("add attributes");
        AttributePrinter printer(console_->outStream());
        for (auto& attribute : request.attributes()) {
            console_->outNoLine('\t');
            attribute->accept(printer);
        }
    }


    void ConsoleRequestPrinter::visit(const RemoveUserAttributeRequest& request)
    {
        console_->out("remove attributes");
        for (auto& name : request.attributes()) {
            console_->out('\t', name);
        }
    }


    void ConsoleRequestPrinter::visit(const AttachSpecialistRequest& request)
    {
        console_->out("attach specialist");
        console_->out("\tspecialist ID: ", request.specialistId());
        console_->out("\tservice ID: ", request.serviceId());
    }


    void ConsoleRequestPrinter::visit(const MakeAppointmentRequest& request)
    {
        console_->out("book ", request.serviceId());
    }


    void ConsoleRequestPrinter::visit(const GetMessageRequest& request)
    {
        console_->out("get messages");
    }


    void ConsoleRequestPrinter::visit(const GetServiceDescriptorRequest& request)
    {
        console_->out("get services");
    }


    void ConsoleRequestPrinter::visit(const GetSpecialistDescriptorRequest& request)
    {
        console_->out("get specialists");
        if (isServiceIdValid(request.serviceId())) {
            console_->out("\tservice ID: ", request.serviceId());
        }
    }


    void ConsoleRequestPrinter::visit(const GetUserAttributeRequest& request)
    {
        console_->out("get attributes");
    }


    void ConsoleRequestPrinter::visit(const GetUserDescriptorRequest& request)
    {
        console_->out("get queue");
        console_->out("\tservice ID: ", request.serviceId());
    }


    void ConsoleRequestPrinter::visit(const GetPriorityRuleRequest& request)
    {
        console_->out("get rules");
        console_->out("\tservice ID: ", request.serviceId());
    }
}
