//
// Created by syzegno on 24.04.17.
//

#ifndef EQUEUE_V2_SERVICE_H
#define EQUEUE_V2_SERVICE_H


#include <deque>
#include <string>
#include <memory>
#include <iostream>
#include <map>

#include "Specialist.h"
#include "Types.h"
#include "IInfoContainer.h"
#include "IIterator.h"


namespace Handmada {
    class Service
    {
    private:
        std::map<Handmada::SpecialistId, Handmada::Specialist*> specialists_;
        std::deque<Handmada::UserId> standardUsers_;
        std::deque<Handmada::UserId> premiumUsers_;
        ServiceId id_;

        friend class Serializer;

    public:
        std::string name;
        std::string description;

        Service() = default;
        Service(const std::string& name, const std::string& description, ServiceId id);

        bool addUser(UserId id, bool hasPriority);
        bool addSpecialist(SpecialistId id, Specialist* specialist);
        bool hasUser(UserId id) const;
        bool isQueueEmpty() const;
        size_t specialistsAmount() const;
        size_t standardUsersAmount() const;
        size_t premiumUsersAmount() const;
        size_t usersAmount() const;
        ServiceId id() const;

        void printQueue(std::ostream& output) const;
        void printSpecialists(std::ostream& output) const;

        std::unique_ptr<IIterator<UserId>> getStandardUsersIterator();
        std::unique_ptr<IIterator<UserId>> getPremiumUsersIterator();
        std::unique_ptr<IIterator<std::pair<const SpecialistId, Specialist*>>>
        getSpecialistsIterator();

        void run(IInfoContainer& infoContainer);
    };
}


#endif //EQUEUE_V2_SERVICE_H
