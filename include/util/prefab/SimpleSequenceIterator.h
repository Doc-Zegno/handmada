//
// Created by syzegno on 18.05.17.
//

#ifndef EQUEUE_V2_SIMPLESEQUENCEITERATOR_H
#define EQUEUE_V2_SIMPLESEQUENCEITERATOR_H


#include "SimpleIterator.h"


namespace Handmada {
    namespace Prefab {
        template<typename TSequence>
        std::unique_ptr<IIterator<typename TSequence::value_type>>
        makeSimpleSequenceIterator(TSequence& sequence)
        {
            return makeSimpleIterator<typename TSequence::value_type>(
                    &sequence,
                    [](typename TSequence::iterator& iter) {
                        return &*iter;
                    }
            );
        }
    }
}


#endif //EQUEUE_V2_SIMPLESEQUENCEITERATOR_H
