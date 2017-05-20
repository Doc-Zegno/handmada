//
// Created by syzegno on 14.05.17.
//


#include "DescriptorHash.h"


namespace Handmada {
    size_t PredicateDescriptorHash::operator()(const BigPredicateDescriptor& descriptor) const
    {
        return std::hash<PredicateId>()(descriptor.id());
    }


    size_t RequirementDescriptorHash::operator()(const RequirementDescriptor& descriptor) const
    {
        return std::hash<std::string>()(descriptor.requirement().name());
    }
}
