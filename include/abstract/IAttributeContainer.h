//
// Created by syzegno on 03.05.17.
//

#ifndef EQUEUE_V2_IATTRIBUTECONTAINER_H
#define EQUEUE_V2_IATTRIBUTECONTAINER_H


#include "IAttribute.h"


namespace Handmada {
    /**
     * Container adapter which is extensively used by all sorts of predicates.
     * The main aim of introducing this interface is to hide the underlying container
     * from predicates
     */
    class IAttributeContainer
    {
    public:
        virtual IAttribute* getAttributeByName(const std::string& name) = 0;
        virtual const IAttribute* getAttributeByName(const std::string& name) const = 0;

        virtual ~IAttributeContainer() { }
    };
}


#endif //EQUEUE_V2_IATTRIBUTECONTAINER_H
