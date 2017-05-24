//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_POLYVECTOR_H
#define EQUEUE_V2_POLYVECTOR_H


#include <memory>
#include <vector>


namespace Handmada {
    template<typename T>
    using PolyVector = std::vector<std::unique_ptr<T>>;
}


#endif //EQUEUE_V2_POLYVECTOR_H
