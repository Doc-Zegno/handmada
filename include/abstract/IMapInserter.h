//
// Created by syzegno on 08.05.17.
//

#ifndef EQUEUE_V2_IMAPINSERTER_H
#define EQUEUE_V2_IMAPINSERTER_H


namespace Handmada {
    template<typename K, typename V>
    class IMapInserter
    {
    public:
        virtual void insert(const K& key, const V& value) = 0;

        virtual ~IMapInserter() { }
    };
}


#endif //EQUEUE_V2_IMAPINSERTER_H
