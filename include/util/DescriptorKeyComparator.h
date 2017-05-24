//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_DESCRIPTORKEYCOMPARATOR_H
#define EQUEUE_V2_DESCRIPTORKEYCOMPARATOR_H


#include "Descriptors.h"


namespace Handmada {
    class PredicateDescriptorKeyComparator
    {
    public:
        bool operator()(const BigPredicateDescriptor& a, const BigPredicateDescriptor& b) const;
    };


    class RequirementDescriptorKeyComparator
    {
    public:
        bool operator()(const RequirementDescriptor& a, const RequirementDescriptor& b) const;
    };
}


#endif //EQUEUE_V2_DESCRIPTORKEYCOMPARATOR_H
