//
// Created by syzegno on 15.05.17.
//


#include "NullUndoList.h"


namespace Handmada {
    namespace Prefab {
        bool NullUndoList::isEmpty() const
        {
            return true;
        }


        void NullUndoList::push(std::unique_ptr<IRequest>&& request)
        { }


        std::unique_ptr<IRequest> NullUndoList::pop()
        {
            return std::unique_ptr<IRequest>();
        }


        void NullUndoList::clear()
        { }


        const IRequest* NullUndoList::peek() const
        {
            return nullptr;
        }
    }
}
