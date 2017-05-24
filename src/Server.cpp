//
// Created by syzegno on 17.05.17.
//


#include <cstdio>
#include <cstring>
#include <cstdint>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <csignal>

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include "SimpleController.h"
#include "BasicFrontend.h"

#include "Serializer.h"
#include "UnixFileStream.h"
#include "DynamicBufferStream.h"

using namespace Handmada;


SimpleController controller;
BasicFrontend frontend(&controller);


std::mutex frontendMutex;
std::mutex outputMutex;
std::mutex numOfThreadsMutex;

volatile sig_atomic_t isInterrupted = 0;
volatile sig_atomic_t numOfThreads = 0;


const int THREAD_CYCLES_PER_MAIN_CYCLE = 300;
const int CYCLE_DURATION = 100;



void increaseNumOfThreads()
{
    numOfThreadsMutex.lock();
    numOfThreads++;
    numOfThreadsMutex.unlock();
}

void decreaseNumOfThreads()
{
    numOfThreadsMutex.lock();
    numOfThreads--;
    numOfThreadsMutex.unlock();
}



void process(int sockFd)
{
    UnixFileStream fileStream(sockFd);
    DynamicBufferStream bufferStream;
    auto threadId = std::this_thread::get_id();

    while (!isInterrupted) {
        size_t size;
        auto haveRead = read(sockFd, reinterpret_cast<char*>(&size), sizeof(size));
        if (haveRead == 0) {
            outputMutex.lock();
            std::cout << "thread #" << threadId << ": connection was lost\n";
            outputMutex.unlock();
            break;
        } else if (haveRead < 0) {
            continue;
        }

        try {
            bufferStream.reserve(size);
            fileStream.get(bufferStream.buffer(), size);
            std::unique_ptr<IRequest> request;
            Serializer::get(bufferStream, request);

            outputMutex.lock();
            std::cout << "thread #" << threadId << " receives request of size " << size << " B\n";
            outputMutex.unlock();

            frontendMutex.lock();
            auto response = frontend.acceptRequest(*request);
            frontendMutex.unlock();

            bufferStream.seek(0);
            Serializer::put(bufferStream, size);
            Serializer::put(bufferStream, response);
            size = bufferStream.position();
            bufferStream.seek(0);
            Serializer::put(bufferStream, size - sizeof(size));
            fileStream.put(bufferStream.buffer(), size);

        } catch (std::exception& e) {
            outputMutex.lock();
            std::cout << "exception in thread #" << std::this_thread::get_id();
            std::cout << ":\n\t" << e.what() << std::endl;
            outputMutex.unlock();
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_DURATION));
    }
    close(sockFd);
    decreaseNumOfThreads();
}


void sigintHandler(int)
{
    char info[] = "Signal: stop\n";
    write(STDOUT_FILENO, info, sizeof(info));
    isInterrupted = 1;
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " @portNumber\n";
        return 1;
    }

    int portNo;
    try {
        portNo = std::stoi(argv[1]);
    } catch (std::exception& e) {
        std::cerr << "Invalid argument @portNumber!\n";
        return 1;
    }


    int sockFd;
    sockaddr_in serverAddress;

    sockFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sockFd < 0) {
        perror("socket");
        return 1;
    }

    std::memset(reinterpret_cast<char*>(&serverAddress), 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(static_cast<uint16_t>(portNo));

    if (bind(sockFd, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        perror("bind");
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = sigintHandler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, nullptr);

    std::cout << "Loading dumps...\n";
    controller.checkOut();
    std::cout << "Done\nRunning...\n";

    int threadCycles = 0;
    listen(sockFd, 5);
    while (!isInterrupted) {
        sockaddr_in clientAddress;
        socklen_t clientLen = sizeof(clientAddress);
        auto newSockFd = accept4(
                sockFd, reinterpret_cast<sockaddr*>(&clientAddress), &clientLen, SOCK_NONBLOCK
        );
        if (newSockFd > 0) {
            increaseNumOfThreads();
            outputMutex.lock();
            std::cout << "New connection was established\n";
            outputMutex.unlock();
            auto thread = std::thread(process, newSockFd);
            thread.detach();
        }

        threadCycles++;
        if (threadCycles == THREAD_CYCLES_PER_MAIN_CYCLE) {
            threadCycles = 0;
            frontendMutex.lock();
            frontend.runServices();
            frontendMutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_DURATION));
    }

    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_DURATION));
    } while (numOfThreads > 0);

    std::cout << "Swapping data...\n";
    controller.swap();
    std::cout << "Server: done\n";
}

