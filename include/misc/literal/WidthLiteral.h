//
// Created by syzegno on 16.05.17.
//

#ifndef EQUEUE_V2_WIDTHLITERAL_H
#define EQUEUE_V2_WIDTHLITERAL_H


#include <cstddef>


namespace Handmada {
    namespace Literal {
        class WidthLiteral
        {
        private:
            size_t width_;

        public:
            constexpr WidthLiteral(size_t width) : width_(width) { }

            constexpr size_t width() const { return width_; }
        };
    }


    constexpr Literal::WidthLiteral operator "" _width(unsigned long long width)
    {
        return Literal::WidthLiteral(width);
    }
}


#endif //EQUEUE_V2_WIDTHLITERAL_H
