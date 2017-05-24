//
// Created by syzegno on 01.05.17.
//

#ifndef EQUEUE_V2_IITERATOR_H
#define EQUEUE_V2_IITERATOR_H


namespace Handmada {
    template<typename T>
    class IIterator
    {
    public:
        virtual bool hasNext() const = 0;
        virtual T* next() = 0;
        virtual void reset() = 0;

        virtual ~IIterator() { }
    };
}


#endif //EQUEUE_V2_IITERATOR_H
