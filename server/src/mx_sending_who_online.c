//
// Created by Igor Khanenko on 1/25/21.
//

#include "server.h"

void mx_sending_who_online(t_server *serv, int user_index) {
    char *send_str = NULL;
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(WHO_ONLINE);
    cJSON *WHO_ONLINE = cJSON_CreateIntArray(serv->users_id, MAX_USERS);

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "WHO_ONLINE", WHO_ONLINE);

    send_str = cJSON_Print(SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
}
