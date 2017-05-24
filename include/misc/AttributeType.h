//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_ATTRIBUTETYPE_H
#define EQUEUE_V2_ATTRIBUTETYPE_H


namespace Handmada {
    class AttributeType
    {
    public:
        AttributeType() = delete;

        enum Type {
            DUMMY,
            STRING,
            NUMBER,
            BOOLEAN,
        };

        static const char* toString(AttributeType::Type type);
    };
}


#endif //EQUEUE_V2_ATTRIBUTETYPE_H
