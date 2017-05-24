//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_DESCRIPTORHASH_H
#define EQUEUE_V2_DESCRIPTORHASH_H


#include "Descriptors.h"


namespace Handmada {
    class PredicateDescriptorHash
    {
    public:
        size_t operator()(const BigPredicateDescriptor& descriptor) const;
    };


    class RequirementDescriptorHash
    {
    public:
        size_t operator()(const RequirementDescriptor& descriptor) const;
    };
}


#endif //EQUEUE_V2_DESCRIPTORHASH_H
