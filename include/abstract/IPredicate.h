//
// Created by syzegno on 29.04.17.
//

#ifndef EQUEUE_V2_IPREDICATE_H
#define EQUEUE_V2_IPREDICATE_H


#include <vector>
#include <memory>

#include "IAttribute.h"
#include "IAttributeContainer.h"


namespace Handmada {
    class IPredicateVisitor;


    /**
     * The essence of priority rules
     */
    class IPredicate
    {
    public:
        /**
         * Analyzes the given attributes to decide whether user with such attributes
         * gets a priority in a queue
         * @param attributes container with user attributes
         * @return true if attributes satisfy predicate and false otherwise
         */
        virtual bool operator()(const IAttributeContainer& attributes) const = 0;
        virtual void accept(IPredicateVisitor& visitor) const = 0;
        virtual std::unique_ptr<IPredicate> clone() const = 0;

        virtual ~IPredicate() { }
    };
}


#endif //EQUEUE_V2_IPREDICATE_H
