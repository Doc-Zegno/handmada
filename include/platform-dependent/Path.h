//
// Created by syzegno on 16.05.17.
//

#ifndef EQUEUE_V2_PATH_H
#define EQUEUE_V2_PATH_H


namespace Handmada {
    const char* const dumpPath                  = "dump";
    const char* const loginsToUserIdsPath       = "login2userId.dump";
    const char* const userIdsToLoginsPath       = "userId2login.dump";
    const char* const usersAttributesPath       = "userAttributes.dump";
    const char* const messagesForUsersPath      = "messages.dump";
    const char* const namesToServiceIdsPath     = "name2serviceId.dump";
    const char* const servicesPath              = "services.dump";
    const char* const servicePredicatesPath     = "predicates.dump";
    const char* const serviceRequirementsPath   = "requirements.dump";
    const char* const namesToSpecialistsIdsPath = "name2specialistId.dump";
    const char* const idsToSpecialistsPath      = "id2specialist.dump";

    const char* const paths[] = {
            loginsToUserIdsPath,
            userIdsToLoginsPath,
            usersAttributesPath,
            messagesForUsersPath,
            namesToServiceIdsPath,
            servicesPath,
            servicePredicatesPath,
            serviceRequirementsPath,
            namesToSpecialistsIdsPath,
            idsToSpecialistsPath
    };
}


#endif //EQUEUE_V2_PATH_H
