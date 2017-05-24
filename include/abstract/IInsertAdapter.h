//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_IINSERTADAPTER_H
#define EQUEUE_V2_IINSERTADAPTER_H


#include <memory>


namespace Handmada {
    template<typename T>
    class IInsertAdapter
    {
    public:
        virtual void insert(std::unique_ptr<T>&& value) = 0;

        virtual ~IInsertAdapter() { }
    };
}


#endif //EQUEUE_V2_IINSERTADAPTER_H
