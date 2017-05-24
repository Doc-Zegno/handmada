//
// Created by syzegno on 17.05.17.
//


#include "StreamRequestScanner.h"
#include "Requests.h"
#include "MetaNumber.h"
#include "Serializer.h"


namespace Handmada {
    StreamRequestScannerException::StreamRequestScannerException(const std::string& info)
            : runtime_error(info)
    { }


    StreamRequestScanner::StreamRequestScanner(IStream& stream) : stream_(stream)
    { }


    std::unique_ptr<IRequest> StreamRequestScanner::getNext() const
    {
        MetaNumber::Type meta;
        Serializer::get(stream_, meta);

        switch (meta) {
        case MetaNumber::ADD_PRIORITY_RULE_REQUEST: {
            ServiceId serviceId;
            std::unique_ptr<IPredicate> predicate;
            PolyVector<IRequirement> requirements;

            Serializer::get(stream_, serviceId);
            Serializer::get(stream_, predicate);
            Serializer::get(stream_, requirements);

            return std::unique_ptr<IRequest>(
                    new AddPriorityRuleRequest(
                            serviceId, std::move(predicate), std::move(requirements)
                    )
            );
        }


        case MetaNumber::ADD_SERVICE_REQUEST: {
            std::string name;
            std::string description;

            Serializer::get(stream_, name);
            Serializer::get(stream_, description);

            return std::unique_ptr<IRequest>(
                    new AddServiceRequest(name, description)
            );
        }


        case MetaNumber::ADD_SPECIALIST_REQUEST: {
            std::string name;
            Serializer::get(stream_, name);
            return std::unique_ptr<IRequest>(
                    new AddSpecialistRequest(name)
            );
        }


        case MetaNumber::ADD_USER_ATTRIBUTE_REQUEST: {
            UserId userId;
            PolyVector<IAttribute> attributes;

            Serializer::get(stream_, userId);
            Serializer::get(stream_, attributes);

            return std::unique_ptr<IRequest>(
                    new AddUserAttributeRequest(userId, std::move(attributes))
            );
        }


        case MetaNumber::REMOVE_USER_ATTRIBUTE_REQUEST: {
            UserId userId;
            std::vector<std::string> attributes;

            Serializer::get(stream_, userId);
            Serializer::get(stream_, attributes);

            return std::unique_ptr<IRequest>(
                    new RemoveUserAttributeRequest(userId, std::move(attributes))
            );
        }


        case MetaNumber::ATTACH_SPECIALIST_REQUEST: {
            SpecialistId specialistId;
            ServiceId serviceId;

            Serializer::get(stream_, specialistId);
            Serializer::get(stream_, serviceId);

            return std::unique_ptr<IRequest>(
                    new AttachSpecialistRequest(specialistId, serviceId)
            );
        }


        case MetaNumber::GET_MESSAGE_REQUEST: {
            UserId userId;
            Serializer::get(stream_, userId);
            return std::unique_ptr<IRequest>(
                    new GetMessageRequest(userId)
            );
        }


        case MetaNumber::GET_PRIORITY_RULE_REQUEST: {
            ServiceId serviceId;
            Serializer::get(stream_, serviceId);
            return std::unique_ptr<IRequest>(
                    new GetPriorityRuleRequest(serviceId)
            );
        }


        case MetaNumber::GET_SERVICE_DESCRIPTOR_REQUEST: {
            return std::unique_ptr<IRequest>(
                    new GetServiceDescriptorRequest()
            );
        }


        case MetaNumber::GET_SPECIALIST_DESCRIPTOR_REQUEST: {
            ServiceId serviceId;
            Serializer::get(stream_, serviceId);
            return std::unique_ptr<IRequest>(
                    new GetSpecialistDescriptorRequest(serviceId)
            );
        }


        case MetaNumber::GET_USER_ATTRIBUTE_REQUEST: {
            UserId userId;
            Serializer::get(stream_, userId);
            return std::unique_ptr<IRequest>(
                    new GetUserAttributeRequest(userId)
            );
        }


        case MetaNumber::GET_USER_DESCRIPTOR_REQUEST: {
            ServiceId serviceId;
            Serializer::get(stream_, serviceId);
            return std::unique_ptr<IRequest>(
                    new GetUserDescriptorRequest(serviceId)
            );
        }


        case MetaNumber::MAKE_APPOINTMENT_REQUEST: {
            UserId userId;
            ServiceId serviceId;

            Serializer::get(stream_, userId);
            Serializer::get(stream_, serviceId);

            return std::unique_ptr<IRequest>(
                    new MakeAppointmentRequest(userId, serviceId)
            );
        }


        case MetaNumber::REGISTER_USER_REQUEST: {
            std::string login;
            Serializer::get(stream_, login);
            return std::unique_ptr<IRequest>(
                    new RegisterUserRequest(login)
            );
        }


        case MetaNumber::SIGN_IN_REQUEST: {
            std::string login;
            Serializer::get(stream_, login);
            return std::unique_ptr<IRequest>(
                    new SignInRequest(login)
            );
        }


        case MetaNumber::SIGN_OUT_REQUEST: {
            UserId userId;
            Serializer::get(stream_, userId);
            return std::unique_ptr<IRequest>(
                    new SignOutRequest(userId)
            );
        }


        default:
            throw StreamRequestScannerException("unknown meta");
        }
    }
}
