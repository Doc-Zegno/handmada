//
// Created by syzegno on 17.05.17.
//


#include "StreamResponsePrinter.h"
#include "Serializer.h"


namespace Handmada {
    StreamResponsePrinter::StreamResponsePrinter(IStream& stream) : stream_(stream)
    { }


    void StreamResponsePrinter::visit(const GeneralResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GENERAL_RESPONSE);
        Serializer::put(stream_, response.code());
    }


    void StreamResponsePrinter::visit(const RegisterUserResponse& response)
    {
        Serializer::put(stream_, MetaNumber::REGISTER_USER_RESPONSE);
        Serializer::put(stream_, response.userId());
    }


    void StreamResponsePrinter::visit(const SignInResponse& response)
    {
        Serializer::put(stream_, MetaNumber::SIGN_IN_RESPONSE);
        Serializer::put(stream_, response.userId());
    }


    void StreamResponsePrinter::visit(const SignOutResponse& response)
    {
        Serializer::put(stream_, MetaNumber::SIGN_OUT_RESPONSE);
        Serializer::put(stream_, response.login());
    }


    void StreamResponsePrinter::visit(const AddServiceResponse& response)
    {
        Serializer::put(stream_, MetaNumber::ADD_SERVICE_RESPONSE);
        Serializer::put(stream_, response.serviceId());
    }


    void StreamResponsePrinter::visit(const AddSpecialistResponse& response)
    {
        Serializer::put(stream_, MetaNumber::ADD_SPECIALIST_RESPONSE);
        Serializer::put(stream_, response.specialistId());
    }


    void StreamResponsePrinter::visit(const AddPriorityRuleResponse& response)
    {
        Serializer::put(stream_, MetaNumber::ADD_PRIORITY_RULE_RESPONSE);
        Serializer::put(stream_, response.serviceId());
        Serializer::put(stream_, response.predicateId());
    }


    void StreamResponsePrinter::visit(const AddUserAttributeResponse& response)
    {
        Serializer::put(stream_, MetaNumber::ADD_USER_ATTRIBUTE_RESPONSE);
        Serializer::put(stream_, response.userId());
        Serializer::put(stream_, response.attributes());
    }


    void StreamResponsePrinter::visit(const RemoveUserAttributeResponse& response)
    {
        Serializer::put(stream_, MetaNumber::REMOVE_USER_ATTRIBUTE_RESPONSE);
        Serializer::put(stream_, response.userId());
        Serializer::put(stream_, response.attributes());
    }


    void StreamResponsePrinter::visit(const AttachSpecialistResponse& response)
    {
        Serializer::put(stream_, MetaNumber::ATTACH_SPECIALIST_RESPONSE);
        Serializer::put(stream_, response.specialistId());
        Serializer::put(stream_, response.serviceId());
    }


    void StreamResponsePrinter::visit(const RequirementCollisionResponse& response)
    {
        Serializer::put(stream_, MetaNumber::REQUIREMENT_COLLISION_RESPONSE);
        Serializer::put(stream_, response.collisions());
    }


    void StreamResponsePrinter::visit(const MakeAppointmentResponse& response)
    {
        Serializer::put(stream_, MetaNumber::MAKE_APPOINTMENT_RESPONSE);
        Serializer::put(stream_, response.userId());
        Serializer::put(stream_, response.serviceId());
        Serializer::put(stream_, response.hasPriority());
    }


    void StreamResponsePrinter::visit(const MissingAttributeResponse& response)
    {
        Serializer::put(stream_, MetaNumber::MISSING_ATTRIBUTE_RESPONSE);
        Serializer::put(stream_, response.requirements());
    }


    void StreamResponsePrinter::visit(const GetMessageResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GET_MESSAGE_RESPONSE);
        Serializer::put(stream_, response.messages());
    }


    void StreamResponsePrinter::visit(const GetServiceDescriptorResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GET_SERVICE_DESCRIPTOR_RESPONSE);
        Serializer::put(stream_, response.descriptors());
    }


    void StreamResponsePrinter::visit(const GetSpecialistDescriptorResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GET_SPECIALIST_DESCRIPTOR_RESPONSE);
        Serializer::put(stream_, response.descriptors());
    }


    void StreamResponsePrinter::visit(const GetUserAttributeResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GET_USER_ATTRIBUTE_RESPONSE);
        Serializer::put(stream_, response.attributes());
    }


    void StreamResponsePrinter::visit(const GetUserDescriptorResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GET_USER_DESCRIPTOR_RESPONSE);
        Serializer::put(stream_, response.descriptors());
    }


    void StreamResponsePrinter::visit(const GetPriorityRuleResponse& response)
    {
        Serializer::put(stream_, MetaNumber::GET_PRIORITY_RULE_RESPONSE);
        Serializer::put(stream_, response.descriptors());
    }
}
