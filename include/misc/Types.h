//
// Created by syzegno on 23.04.17.
//


#ifndef EQUEUE_V2_TYPES_H
#define EQUEUE_V2_TYPES_H


namespace Handmada {
    using UserId = long;
    const UserId VALID_USER_ID = 0;
    const UserId INVALID_USER_ID = -1;
    const UserId USER_ALREADY_SIGN_IN = -2;

    inline bool isUserIdValid(UserId id)
    { return id >= 0; }


    using ServiceId = long;
    const ServiceId VALID_SERVICE_ID = 0;
    const ServiceId INVALID_SERVICE_ID = -1;

    inline bool isServiceIdValid(ServiceId id)
    { return id >= 0; }


    using SpecialistId = long;
    const ServiceId INVALID_SPECIALIST_ID = -1;

    inline bool isSpecialistIdValid(SpecialistId id)
    { return id >= 0; }


    using PredicateId = long;
    inline bool isPredicateIdValid(PredicateId id)
    { return id >= 0; }
}

#endif //EQUEUE_V2_TYPES_H
