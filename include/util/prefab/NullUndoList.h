//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_NULLUNDOLIST_H
#define EQUEUE_V2_NULLUNDOLIST_H


#include "IUndoList.h"


namespace Handmada {
    namespace Prefab {
        /**
         * This list discards all requests that are pushed into it.
         * Useful for preventing the system from pushing an undo-version
         * of undo-request
         */
        class NullUndoList : public IUndoList
        {
        public:
            virtual bool isEmpty() const override;
            virtual void push(std::unique_ptr<IRequest>&& request) override;
            virtual std::unique_ptr<IRequest> pop() override;
            virtual const IRequest* peek() const override;
            virtual void clear() override;
        };
    }
}


#endif //EQUEUE_V2_NULLUNDOLIST_H
