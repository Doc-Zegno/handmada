//
// Created by syzegno on 01.05.17.
//

#ifndef EQUEUE_V2_IITERATOR_H
#define EQUEUE_V2_IITERATOR_H


namespace Handmada {
    /**
     * One of the most useful interfaces in this project.
     * It allows to completely hide the internal containers
     * that are used by different parts of program.
     * That's why it's very easy to change them without
     * crashing the rest of the program
     * @tparam T type of objects stored in the container
     */
    template<typename T>
    class IIterator
    {
    public:
        /**
         * This method is used to write iterator-base loops
         * @return true if there are objects in the container that haven't been read yet
         * and false otherwise
         */
        virtual bool hasNext() const = 0;
        /**
         * This method is used to get access to the next element in the container.
         * Upon retrieving the pointer an iterator moves forward
         * @return a pointer to the next element in the container
         */
        virtual T* next() = 0;
        /**
         * Effectively resets iterator to be pointing to the beginning of the container
         */
        virtual void reset() = 0;

        virtual ~IIterator() { }
    };
}


#endif //EQUEUE_V2_IITERATOR_H
