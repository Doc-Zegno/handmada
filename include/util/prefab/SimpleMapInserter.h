//
// Created by syzegno on 08.05.17.
//

#ifndef EQUEUE_V2_SIMPLEMAPINSERTER_H
#define EQUEUE_V2_SIMPLEMAPINSERTER_H


#include <utility>

#include "../../abstract/IMapInserter.h"


namespace Handmada {
    namespace Prefab {
        template<typename TContainer>
        class SimpleMapInserter : public IMapInserter<typename TContainer::key_type,
                typename TContainer::mapped_type>
        {
        private:
            TContainer& container_;

        public:
            using K = typename TContainer::key_type;
            using V = typename TContainer::mapped_type;

            SimpleMapInserter(TContainer& container) : container_(container)
            {}

            virtual void insert(const K& key, const V& value) override
            {
                container_.insert(std::make_pair(key, value));
            }
        };


        template<typename TContainer>
        SimpleMapInserter<TContainer> makeSimpleMapInserter(TContainer& container)
        {
            return SimpleMapInserter<TContainer>(container);
        };
    }
}



#endif //EQUEUE_V2_SIMPLEMAPINSERTER_H
