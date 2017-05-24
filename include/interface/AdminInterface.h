//
// Created by syzegno on 20.05.17.
//

#ifndef EQUEUE_V2_ADMININTERFACE_H
#define EQUEUE_V2_ADMININTERFACE_H


#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "IFrontend.h"
#include "IResponseVisitor.h"
#include "IRequirementVisitor.h"
#include "Console.h"
#include "Requests.h"
#include "Types.h"


namespace Handmada {
    class AdminInterface : public IResponseVisitor
    {
    private:
        Console console_;

        IFrontend* frontend_;
        std::vector<std::string> args_;
        const char* usage_;

        static std::unordered_map<
                std::string, std::pair<std::string, void (AdminInterface::*)(void)>
        > commands_;


        void add();
        void addService();
        void addSpecialist();
        void get();
        void attachSpecialistToService();
        void addPriorityRule();
        void help();
        void usage();

    public:
        AdminInterface(IFrontend* frontend, std::istream& in, std::ostream& out, std::ostream& err);

        void run();

        virtual void visit(const GeneralResponse& response) override;
        virtual void visit(const AddServiceResponse& response) override;
        virtual void visit(const AddSpecialistResponse& response) override;
        virtual void visit(const AddPriorityRuleResponse& response) override;
        virtual void visit(const AttachSpecialistResponse& response) override;
        virtual void visit(const RequirementCollisionResponse& response) override;
        virtual void visit(const GetServiceDescriptorResponse& response) override;
        virtual void visit(const GetSpecialistDescriptorResponse& response) override;
        virtual void visit(const GetPriorityRuleResponse& response) override;
    };
}


#endif //EQUEUE_V2_ADMININTERFACE_H
