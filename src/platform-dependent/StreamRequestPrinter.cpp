//
// Created by syzegno on 17.05.17.
//


#include "StreamRequestPrinter.h"
#include "MetaNumber.h"
#include "Serializer.h"


namespace Handmada {
    StreamRequestPrinter::StreamRequestPrinter(IStream& stream) : stream_(stream)
    { }


    void StreamRequestPrinter::visit(const RegisterUserRequest& request)
    {
        Serializer::put(stream_, MetaNumber::REGISTER_USER_REQUEST);
        Serializer::put(stream_, request.login());
    }


    void StreamRequestPrinter::visit(const SignInRequest& request)
    {
        Serializer::put(stream_, MetaNumber::SIGN_IN_REQUEST);
        Serializer::put(stream_, request.login());
    }


    void StreamRequestPrinter::visit(const SignOutRequest& request)
    {
        Serializer::put(stream_, MetaNumber::SIGN_OUT_REQUEST);
        Serializer::put(stream_, request.userId());
    }


    void StreamRequestPrinter::visit(const AddServiceRequest& request)
    {
        Serializer::put(stream_, MetaNumber::ADD_SERVICE_REQUEST);
        Serializer::put(stream_, request.name());
        Serializer::put(stream_, request.description());
    }


    void StreamRequestPrinter::visit(const AddSpecialistRequest& request)
    {
        Serializer::put(stream_, MetaNumber::ADD_SPECIALIST_REQUEST);
        Serializer::put(stream_, request.name());
    }


    void StreamRequestPrinter::visit(const AddPriorityRuleRequest& request)
    {
        Serializer::put(stream_, MetaNumber::ADD_PRIORITY_RULE_REQUEST);
        Serializer::put(stream_, request.serviceId());
        Serializer::put(stream_, request.predicate());
        Serializer::put(stream_, request.requirements());
    }


    void StreamRequestPrinter::visit(const AddUserAttributeRequest& request)
    {
        Serializer::put(stream_, MetaNumber::ADD_USER_ATTRIBUTE_REQUEST);
        Serializer::put(stream_, request.userId());
        Serializer::put(stream_, request.attributes());
    }


    void StreamRequestPrinter::visit(const RemoveUserAttributeRequest& request)
    {
        Serializer::put(stream_, MetaNumber::REMOVE_USER_ATTRIBUTE_REQUEST);
        Serializer::put(stream_, request.userId());
        Serializer::put(stream_, request.attributes());
    }


    void StreamRequestPrinter::visit(const AttachSpecialistRequest& request)
    {
        Serializer::put(stream_, MetaNumber::ATTACH_SPECIALIST_REQUEST);
        Serializer::put(stream_, request.specialistId());
        Serializer::put(stream_, request.serviceId());
    }


    void StreamRequestPrinter::visit(const MakeAppointmentRequest& request)
    {
        Serializer::put(stream_, MetaNumber::MAKE_APPOINTMENT_REQUEST);
        Serializer::put(stream_, request.userId());
        Serializer::put(stream_, request.serviceId());
    }


    void StreamRequestPrinter::visit(const GetMessageRequest& request)
    {
        Serializer::put(stream_, MetaNumber::GET_MESSAGE_REQUEST);
        Serializer::put(stream_, request.userId());
    }


    void StreamRequestPrinter::visit(const GetServiceDescriptorRequest& request)
    {
        Serializer::put(stream_, MetaNumber::GET_SERVICE_DESCRIPTOR_REQUEST);
    }


    void StreamRequestPrinter::visit(const GetSpecialistDescriptorRequest& request)
    {
        Serializer::put(stream_, MetaNumber::GET_SPECIALIST_DESCRIPTOR_REQUEST);
        Serializer::put(stream_, request.serviceId());
    }


    void StreamRequestPrinter::visit(const GetUserAttributeRequest& request)
    {
        Serializer::put(stream_, MetaNumber::GET_USER_ATTRIBUTE_REQUEST);
        Serializer::put(stream_, request.userId());
    }


    void StreamRequestPrinter::visit(const GetUserDescriptorRequest& request)
    {
        Serializer::put(stream_, MetaNumber::GET_USER_DESCRIPTOR_REQUEST);
        Serializer::put(stream_, request.serviceId());
    }


    void StreamRequestPrinter::visit(const GetPriorityRuleRequest& request)
    {
        Serializer::put(stream_, MetaNumber::GET_PRIORITY_RULE_REQUEST);
        Serializer::put(stream_, request.serviceId());
    }
}
