//
// Created by syzegno on 07.05.17.
//


#include "ComparisonFlag.h"


namespace Handmada {
    const char* ComparisonFlag::toString(ComparisonFlag::Type flag)
    {
        switch (flag) {
        case ComparisonFlag::LESS:
            return "<";
        case ComparisonFlag::EQUAL:
            return "==";
        case ComparisonFlag::GREATER:
            return ">";
        case ComparisonFlag::NOT_EQUAL:
            return "!=";
        case ComparisonFlag::LESS_OR_EQUAL:
            return "<=";
        case ComparisonFlag::GREATER_OR_EQUAL:
            return ">=";
        default:
            return "";
        }
    }


    bool ComparisonFlag::isCompatible(int result, ComparisonFlag::Type flag)
    {
        if (result < 0) {
            switch (flag) {
            case ComparisonFlag::LESS:
            case ComparisonFlag::LESS_OR_EQUAL:
            case ComparisonFlag::NOT_EQUAL:
                return true;

            default:
                return false;
            }

        } else if (result == 0) {
            switch (flag) {
            case ComparisonFlag::LESS_OR_EQUAL:
            case ComparisonFlag::EQUAL:
            case ComparisonFlag::GREATER_OR_EQUAL:
                return true;

            default:
                return false;
            }

        } else {
            switch (flag) {
            case ComparisonFlag::GREATER_OR_EQUAL:
            case ComparisonFlag::GREATER:
            case ComparisonFlag::NOT_EQUAL:
                return true;

            default:
                return false;
            }
        }
    }
}

