//
// Created by syzegno on 20.05.17.
//


#include "AdminInterface.h"
#include "Parser.h"
#include "ConsoleRequirementListBuilder.h"
#include "PredicatePrinter.h"


namespace Handmada {
    std::unordered_map<std::string, std::pair<std::string, void (AdminInterface::*)(void)>>
            AdminInterface::commands_ = {
            {
                    "help",
                    {
                            "help [command]",
                            &AdminInterface::help
                    }
            },
            {
                    "add",
                    {
                            "add rule/specialist/service",
                            &AdminInterface::add
                    }
            },
            {
                    "get",
                    {
                            "get services/specialists/rules",
                            &AdminInterface::get
                    }
            },
            {
                    "attach",
                    {
                            "attach @specialistId @serviceId",
                            &AdminInterface::attachSpecialistToService
                    }
            },
    };


    AdminInterface::AdminInterface(
            IFrontend* frontend,
            std::istream& in,
            std::ostream& out,
            std::ostream& err
    ) : console_(in, out, err), frontend_(frontend)
    { }


    void AdminInterface::run()
    {
        console_.out("\t\tH a n d m a d a");
        console_.out("Enter your command below. If you stuck, write \"help\"");

        while (true) {
            args_ = console_.getArgs("");
            auto iterator = commands_.find(args_[0]);
            if (iterator != commands_.end()) {
                auto mem = iterator->second.second;
                usage_ = iterator->second.first.c_str();
                (this->*mem)();
            } else if (args_[0] == "exit") {
                return;
            } else {
                console_.err("Cannot recognize command");
            }
            console_.out();
        }
    }



    // S u b r o u t i n e s
    void AdminInterface::add()
    {
        if (args_.size() != 2) {
            usage();
            return;
        }

        if (args_[1] == "rule") {
            addPriorityRule();
        } else if (args_[1] == "service") {
            addService();
        } else if (args_[1] == "specialist") {
            addSpecialist();
        } else {
            usage();
        }
    }


    void AdminInterface::addService()
    {
        std::string name;
        console_.input("Enter service name: ", name);
        if (name.size() == 0) {
            console_.err("Aborted");
            return;
        }
        std::string description;
        console_.input("Enter short description: ", description);
        auto response = frontend_->acceptRequest(AddServiceRequest(name, description));
        response->accept(*this);
    }


    void AdminInterface::addSpecialist()
    {
        std::string name;
        console_.input("Enter specialist's name: ", name);
        if (name.size() == 0) {
            console_.err("Aborted");
            return;
        }
        auto response = frontend_->acceptRequest(AddSpecialistRequest(name));
        response->accept(*this);
    }


    void AdminInterface::get()
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
        } else {
            usage();
        }
    }


    void AdminInterface::attachSpecialistToService()
    {
        if (args_.size() != 3) {
            usage();
            return;
        }

        SpecialistId specialistId;
        ServiceId serviceId;
        try {
            specialistId = std::stoi(args_[1]);
            serviceId = std::stoi(args_[2]);
        } catch (std::exception& e) {
            console_.err("Invalid arguments");
            console_.err("Aborted");
            return;
        }

        auto response = frontend_->acceptRequest(
                AttachSpecialistRequest(specialistId, serviceId)
        );
        response->accept(*this);
    }


    void AdminInterface::addPriorityRule()
    {
        ServiceId serviceId;
        console_.input("Enter service ID: ", serviceId);

        Parser parser(console_.inStream(), '\n');
        std::unique_ptr<IPredicate> predicate;
        while (true) {
            console_.out("Enter new priority rule:");
            console_.outNoLine(">> ");
            parser.reset(console_.inStream(), '\n');
            try {
                predicate = parser.getPredicate();
                break;
            } catch (std::exception& e) {
                console_.err(e.what());
                console_.out();
                continue;
            }
        }

        PredicatePrinter printer(console_.outStream(), 1);
        console_.out("The following rule will be added to the system:");
        predicate->accept(printer);
        char choice;
        console_.input("Is this really what you want? (y/n): ", choice);
        if (choice == 'y' || choice == 'Y') {
            console_.out("So mote it be");
            console_.out();
            auto requirements = ConsoleRequirementListBuilder::build(
                    &console_, parser.getIdentifiers()
            );
            auto response = frontend_->acceptRequest(
                    AddPriorityRuleRequest(
                            serviceId, std::move(predicate), std::move(requirements)
                    )
            );
            response->accept(*this);
        } else {
            console_.err("Aborted");
        }
    }


    void AdminInterface::help()
    {
        if (args_.size() > 1) {
            auto iterator = commands_.find(args_[1]);
            if (iterator == commands_.end()) {
                console_.err("No manual available for ", args_[1]);
            } else {
                console_.out("Usage for \"", args_[1], "\": ", iterator->second.first);
            }
        } else {
            console_.out("Available commands:");
            for (auto& command : commands_) {
                console_.out('\t', command.second.first);
            }
            console_.out("\texit");
        }
    }


    void AdminInterface::usage()
    {
        console_.err("Usage: ", usage_);
    }



    // R e s p o n s e H a n d l i n g
    void AdminInterface::visit(const GeneralResponse& response)
    {
        switch (response.code()) {
        case OpCode::SUCCESS:
            console_.out("Success");
            break;

        case OpCode::NO_SUCH_SERVICE:
            console_.err("There is no service with this ID");
            break;

        case OpCode::NO_SUCH_SPECIALIST:
            console_.err("There is no specialist with this ID");
            break;

        case OpCode::ALREADY_ATTACHED:
            console_.err("This specialist has already been attached to that service");
            break;

        case OpCode::SERVICE_EXISTS:
            console_.err("Service with this name already exists");
            break;

        case OpCode::SPECIALIST_EXISTS:
            console_.err("Specialist with this name already exists");
            break;

        default:
            console_.err("Unhandled code error#", static_cast<int>(response.code()));
            console_.err("If you can see this message, please, call support specialist");
            break;
        }
    }


    void AdminInterface::visit(const AddServiceResponse& response)
    {
        console_.out("Successfully added");
        console_.out("Service ID is ", response.serviceId());
    }


    void AdminInterface::visit(const AddSpecialistResponse& response)
    {
        console_.out("Successfully added");
        console_.out("Specialist ID is ", response.specialistId());
    }


    void AdminInterface::visit(const AddPriorityRuleResponse& response)
    {
        console_.out("Successfully added");
        console_.out("Full predicate ID is ", response.serviceId(), ':', response.predicateId());
    }


    void AdminInterface::visit(const AttachSpecialistResponse& response)
    {
        console_.out("Successfully attached");
    }


    void AdminInterface::visit(const RequirementCollisionResponse& response)
    {
        console_.err("The following attributes conflict with their previously declared type:");
        for (auto& pair : response.collisions()) {
            console_.err(
                    "- \"",
                    pair.first,
                    "\" previously declared as ",
                    AttributeType::toString(pair.second)
            );
        }
        console_.err("Operation failed");
    }


    void AdminInterface::visit(const GetServiceDescriptorResponse& response)
    {
        if (response.descriptors().size() != 0) {
            console_.out("Available services:");
            for (auto& service : response.descriptors()) {
                console_.out("ID: ", service.id());
                console_.out("name: ", service.name());
                if (service.description().size() != 0) {
                    console_.out("description: ", service.description());
                }
                console_.out();
            }
        } else {
            console_.out("No services available! The time has come to change it");
        }
    }


    void AdminInterface::visit(const GetSpecialistDescriptorResponse& response)
    {
        if (response.descriptors().size() != 0) {
            console_.out("Available specialists:");
            console_.out(10_width, "ID", "name");
            for (auto& specialist : response.descriptors()) {
                console_.out(10_width, specialist.id(), specialist.name());
            }
        } else {
            console_.out("No specialists here! We need to attach someone");
        }
    }


    void AdminInterface::visit(const GetPriorityRuleResponse& response)
    {
        if (response.descriptors().size() != 0) {
            console_.out("Service priority rules:");
            PredicatePrinter printer(console_.outStream(), 1);
            for (auto& predicate : response.descriptors()) {
                console_.out("ID: ", predicate.id());
                predicate.predicate().accept(printer);
                console_.out();
            }
        } else {
            console_.out("No rules were declared for this service");
            console_.out("Nothing is true and everyone gets the priority");
        }
    }
}
