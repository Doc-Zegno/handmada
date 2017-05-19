//
// Created by syzegno on 20.05.17.
//


#include "UserInterface.h"

#include <cstring>
#include <unordered_set>

#include "ConsoleRequestPrinter.h"
#include "ConsoleAttributeListBuilder.h"
#include "AttributePrinter.h"
#include "PredicatePrinter.h"
#include "SnapShooter.h"
#include "BooleanLiteral.h"
#include "Lexer.h"


namespace Handmada {
    std::unordered_map<std::string, std::pair<std::string, void (UserInterface::*)(void)>>
            UserInterface::signedOutCommands_ = {
            {
                    "sign",
                    {
                            "sign in/up @login",
                            &UserInterface::sign
                    }
            },
            {
                    "help",
                    {
                            "help [command]",
                            &UserInterface::help
                    }
            },
    };

    std::unordered_map<std::string, std::pair<std::string, void (UserInterface::*)(void)>>
            UserInterface::signedInCommands_ = {
            {
                    "sign",
                    {
                            "sign out",
                            &UserInterface::sign,
                    }
            },
            {
                    "help",
                    {
                            "help [command]",
                            &UserInterface::help
                    }
            },
            {
                    "get",
                    {
                            "get services/specialists/rules/messages/attributes/queue",
                            &UserInterface::get
                    }
            },
            {
                    "remove",
                    {
                            "remove attributes",
                            &UserInterface::remove
                    }
            },
            {
                    "undo",
                    {
                            "undo",
                            &UserInterface::undo
                    }
            },
            {
                    "book",
                    {
                            "book",
                            &UserInterface::book
                    }
            },
            {
                    "add",
                    {
                            "add attributes",
                            &UserInterface::add
                    }
            },
    };


    UserInterface::UserInterface(
            IFrontend* frontend,
            std::istream& in,
            std::ostream& out,
            std::ostream& err
    ) : console_(in, out, err), frontend_(frontend)
    {
        userId_ = INVALID_USER_ID;
        commands_ = &signedOutCommands_;
        undoList_ = &simpleUndoList_;
    }


    void UserInterface::run()
    {
        console_.out("\t\tH a n d m a d a");
        console_.out("Enter your command below. If you stuck, write \"help\"");
        console_.out("Please sign up/in to continue");

        while (true) {
            args_ = console_.getArgs(isUserIdValid(userId_) ? login_ : "");
            auto iterator = commands_->find(args_[0]);
            if (iterator != commands_->end()) {
                auto mem = iterator->second.second;
                usage_ = iterator->second.first.c_str();
                (this->*mem)();
            } else if (args_[0] == "exit") {
                if (isUserIdValid(userId_)) {
                    frontend_->acceptRequest(SignOutRequest(userId_));
                }
                return;
            } else {
                console_.err("Cannot recognize command");
            }
            console_.out();
        }
    }



    // S u b r o u t i n e s
    void UserInterface::usage()
    {
        console_.err("Usage: ", usage_);
    }


    void UserInterface::sign()
    {
        if (args_.size() < 2) {
            usage();
            return;
        }

        if (args_[1] == "in" && args_.size() == 3) {
            login_ = args_[2];
            makeSignRequest(SignInRequest(login_), false, "You are already signed in");
        } else if (args_[1] == "up" && args_.size() == 3) {
            makeSignRequest(RegisterUserRequest(args_[2]), false, "You must sign out before new registration");
        } else if (args_[1] == "out" && args_.size() == 2) {
            makeSignRequest(SignOutRequest(userId_), true, "You are not signed in yet");
        } else {
            usage();
        }
    }


    void UserInterface::makeSignRequest(
            const IRequest& request,
            bool isSignedIn,
            const std::string& failureMessage
    )
    {
        if (isUserIdValid(userId_) == isSignedIn) {
            auto response = frontend_->acceptRequest(request);
            response->accept(*this);
        } else {
            console_.err(failureMessage);
        }
    }


    void UserInterface::get()
    {
        if (args_.size() != 2) {
            usage();
            return;
        }

        if (args_[1] == "services") {
            auto response = frontend_->acceptRequest(GetServiceDescriptorRequest());
            response->accept(*this);
        } else if (args_[1] == "specialists") {
            ServiceId serviceId;
            console_.input("Enter service ID (-1 to show all specialists): ", serviceId);
            auto response = frontend_->acceptRequest(GetSpecialistDescriptorRequest(serviceId));
            response->accept(*this);
        } else if (args_[1] == "rules") {
            ServiceId serviceId;
            console_.input("Enter service ID: ", serviceId);
            auto response = frontend_->acceptRequest(GetPriorityRuleRequest(serviceId));
            response->accept(*this);
        } else if (args_[1] == "messages") {
            auto response = frontend_->acceptRequest(GetMessageRequest(userId_));
            response->accept(*this);
        } else if (args_[1] == "attributes") {
            auto response = frontend_->acceptRequest(GetUserAttributeRequest(userId_));
            response->accept(*this);
        } else if (args_[1] == "queue") {
            ServiceId serviceId;
            console_.input("Enter service ID: ", serviceId);
            auto response = frontend_->acceptRequest(GetUserDescriptorRequest(serviceId));
            response->accept(*this);
        } else {
            usage();
        }
    }


    void UserInterface::add()
    {
        if (args_.size() != 2) {
            usage();
            return;
        }

        if (args_[1] == "attributes") {
            addAttributes();
        } else {
            usage();
        }
    }


    void UserInterface::addAttributes()
    {
        PolyVector<IAttribute> attributes;
        std::unordered_set<std::string> identifiers;
        Lexer lexer;
        while (true) {
            try {
                console_.outNoLine("Enter new attribute name: ");
                lexer.reset(console_.inStream(), '\n');
                auto lexeme = lexer.getLex();
                std::string name;
                if (lexeme == Lexeme::END_OF_SEQUENCE) {
                    break;
                } else if (lexeme == Lexeme::IDENTIFIER) {
                    name = lexer.getString();
                    if (lexer.getLex() != Lexeme::END_OF_SEQUENCE) {
                        lexer.swallow();
                        throw std::runtime_error("Error: extra lexemes were detected on the line");
                    }
                } else {
                    lexer.swallow();
                    throw std::runtime_error("Error: identifier was expected");
                }

                auto iterator = identifiers.find(name);
                if (iterator != identifiers.end()) {
                    console_.err("Error: identifier has already been declared");
                    console_.out();
                    continue;
                }

                console_.outNoLine("Enter attribute value: ");
                lexer.reset(console_.inStream(), '\n');
                lexeme = lexer.getLex();

                std::unique_ptr<IAttribute> attribute;
                switch (lexeme) {
                case Lexeme::STRING_LITERAL:
                    attribute = makeAttribute(name, lexer.getString());
                    break;
                case Lexeme::NUMBER_LITERAL:
                    attribute = makeAttribute(name, lexer.getNumber());
                    break;
                case Lexeme::BOOLEAN_LITERAL:
                    attribute = makeAttribute(name, lexer.getBoolean());
                    break;
                default:
                    lexer.swallow();
                    throw std::runtime_error("Lexical error: unknown literal");
                }

                if (lexer.getLex() != Lexeme::END_OF_SEQUENCE) {
                    lexer.swallow();
                    throw std::runtime_error("Error: extra lexemes were detected on the line");
                }

                identifiers.insert(name);
                attributes.push_back(std::move(attribute));
            } catch (std::exception& e) {
                console_.err(e.what());
                console_.err("This attribute will be skipped");
            }
            console_.out();
        }

        if (attributes.size() == 0) {
            console_.err("Aborted");
        } else {
            console_.out("The following attributes will be added to the system:");
            AttributePrinter printer(console_.outStream());
            for (auto& attribute : attributes) {
                console_.outNoLine("- ");
                attribute->accept(printer);
            }
            char choice;
            console_.input("Is this really what you want? (y/n): ", choice);
            if (choice == 'y' || choice == 'Y') {
                console_.out("So mote it be");
                auto response = frontend_->acceptRequest(
                        AddUserAttributeRequest(userId_, std::move(attributes))
                );
                response->accept(*this);
            } else {
                console_.err("Aborted");
            }
        }
    }


    void UserInterface::remove()
    {
        if (args_.size() != 2) {
            usage();
            return;
        }

        if (args_[1] == "attributes") {
            removeAttributes();
        } else {
            usage();
        }
    }


    void UserInterface::removeAttributes()
    {
        std::vector<std::string> names;
        std::string name;

        console_.out("Enter names of attributes to be removed");
        console_.out("Empty line to finish input");

        while (true) {
            console_.input(">> ", name);
            if (name.size() == 0) {
                break;
            }
            if (name == "login") {
                console_.err("\"login\" attribute cannot be removed");
                continue;
            }
            names.push_back(std::move(name));
        }

        if (names.size() == 0) {
            console_.err("No attributes were entered. Aborted");
            return;
        }

        auto response = frontend_->acceptRequest(
                RemoveUserAttributeRequest(userId_, std::move(names))
        );
        response->accept(*this);
    }


    void UserInterface::undo()
    {
        if (undoList_->isEmpty()) {
            console_.err("Nothing to undo");
            return;
        }

        console_.out("The following request will be sent to perform undo:");
        console_.outNoLine("- ");
        ConsoleRequestPrinter printer(&console_);
        undoList_->peek()->accept(printer);

        char choice;
        console_.input("Is this really what you want? (y/n): ", choice);
        if (choice == 'y' || choice == 'Y') {
            console_.out("So mote it be");
            auto response = frontend_->acceptRequest(*undoList_->pop());
            undoList_ = &nullUndoList_;
            response->accept(*this);
            undoList_ = &simpleUndoList_;
        } else {
            console_.err("Aborted");
        }
    }


    void UserInterface::book()
    {
        if (args_.size() != 1) {
            usage();
            return;
        }

        console_.input("Enter service ID: ", serviceId_);
        auto response = frontend_->acceptRequest(MakeAppointmentRequest(userId_, serviceId_));
        response->accept(*this);
    }


    void UserInterface::help()
    {
        if (args_.size() > 1) {
            auto iterator = commands_->find(args_[1]);
            if (iterator == commands_->end()) {
                console_.err("No manual available for \"", args_[1], '\"');
            } else {
                console_.out("Usage for \"", args_[1], "\": ", iterator->second.first);
            }
        } else {
            console_.out("Available commands:");
            for (auto& command : *commands_) {
                console_.out('\t', command.second.first);
            }
            console_.out("\texit");
        }
    }



    // R e s p o n s e H a n d l i n g
    void UserInterface::visit(const GeneralResponse& response)
    {
        switch (response.code()) {
        case OpCode::SUCCESS:
            console_.out("Success");
            break;

        case OpCode::ALREADY_SIGN_IN:
            console_.err("User with the same login has already been signed in");
            break;

        case OpCode::NOT_REGISTERED:
            console_.err("You are not registered");
            break;

        case OpCode::ALREADY_REGISTERED:
            console_.err("User with the same login has already been registered");
            break;

        case OpCode::ALREADY_SIGN_OUT:
            console_.err("You have already been signed out");
            break;

        case OpCode::ALREADY_IN_QUEUE:
            console_.err("You have already joined this queue");
            break;

        case OpCode::NO_SUCH_SERVICE:
            console_.err("There is no service with this ID");
            break;

        default:
            console_.err(
                    "Undefined error with code #",
                    static_cast<int>(response.code()),
                    " has occurred"
            );
            console_.err("If you can see this message, please, call support specialist");
            break;
        }
    }


    void UserInterface::visit(const RegisterUserResponse& response)
    {
        console_.out("Successfully registered");
        console_.out("Your ID: ", response.userId());
    }


    void UserInterface::visit(const SignInResponse& response)
    {
        userId_ = response.userId();
        commands_ = &signedInCommands_;
        console_.out("Successfully signed in");
        console_.out("Welcome back, ", login_);
    }


    void UserInterface::visit(const SignOutResponse& response)
    {
        userId_ = INVALID_USER_ID;
        commands_ = &signedOutCommands_;
        console_.out("Successfully signed out");
    }


    void UserInterface::visit(const AddUserAttributeResponse& response)
    {
        auto copy = response.attributes();
        if (copy.size() == 0) {
            console_.out("All attributes already exists");
        } else {
            console_.out("These attributes were added:");
            for (auto& name : copy) {
                console_.out('\t', name);
            }
            undoList_->push(std::unique_ptr<IRequest>(
                    new RemoveUserAttributeRequest(userId_, std::move(copy))
            ));
        }
    }


    void UserInterface::visit(const RemoveUserAttributeResponse& response)
    {
        if (response.attributes().size() != 0) {
            auto copy = SnapShooter::copy(response.attributes());
            console_.out("These attributes were removed:");
            AttributePrinter printer(console_.outStream());
            for (auto& attribute : copy) {
                console_.outNoLine('\t');
                attribute->accept(printer);
            }
            undoList_->push(std::unique_ptr<IRequest>(
                    new AddUserAttributeRequest(userId_, std::move(copy))
            ));
        } else {
            console_.out("No attributes were removed");
        }
    }


    void UserInterface::visit(const MakeAppointmentResponse& response)
    {
        console_.outNoLine("Success!");
        if (response.hasPriority()) {
            console_.out(" You got the priority in queue");
        } else {
            console_.out();
        }
    }


    void UserInterface::visit(const MissingAttributeResponse& response)
    {
        console_.out("The system needs to get more information about you:");
        ConsoleAttributeListBuilder builder(&console_);
        auto attributes = builder.build(response.requirements());
        auto res = frontend_->acceptRequest(
                AddUserAttributeRequest(userId_, std::move(attributes))
        );
        res->accept(*this);

        res = frontend_->acceptRequest(MakeAppointmentRequest(userId_, serviceId_));
        res->accept(*this);
    }


    void UserInterface::visit(const GetMessageResponse& response)
    {
        auto number = response.messages().size();
        if (number == 0) {
            console_.out("No new messages");
        } else {
            int i = 1;
            for (auto& message : response.messages()) {
                console_.out('(', i, '/', number, ')');
                console_.outNoLine("date:  ", std::ctime(&message.when()));
                console_.out("from:  ", message.from());
                console_.out("theme: ", message.theme());
                console_.out('\t', message.text());
                console_.out("~~~");
                i++;
            }
        }
    }


    void UserInterface::visit(const GetServiceDescriptorResponse& response)
    {
        if (response.descriptors().size() == 0) {
            console_.out("There is no available services");
        } else {
            console_.out("Available services:");
            for (auto& service : response.descriptors()) {
                console_.out("ID: ", service.id());
                console_.out("name: ", service.name());
                if (service.description().size() != 0) {
                    console_.out("description: ", service.description());
                }
                console_.out();
            }
        }
    }


    void UserInterface::visit(const GetUserAttributeResponse& response)
    {
        console_.out("Your attributes:");
        AttributePrinter printer(console_.outStream());
        console_.out("ID: ", userId_);
        for (auto& attribute : response.attributes()) {
            if (attribute->name() != "login") {
                attribute->accept(printer);
            }
        }
    }


    void UserInterface::visit(const GetUserDescriptorResponse& response)
    {
        if (response.descriptors().size() == 0) {
            console_.out("No users here! Why don't you book this service?");
        } else {
            console_.out("Queue state:");
            console_.out(10_width, "ID", 50_width, "login", 20_width, "has priority?");

            for (auto& user : response.descriptors()) {
                console_.out(
                        10_width, user.id(),
                        50_width, user.login(),
                        20_width,
                        user.hasPriority() ? Literal::strTrueLiteral : Literal::strFalseLiteral
                );
            }
        }
    }


    void UserInterface::visit(const GetPriorityRuleResponse& response)
    {
        console_.out("Priority rules for this service:");
        PredicatePrinter printer(console_.outStream(), 1);
        for (auto& predicate : response.descriptors()) {
            console_.out("ID: ", predicate.id());
            predicate.predicate().accept(printer);
            console_.out();
        }
    }


    void UserInterface::visit(const GetSpecialistDescriptorResponse& response)
    {
        if (response.descriptors().size() == 0) {
            console_.out("No way! No specialists here yet!");
        } else {
            console_.out("Available specialists:");
            console_.out(10_width, "ID", "name");
            for (auto& descriptor : response.descriptors()) {
                console_.out(10_width, descriptor.id(), descriptor.name());
            }
        }
    }
}
