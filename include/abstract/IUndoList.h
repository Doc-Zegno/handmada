//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_IUNDOLIST_H
#define EQUEUE_V2_IUNDOLIST_H


#include <memory>

#include "IRequest.h"


namespace Handmada {
    /**
     * Perhaps the simplest undo-list interface possible.
     * Effectively stores the undo-versions of sent requests
     * using stack model.
     * Doesn't provide any support for redo
     */
    class IUndoList
    {
    public:
        /// \return true is undo list is empty
        virtual bool isEmpty() const = 0;
        /**
         * Adds new undo-version of request to the stack
         * @param request pointer to the request's undo-version
         */
        virtual void push(std::unique_ptr<IRequest>&& request) = 0;
        /**
         * Retrieves the latest undo-request and deletes its internal copy
         * @return a pointer to the latest undo-request stored in the list
         */
        virtual std::unique_ptr<IRequest> pop() = 0;
        /**
         * Provides an access to the latest undo-request without popping it
         * @return the latest undo-request stored in the list
         */
        virtual const IRequest* peek() const = 0;
        /// Removes all the stored requests from the list
        virtual void clear() = 0;

        virtual ~IUndoList() { }
    };
}


#endif //EQUEUE_V2_IUNDOLIST_H
