//
// Created by syzegno on 18.05.17.
//

#ifndef EQUEUE_V2_SERIALIZER_H
#define EQUEUE_V2_SERIALIZER_H


#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <type_traits>

#include "IStream.h"
#include "StreamAttributePrinter.h"
#include "StreamAttributeScanner.h"
#include "StreamPredicatePrinter.h"
#include "StreamPredicateScanner.h"
#include "StreamRequirementPrinter.h"
#include "StreamRequirementScanner.h"
#include "StreamRequestPrinter.h"
#include "StreamRequestScanner.h"
#include "StreamResponsePrinter.h"
#include "StreamResponseScanner.h"
#include "Message.h"
#include "Specialist.h"
#include "Service.h"
#include "Descriptors.h"


namespace Handmada {
    /**
     * Serializer is a kit of template static high-level methods
     * for interacting with various IStream objects
     */
    class Serializer
    {
    private:
        template<typename TMap>
        static void putMap(IStream& stream, const TMap& map);

        template<typename TMap>
        static void getMap(IStream& stream, TMap& map);

        template<typename TSet>
        static void putSet(IStream& stream, const TSet& set);

        template<typename TSet>
        static void getSet(IStream& stream, TSet& set);

        template<typename TSequence>
        static void putSequence(IStream& stream, const TSequence& sequence);

        template<typename TSequence>
        static void getSequence(IStream& stream, TSequence& sequence);

    public:
        /**
         * Serializes object Value and writes its binary representation
         * into Stream object.
         * Stream's internal pointer is moved during the process that's why
         * it is possible to perform a sequence of such serializations
         * @tparam T type of serializable value
         * @param stream output stream
         * @param value serializable value
         */
        template<typename T>
        static void put(IStream& stream, const T& value);

        /**
         * Retrieves binary representation of Value from Stream
         * and initializes Value
         * @tparam T type of retrieved value
         * @param stream input stream
         * @param value value to be initialized from input stream
         */
        template<typename T>
        static void get(IStream& stream, T& value);

        template<typename K, typename V>
        static void put(IStream& stream, const std::map<K, V>& map);

        template<typename K, typename V>
        static void get(IStream& stream, std::map<K, V>& map);

        template<typename K>
        static void put(IStream& stream, const std::set<K>& set);

        template<typename K>
        static void get(IStream& stream, std::set<K>& set);

        template<typename K, typename V, typename H, typename C>
        static void put(IStream& stream, const std::unordered_map<K, V, H, C>& map);

        template<typename K, typename V, typename H, typename C>
        static void get(IStream& stream, std::unordered_map<K, V, H, C>& map);

        template<typename K, typename H, typename C>
        static void put(IStream& stream, const std::unordered_set<K, H, C>& set);

        template<typename K, typename H, typename C>
        static void get(IStream& stream, std::unordered_set<K, H, C>& set);

        template<typename T>
        static void put(IStream& stream, const std::vector<T>& vector);

        template<typename T>
        static void get(IStream& stream, std::vector<T>& vector);

        template<typename T>
        static void put(IStream& stream, const std::deque<T>& deque);

        template<typename T>
        static void get(IStream& stream, std::deque<T>& deque);

        template<typename T>
        static void put(IStream& stream, const std::unique_ptr<T>& ptr);

        template<typename T>
        static void get(IStream& stream, std::unique_ptr<T>& ptr);
    };


    template<typename T>
    void Serializer::put(IStream& stream, const T& value)
    {
        stream.put(reinterpret_cast<const char*>(&value), sizeof(value));
    }


    template<typename T>
    void Serializer::get(IStream& stream, T& value)
    {
        stream.get(reinterpret_cast<char*>(&value), sizeof(value));
    }


    template<>
    inline void Serializer::put(IStream& stream, const std::string& str)
    {
        auto size = str.size();
        stream.put(reinterpret_cast<const char*>(&size), sizeof(size));
        stream.put(str.c_str(), size);
    }


    template<>
    inline void Serializer::get(IStream& stream, std::string& str)
    {
        size_t size;
        stream.get(reinterpret_cast<char*>(&size), sizeof(size));
        char buffer[size + 1];
        std::memset(buffer, 0, size + 1);
        stream.get(buffer, size);
        str = buffer;
    }



    // C o n t a i n e r s    a n d    p o i n t e r s
    template<typename K, typename V, typename H, typename C>
    void Serializer::put(IStream& stream, const std::unordered_map<K, V, H, C>& map)
    {
        putMap(stream, map);
    }


    template<typename K, typename V, typename H, typename C>
    void Serializer::get(IStream& stream, std::unordered_map<K, V, H, C>& map)
    {
        getMap(stream, map);
    }


    template<typename K, typename H, typename C>
    void Serializer::put(IStream& stream, const std::unordered_set<K, H, C>& set)
    {
        putSet(stream, set);
    }


    template<typename K, typename H, typename C>
    void Serializer::get(IStream& stream, std::unordered_set<K, H, C>& set)
    {
        getSet(stream, set);
    }


    template<typename T>
    void Serializer::put(IStream& stream, const std::vector<T>& vector)
    {
        putSequence(stream, vector);
    }


    template<typename T>
    void Serializer::get(IStream& stream, std::vector<T>& vector)
    {
        getSequence(stream, vector);
    }


    template<typename T>
    void Serializer::put(IStream& stream, const std::deque<T>& deque)
    {
        putSequence(stream, deque);
    }


    template<typename T>
    void Serializer::get(IStream& stream, std::deque<T>& deque)
    {
        getSequence(stream, deque);
    }


    template<typename K, typename V>
    void Serializer::put(IStream& stream, const std::map<K, V>& map)
    {
        putMap(stream, map);
    }


    template<typename K, typename V>
    void Serializer::get(IStream& stream, std::map<K, V>& map)
    {
        getMap(stream, map);
    }


    template<typename K>
    void Serializer::put(IStream& stream, const std::set<K>& set)
    {
        putSet(stream, set);
    }


    template<typename K>
    void Serializer::get(IStream& stream, std::set<K>& set)
    {
        getSet(stream, set);
    }


    template<typename T>
    void Serializer::put(IStream& stream, const std::unique_ptr<T>& ptr)
    {
        put(stream, *ptr);
    }


    template<typename T>
    void Serializer::get(IStream& stream, std::unique_ptr<T>& ptr)
    {
        static_assert(std::is_default_constructible<T>::value, "Pointer element type must be default constructible");

        T* tmp = new T();
        get(stream, *tmp);
        ptr = std::unique_ptr<T>(tmp);
    }



    // P r e f a b s
    template<typename TMap>
    void Serializer::putMap(IStream& stream, const TMap& map)
    {
        put(stream, map.size());
        for (auto iterator = map.begin(); iterator != map.end(); ++iterator) {
            put(stream, iterator->first);
            put(stream, iterator->second);
        }
    }


    template<typename TMap>
    void Serializer::getMap(IStream& stream, TMap& map)
    {
        static_assert(
                std::is_default_constructible<typename TMap::key_type>::value,
                "Map key type must be default constructible"
        );
        static_assert(
                std::is_default_constructible<typename TMap::mapped_type>::value,
                "Map value type must be default constructible"
        );

        size_t size;
        get(stream, size);
        for (size_t i = 0; i < size; i++) {
            typename TMap::key_type key;
            typename TMap::mapped_type value;
            get(stream, key);
            get(stream, value);
            map.insert(std::make_pair(std::move(key), std::move(value)));
        }
    }


    template<typename TSet>
    void Serializer::putSet(IStream& stream, const TSet& set)
    {
        put(stream, set.size());
        for (auto iterator = set.begin(); iterator != set.end(); ++iterator) {
            put(stream, *iterator);
        }
    }


    template<typename TSet>
    void Serializer::getSet(IStream& stream, TSet& set)
    {
        static_assert(
                std::is_default_constructible<typename TSet::key_type>::value,
                "Set key type must be default constructible"
        );

        size_t size;
        get(stream, size);
        for (size_t i = 0; i < size; i++) {
            typename TSet::key_type key;
            get(stream, key);
            set.insert(std::move(key));
        }
    }


    template<typename TSequence>
    void Serializer::putSequence(IStream& stream, const TSequence& sequence)
    {
        put(stream, sequence.size());
        for (auto iterator = sequence.begin(); iterator != sequence.end(); ++iterator) {
            put(stream, *iterator);
        }
    }


    template<typename TSequence>
    void Serializer::getSequence(IStream& stream, TSequence& sequence)
    {
        static_assert(
                std::is_default_constructible<typename TSequence::value_type>::value,
                "Sequence value type must be default constructible");

        size_t size;
        get(stream, size);
        for (size_t i = 0; i < size; i++) {
            typename TSequence::value_type value;
            get(stream, value);
            sequence.push_back(std::move(value));
        }
    }



    // S p e c i a l i z a t i o n s
    // P o l y m o r p h i c
    template<>
    inline void Serializer::put(IStream& stream, const IAttribute& attribute)
    {
        StreamAttributePrinter printer(stream);
        attribute.accept(printer);
    }


    template<>
    inline void Serializer::get(IStream& stream, std::unique_ptr<IAttribute>& attribute)
    {
        StreamAttributeScanner scanner(stream);
        attribute = scanner.getNext();
    }


    template<>
    inline void Serializer::put(IStream& stream, const IPredicate& predicate)
    {
        StreamPredicatePrinter printer(stream);
        predicate.accept(printer);
    }


    template<>
    inline void Serializer::get(IStream& stream, std::unique_ptr<IPredicate>& predicate)
    {
        StreamPredicateScanner scanner(stream);
        predicate = scanner.getNext();
    }


    template<>
    inline void Serializer::put(IStream& stream, const IRequirement& requirement)
    {
        StreamRequirementPrinter printer(stream);
        requirement.accept(printer);
    }


    template<>
    inline void Serializer::get(IStream& stream, std::unique_ptr<IRequirement>& requirement)
    {
        StreamRequirementScanner scanner(stream);
        requirement = scanner.getNext();
    }


    template<>
    inline void Serializer::put(IStream& stream, const IRequest& request)
    {
        StreamRequestPrinter printer(stream);
        request.accept(printer);
    }


    template<>
    inline void Serializer::get(IStream& stream, std::unique_ptr<IRequest>& request)
    {
        StreamRequestScanner scanner(stream);
        request = scanner.getNext();
    }


    template<>
    inline void Serializer::put(IStream& stream, const IResponse& response)
    {
        StreamResponsePrinter printer(stream);
        response.accept(printer);
    }


    template<>
    inline void Serializer::get(IStream& stream, std::unique_ptr<IResponse>& response)
    {
        StreamResponseScanner scanner(stream);
        response = scanner.getNext();
    }



    // S t r u c t u r e s
    template<>
    inline void Serializer::put(IStream& stream, const Message& message)
    {
        put(stream, message.when());
        put(stream, message.from());
        put(stream, message.theme());
        put(stream, message.text());
    }

    template<>
    inline void Serializer::get(IStream& stream, Message& message)
    {
        std::time_t when;
        std::string from, theme, text;

        get(stream, when);
        get(stream, from);
        get(stream, theme);
        get(stream, text);

        message = Message(when, from, theme, text);
    }


    template<>
    inline void Serializer::put(IStream& stream, const Specialist& specialist)
    {
        put(stream, specialist.name());
        put(stream, specialist.isBusy());
        put(stream, specialist.currentUserId());
        put(stream, specialist.currentServiceId());
    }


    template<>
    inline void Serializer::get(IStream& stream, Specialist& specialist)
    {
        std::string name;
        bool isBusy;
        UserId userId;
        ServiceId serviceId;

        get(stream, name);
        get(stream, isBusy);
        get(stream, userId);
        get(stream, serviceId);

        specialist = Specialist(name, isBusy, userId, serviceId);
    }



    // C o m p l e x
    template<>
    inline void Serializer::put(IStream& stream, const ServiceDescriptor& descriptor)
    {
        put(stream, descriptor.id());
        put(stream, descriptor.name());
        put(stream, descriptor.description());
    }


    template<>
    inline void Serializer::get(IStream& stream, ServiceDescriptor& descriptor)
    {
        ServiceId serviceId;
        std::string name;
        std::string description;

        get(stream, serviceId);
        get(stream, name);
        get(stream, description);

        descriptor = ServiceDescriptor(serviceId, name, description);
    }


    template<>
    inline void Serializer::put(IStream& stream, const SpecialistDescriptor& descriptor)
    {
        put(stream, descriptor.id());
        put(stream, descriptor.name());
    }


    template<>
    inline void Serializer::get(IStream& stream, SpecialistDescriptor& descriptor)
    {
        SpecialistId specialistId;
        std::string name;

        get(stream, specialistId);
        get(stream, name);

        descriptor = SpecialistDescriptor(specialistId, name);
    }


    template<>
    inline void Serializer::put(IStream& stream, const UserDescriptor& descriptor)
    {
        put(stream, descriptor.id());
        put(stream, descriptor.login());
        put(stream, descriptor.hasPriority());
    }


    template<>
    inline void Serializer::get(IStream& stream, UserDescriptor& descriptor)
    {
        UserId userId;
        std::string login;
        bool hasPriority;

        get(stream, userId);
        get(stream, login);
        get(stream, hasPriority);

        descriptor = UserDescriptor(userId, login, hasPriority);
    }


    template<>
    inline void Serializer::put(IStream& stream, const SmallPredicateDescriptor& descriptor)
    {
        put(stream, descriptor.id());
        put(stream, descriptor.predicate());
    }


    template<>
    inline void Serializer::get(IStream& stream, SmallPredicateDescriptor& descriptor)
    {
        PredicateId predicateId;
        std::unique_ptr<IPredicate> predicate;

        get(stream, predicateId);
        get(stream, predicate);

        descriptor = SmallPredicateDescriptor(predicateId, std::move(predicate));
    }


    template<>
    inline void Serializer::put(IStream& stream, const BigPredicateDescriptor& descriptor)
    {
        put(stream, descriptor.id());
        put(stream, descriptor.predicate());
        put(stream, descriptor.requirements());
    }


    template<>
    inline void Serializer::get(IStream& stream, BigPredicateDescriptor& descriptor)
    {
        PredicateId predicateId;
        std::unique_ptr<IPredicate> predicate;
        PolyVector<IRequirement> requirements;

        get(stream, predicateId);
        get(stream, predicate);
        get(stream, requirements);

        descriptor = BigPredicateDescriptor(
                predicateId, std::move(predicate), std::move(requirements)
        );
    }


    template<>
    inline void Serializer::put(IStream& stream, const RequirementDescriptor& descriptor)
    {
        put(stream, descriptor.requirement());
        put(stream, descriptor.numberOfUsages());
    }


    template<>
    inline void Serializer::get(IStream& stream, RequirementDescriptor& descriptor)
    {
        std::unique_ptr<IRequirement> requirement;
        size_t usages;

        get(stream, requirement);
        get(stream, usages);

        descriptor = RequirementDescriptor(std::move(requirement), usages);
    }


    template<>
    inline void Serializer::put(IStream& stream, const Service& service)
    {
        put(stream, service.specialists_);
        put(stream, service.standardUsers_);
        put(stream, service.premiumUsers_);
        put(stream, service.id_);
        put(stream, service.name);
        put(stream, service.description);
    }


    template<>
    inline void Serializer::get(IStream& stream, Service& service)
    {
        get(stream, service.specialists_);
        get(stream, service.standardUsers_);
        get(stream, service.premiumUsers_);
        get(stream, service.id_);
        get(stream, service.name);
        get(stream, service.description);
    }
}


#endif //EQUEUE_V2_SERIALIZER_H
