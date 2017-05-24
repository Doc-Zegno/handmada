//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_SIMPLEPOLYSEQUENCEITERATOR_H
#define EQUEUE_V2_SIMPLEPOLYSEQUENCEITERATOR_H


#include "SimpleIterator.h"


namespace Handmada {
    namespace Prefab {
        /**
         * Initial intention was to adapt makeSimpleIterator<T> function for
         * std::vector<std::unique_ptr<T>>
         * @tparam TSequence type of sequence, i.e. vector, deque, list
         * @param sequence sequence of unique_ptr's to polymorphic objects
         * @return unique_ptr wrapped around instance of IIterator<T>
         */
        template<typename TSequence>
        std::unique_ptr<Handmada::IIterator<typename TSequence::value_type::element_type>>
        makeSimplePolySequenceIterator(TSequence& sequence)
        {
            return makeSimpleIterator<typename TSequence::value_type::element_type>(
                    &sequence,
                    [](typename TSequence::iterator& it) {
                        return it->get();
                    }
            );
        }
    }
}


#endif //EQUEUE_V2_SIMPLEPOLYSEQUENCEITERATOR_H
