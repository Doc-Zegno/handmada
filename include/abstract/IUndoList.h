//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_IUNDOLIST_H
#define EQUEUE_V2_IUNDOLIST_H


#include <memory>

#include "IRequest.h"


namespace Handmada {
    class IUndoList
    {
    public:
        virtual bool isEmpty() const = 0;
        virtual void push(std::unique_ptr<IRequest>&& request) = 0;
        virtual std::unique_ptr<IRequest> pop() = 0;
        virtual const IRequest* peek() const = 0;
        virtual void clear() = 0;

        virtual ~IUndoList() { }
    };
}


#endif //EQUEUE_V2_IUNDOLIST_H
