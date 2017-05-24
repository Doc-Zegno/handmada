//
// Created by syzegno on 20.05.17.
//


#include "UserInterface.h"
#include "ProxyFrontend.h"

using namespace Handmada;


int main(int argc, char* argv[])
{
    try {
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " @portName @portNumber\n";
            return 1;
        }
        int portNo;
        try {
            portNo = std::stoi(argv[2]);
        } catch (std::exception& e) {
            std::cerr << "Invalid @portNumber argument!\n";
            return 1;
        }

        ProxyFrontend frontend(argv[1], static_cast<uint16_t>(portNo));
        UserInterface ui(&frontend, std::cin, std::cout, std::cerr);
        ui.run();

    } catch (ProxyFrontendException& e) {
        std::cerr << "Unable to establish connection with Master Server\n";
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

