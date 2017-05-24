//
// Created by syzegno on 14.05.17.
//


#include "DescriptorKeyComparator.h"


namespace Handmada {
    bool PredicateDescriptorKeyComparator::operator()(
            const BigPredicateDescriptor& a, const BigPredicateDescriptor& b
    ) const
    {
        return a.id() == b.id();
    }


    bool RequirementDescriptorKeyComparator::operator()(
            const RequirementDescriptor& a, const RequirementDescriptor& b
    ) const
    {
        return a.requirement().name() == b.requirement().name();
    }
}
