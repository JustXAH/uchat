//
// Created by Igor Khanenko on 1/5/21.
//

#include "server.h"

void mx_user_registration(cJSON *user_JSON, int user_sock) {
    char *send = NULL;
    cJSON *REGISTRATION = mx_database_stub(user_JSON);

    send = cJSON_Print(REGISTRATION);

    write(user_sock, send, strlen(send));

    cJSON_Delete(REGISTRATION);
    free(send);
}
