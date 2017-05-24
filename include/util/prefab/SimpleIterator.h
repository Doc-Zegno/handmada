//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_SIMPLEITERATOR_H
#define EQUEUE_V2_SIMPLEITERATOR_H


#include <memory>

#include "../../abstract/IIterator.h"


namespace Handmada {
    namespace Prefab {
        template<typename T, typename TIterator, typename TGetter>
        class SimpleIterator : public IIterator<T>
        {
        private:
            TIterator iterator_;
            TIterator begin_;
            TIterator end_;
            TGetter getter_;

        public:
            SimpleIterator(
                    const TIterator& begin,
                    const TIterator& end,
                    const TGetter& getter
            ) : iterator_(begin), begin_(begin), end_(end), getter_(getter)
            {}

            virtual bool hasNext() const override
            {
                return iterator_ != end_;
            }

            virtual T* next() override
            {
                T* t = getter_(iterator_);
                ++iterator_;
                return t;
            }

            virtual void reset() override
            {
                iterator_ = begin_;
            }
        };


        template<typename T, typename TContainer, typename TFunction>
        std::unique_ptr<Handmada::IIterator<T>> makeSimpleIterator(
                TContainer* container,
                const TFunction& func
        )
        {
            return std::unique_ptr<Handmada::IIterator<T>>(
                    new SimpleIterator<T, typename TContainer::iterator, TFunction>(
                            container->begin(), container->end(), func
                    )
            );
        }


        template<typename T, typename TIterator, typename TFunction>
        std::unique_ptr<Handmada::IIterator<T>> makeAdvancedIterator(
                const TIterator& begin,
                const TIterator& end,
                const TFunction& getter
        )
        {
            return std::unique_ptr<IIterator<T>>(
                    new SimpleIterator<T, TIterator, TFunction>(begin, end, getter)
            );
        };
    }
}


#endif //EQUEUE_V2_SIMPLEITERATOR_H
