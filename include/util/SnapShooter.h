//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_SNAPSHOOTER_H
#define EQUEUE_V2_SNAPSHOOTER_H


#include "PolyVector.h"


namespace Handmada {
    /**
     * Provides classes with a function that makes copies of poly vectors
     */
    class SnapShooter
    {
    public:
        template<typename T>
        static PolyVector<T> copy(const PolyVector<T>& polyVector);
    };


    template<typename T>
    PolyVector<T> SnapShooter::copy(const PolyVector<T>& polyVector)
    {
        PolyVector<T> copy;
        for (auto& item : polyVector) {
            copy.push_back(item->clone());
        }
        return std::move(copy);
    }
}


#endif //EQUEUE_V2_SNAPSHOOTER_H
