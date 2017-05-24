//
// Created by syzegno on 02.05.17.
//

#ifndef EQUEUE_V2_OPCODE_H
#define EQUEUE_V2_OPCODE_H


namespace Handmada {
    enum class OpCode {
        SUCCESS,
        GENERAL_FAILURE,
        MISSING_ATTRIBUTES,
        ALREADY_HAS_ATTRIBUTE,
        ALREADY_IN_QUEUE,

        ALREADY_REGISTERED,
        ALREADY_SIGN_IN,
        ALREADY_SIGN_OUT,
        NOT_REGISTERED,

        REQUIREMENT_TYPE_COLLISION,

        NO_SUCH_USER,
        NO_SUCH_SERVICE,
        NO_SUCH_SPECIALIST,
        ALREADY_ATTACHED,

        SERVICE_EXISTS,
        SPECIALIST_EXISTS,
    };
}

#endif //EQUEUE_V2_OPCODE_H
