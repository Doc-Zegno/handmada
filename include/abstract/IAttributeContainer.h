//
// Created by syzegno on 03.05.17.
//

#ifndef EQUEUE_V2_IATTRIBUTECONTAINER_H
#define EQUEUE_V2_IATTRIBUTECONTAINER_H


#include "IAttribute.h"


namespace Handmada {
    class IAttributeContainer
    {
    public:
        virtual IAttribute* getAttributeByName(const std::string& name) = 0;
        virtual const IAttribute* getAttributeByName(const std::string& name) const = 0;

        virtual ~IAttributeContainer() { }
    };
}


#endif //EQUEUE_V2_IATTRIBUTECONTAINER_H
