//
// Created by syzegno on 07.05.17.
//

#ifndef EQUEUE_V2_COMPAREFLAG_H
#define EQUEUE_V2_COMPAREFLAG_H


namespace Handmada {
    class ComparisonFlag
    {
    public:
        ComparisonFlag() = delete;

        enum Type {
            LESS,
            EQUAL,
            GREATER,
            NOT_EQUAL,
            LESS_OR_EQUAL,
            GREATER_OR_EQUAL,
        };

        static const char* toString(ComparisonFlag::Type flag);
        /**
         * Each comparator needs to decide whether the result of comparing
         * satisfies requirements. Obviously, such analysis requires
         * significant effort since, for example, negative result of comparing
         * satisfies both LESS and LESS_OR_EQUAL requirements.
         * @param result result of comparing attributes
         * @param flag requirements, i.e. LESS, LESS_OR_EQUAL and so on
         * @return true if result satisfies flag and false otherwise
         */
        static bool isCompatible(int result, ComparisonFlag::Type flag);
    };
}


#endif //EQUEUE_V2_COMPAREFLAG_H
