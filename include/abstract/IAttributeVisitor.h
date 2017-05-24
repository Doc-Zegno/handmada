//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_IVISITOR_H
#define EQUEUE_V2_IVISITOR_H


#include "../model/Attributes.h"


namespace Handmada {
    class IAttributeVisitor
    {
    public:
        virtual void visit(const StringAttribute& attribute) = 0;
        virtual void visit(const NumberAttribute& attribute) = 0;
        virtual void visit(const BooleanAttribute& attribute) = 0;

        virtual ~IAttributeVisitor() { }
    };
}

#endif //EQUEUE_V2_IVISITOR_H
