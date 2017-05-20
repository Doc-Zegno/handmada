//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_SIMPLEUNDOLIST_H
#define EQUEUE_V2_SIMPLEUNDOLIST_H


#include <list>

#include "IUndoList.h"


namespace Handmada {
    namespace Prefab {
        /**
         * Uses std::list to implement IUndoList
         */
        class SimpleUndoList : public IUndoList
        {
        private:
            size_t maxLength_;
            std::list<std::unique_ptr<IRequest>> requests_;

        public:
            SimpleUndoList(size_t maxLength = 10);

            virtual bool isEmpty() const override;
            virtual void push(std::unique_ptr<IRequest>&& request) override;
            virtual std::unique_ptr<IRequest> pop() override;
            virtual const IRequest* peek() const override;
            virtual void clear() override;
        };
    }
}


#endif //EQUEUE_V2_SIMPLEUNDOLIST_H
