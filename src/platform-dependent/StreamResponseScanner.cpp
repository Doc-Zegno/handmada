//
// Created by syzegno on 17.05.17.
//


#include "StreamResponseScanner.h"
#include "Serializer.h"
#include "Responses.h"


namespace Handmada {
    StreamResponseScannerException::StreamResponseScannerException(
            const std::string& info
    ) : runtime_error(info)
    { }


    StreamResponseScanner::StreamResponseScanner(IStream& stream) : stream_(stream)
    { }


    std::unique_ptr<IResponse> StreamResponseScanner::getNext() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);

        switch (meta) {
        case MetaNumber::ADD_PRIORITY_RULE_RESPONSE:
            return getAddPriorityRuleResponse();

        case MetaNumber::ADD_SERVICE_RESPONSE:
            return getAddServiceResponse();

        case MetaNumber::ADD_SPECIALIST_RESPONSE:
            return getAddSpecialistResponse();

        case MetaNumber::ADD_USER_ATTRIBUTE_RESPONSE:
            return getAddUserAttributeResponse();

        case MetaNumber::REMOVE_USER_ATTRIBUTE_RESPONSE:
            return getRemoveUserAttributeResponse();

        case MetaNumber::ATTACH_SPECIALIST_RESPONSE:
            return getAttachSpecialistResponse();

        case MetaNumber::GENERAL_RESPONSE:
            return getGeneralResponse();

        case MetaNumber::GET_MESSAGE_RESPONSE:
            return getGetMessageResponse();

        case MetaNumber::GET_PRIORITY_RULE_RESPONSE:
            return getGetPriorityRuleResponse();

        case MetaNumber::GET_SERVICE_DESCRIPTOR_RESPONSE:
            return getGetServiceDescriptorResponse();

        case MetaNumber::GET_SPECIALIST_DESCRIPTOR_RESPONSE:
            return getGetSpecialistDescriptorResponse();

        case MetaNumber::GET_USER_ATTRIBUTE_RESPONSE:
            return getGetUserAttributeResponse();

        case MetaNumber::GET_USER_DESCRIPTOR_RESPONSE:
            return getGetUserDescriptorResponse();

        case MetaNumber::MAKE_APPOINTMENT_RESPONSE:
            return getMakeAppointmentResponse();

        case MetaNumber::MISSING_ATTRIBUTE_RESPONSE:
            return getMissingAttributeResponse();

        case MetaNumber::REGISTER_USER_RESPONSE:
            return getRegisterUserResponse();

        case MetaNumber::REQUIREMENT_COLLISION_RESPONSE:
            return getRequirementCollisionResponse();

        case MetaNumber::SIGN_IN_RESPONSE:
            return getSignInResponse();

        case MetaNumber::SIGN_OUT_RESPONSE:
            return getSignOutResponse();

        default:
            throw StreamResponseScannerException("unknown meta");
        }
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getAddPriorityRuleResponse() const
    {
        ServiceId serviceId;
        PredicateId predicateId;

        Serializer::get(stream_, serviceId);
        Serializer::get(stream_, predicateId);

        return AddPriorityRuleResponse::create(serviceId, predicateId);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getAddServiceResponse() const
    {
        ServiceId serviceId;
        Serializer::get(stream_, serviceId);
        return AddServiceResponse::create(serviceId);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getAddSpecialistResponse() const
    {
        SpecialistId specialistId;
        Serializer::get(stream_, specialistId);
        return AddSpecialistResponse::create(specialistId);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getAddUserAttributeResponse() const
    {
        UserId userId;
        std::vector<std::string> attributes;

        Serializer::get(stream_, userId);
        Serializer::get(stream_, attributes);

        return AddUserAttributeResponse::create(userId, std::move(attributes));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getRemoveUserAttributeResponse() const
    {
        UserId userId;
        PolyVector<IAttribute> attributes;

        Serializer::get(stream_, userId);
        Serializer::get(stream_, attributes);

        return RemoveUserAttributeResponse::create(userId, std::move(attributes));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getAttachSpecialistResponse() const
    {
        SpecialistId specialistId;
        ServiceId serviceId;

        Serializer::get(stream_, specialistId);
        Serializer::get(stream_, serviceId);

        return AttachSpecialistResponse::create(specialistId, serviceId);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGeneralResponse() const
    {
        OpCode code;
        Serializer::get(stream_, code);
        return GeneralResponse::create(code);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGetMessageResponse() const
    {
        std::vector<Message> messages;
        Serializer::get(stream_, messages);
        return GetMessageResponse::create(std::move(messages));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGetPriorityRuleResponse() const
    {
        std::vector<SmallPredicateDescriptor> descriptors;
        Serializer::get(stream_, descriptors);
        return GetPriorityRuleResponse::create(std::move(descriptors));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGetServiceDescriptorResponse() const
    {
        std::vector<ServiceDescriptor> descriptors;
        Serializer::get(stream_, descriptors);
        return GetServiceDescriptorResponse::create(std::move(descriptors));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGetSpecialistDescriptorResponse() const
    {
        std::vector<SpecialistDescriptor> descriptors;
        Serializer::get(stream_, descriptors);
        return GetSpecialistDescriptorResponse::create(std::move(descriptors));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGetUserAttributeResponse() const
    {
        PolyVector<IAttribute> attributes;
        Serializer::get(stream_, attributes);
        return GetUserAttributeResponse::create(std::move(attributes));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getGetUserDescriptorResponse() const
    {
        std::vector<UserDescriptor> descriptors;
        Serializer::get(stream_, descriptors);
        return GetUserDescriptorResponse::create(std::move(descriptors));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getMakeAppointmentResponse() const
    {
        UserId userId;
        ServiceId serviceId;
        bool hasPriority;

        Serializer::get(stream_, userId);
        Serializer::get(stream_, serviceId);
        Serializer::get(stream_, hasPriority);

        return MakeAppointmentResponse::create(userId, serviceId, hasPriority);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getMissingAttributeResponse() const
    {
        PolyVector<IRequirement> requirements;
        Serializer::get(stream_, requirements);
        return MissingAttributeResponse::create(std::move(requirements));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getRegisterUserResponse() const
    {
        UserId userId;
        Serializer::get(stream_, userId);
        return RegisterUserResponse::create(userId);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getRequirementCollisionResponse() const
    {
        std::unordered_map<std::string, AttributeType::Type> collisions;
        Serializer::get(stream_, collisions);
        return RequirementCollisionResponse::create(std::move(collisions));
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getSignInResponse() const
    {
        UserId userId;
        Serializer::get(stream_, userId);
        return SignInResponse::create(userId);
    }


    std::unique_ptr<IResponse> StreamResponseScanner::getSignOutResponse() const
    {
        std::string login;
        Serializer::get(stream_, login);
        return SignOutResponse::create(login);
    }
}
