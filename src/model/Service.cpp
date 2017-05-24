//
// Created by syzegno on 24.04.17.
//


#include "Service.h"
#include "SimpleSequenceIterator.h"


namespace Handmada {
    Service::Service(const std::string& name, const std::string& description, ServiceId id)
        : id_(id), name(name), description(description)
    { }


    bool Service::addUser(UserId id, bool hasPriority)
    {
        if (hasUser(id)) {
            return false;
        }

        if (hasPriority) {
            premiumUsers_.push_back(id);
        } else {
            standardUsers_.push_back(id);
        }
        return true;
    }


    bool Service::hasUser(UserId id) const
    {
        for (auto user : premiumUsers_) {
            if (user == id) {
                return true;
            }
        }
        for (auto user : standardUsers_) {
            if (user == id) {
                return true;
            }
        }
        return false;
    }


    bool Service::isQueueEmpty() const
    {
        return premiumUsers_.empty() && standardUsers_.empty();
    }


    size_t Service::usersAmount() const
    {
        return premiumUsers_.size() + standardUsers_.size();
    }


    bool Service::addSpecialist(SpecialistId id, Specialist* specialist)
    {
        auto iterator = specialists_.find(id);
        if (iterator == specialists_.end()) {
            specialists_.insert(std::make_pair(id, specialist));
            return true;
        } else {
            return false;
        }
    }


    void Service::printQueue(std::ostream& output) const
    {
        int i = 1;
        for (const auto& user : premiumUsers_) {
            output << '#' << i++ << ": " << user << std::endl;
        }
        for (const auto& user : standardUsers_) {
            output << '#' << i++ << ": " << user << std::endl;
        }
    }


    void Service::printSpecialists(std::ostream& output) const
    {
        for (auto pair : specialists_) {
            output << "ID: " << pair.first << "\n" << pair.second->name() << "\n\n";
        }
    }


    void Service::run(IInfoContainer& infoContainer)
    {
        for (auto pair : specialists_) {
            auto spec = pair.second;
            if (spec->isBusy() && spec->currentServiceId() == id_) {
                spec->busy_ = false;
                infoContainer.addInfo(spec->currentUserId(), id_, spec);
            }
            if (!spec->isBusy()) {
                UserId nextId = INVALID_USER_ID;
                if (!premiumUsers_.empty()) {
                    nextId = premiumUsers_.front();
                    premiumUsers_.pop_front();
                } else if (!standardUsers_.empty()) {
                    nextId = standardUsers_.front();
                    standardUsers_.pop_front();
                } else {
                    break;
                }
                if (isUserIdValid(nextId)) {
                    spec->busy_ = true;
                    spec->currentServiceId_ = id_;
                    spec->currentUserId_ = nextId;
                }
            }
        }
    }


    ServiceId Service::id() const
    {
        return id_;
    }


    std::unique_ptr<IIterator<UserId>> Service::getStandardUsersIterator()
    {
        return Prefab::makeSimpleSequenceIterator(standardUsers_);
    }


    std::unique_ptr<IIterator<UserId>> Service::getPremiumUsersIterator()
    {
        return Prefab::makeSimpleSequenceIterator(premiumUsers_);
    }


    std::unique_ptr<IIterator<std::pair<const SpecialistId, Specialist*>>>
    Service::getSpecialistsIterator()
    {
        using Container = std::remove_reference<decltype(specialists_)>::type;
        return Prefab::makeSimpleIterator<std::pair<const SpecialistId, Specialist*>>(
                &specialists_,
                [](const Container::iterator& iter) {
                    return &*iter;
                }
        );
    }


    size_t Service::specialistsAmount() const
    {
        return specialists_.size();
    }


    size_t Service::standardUsersAmount() const
    {
        return standardUsers_.size();
    }


    size_t Service::premiumUsersAmount() const
    {
        return premiumUsers_.size();
    }
}
