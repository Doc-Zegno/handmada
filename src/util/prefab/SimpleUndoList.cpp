//
// Created by syzegno on 15.05.17.
//


#include "SimpleUndoList.h"


namespace Handmada {
    namespace Prefab {
        SimpleUndoList::SimpleUndoList(size_t maxLength) : maxLength_(maxLength)
        {}


        bool SimpleUndoList::isEmpty() const
        {
            return requests_.empty();
        }


        void SimpleUndoList::push(std::unique_ptr<IRequest>&& request)
        {
            requests_.push_back(std::move(request));
            if (requests_.size() > maxLength_) {
                requests_.pop_front();
            }
        }


        std::unique_ptr<IRequest> SimpleUndoList::pop()
        {
            if (requests_.empty()) {
                return std::unique_ptr<IRequest>();
            } else {
                auto request = std::move(requests_.back());
                requests_.pop_back();
                return std::move(request);
            }
        }


        void SimpleUndoList::clear()
        {
            requests_.clear();
        }


        const IRequest* SimpleUndoList::peek() const
        {
            if (!requests_.empty()) {
                return requests_.back().get();
            }
            return nullptr;
        }
    }
}
