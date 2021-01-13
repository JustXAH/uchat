//
// Created by dima on 12.01.2021.
//

#include "server.h"

void mx_add_new_message(t_server *serv, int user_id, int contact_id, char *message) {
    cJSON *NEW_MESSAGES = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(NEW_MESSAGE); // create new messages
    cJSON *RESULT = NULL; // результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *MESSAGES_ID = NULL;
    cJSON *MESSAGES = cJSON_CreateString(message);

    char *send = NULL;

    MESSAGES_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, user_id, mx_db_get_chat_by_users(serv->db, user_id, contact_id), message));
    RESULT = MESSAGES_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    cJSON_AddItemToObject(NEW_MESSAGES, "TYPE", TYPE);
    cJSON_AddItemToObject(NEW_MESSAGES, "RESULT", RESULT);
    cJSON_AddItemToObject(NEW_MESSAGES, "MESSAGES_ID", MESSAGES_ID);
    cJSON_AddItemToObject(NEW_MESSAGES, "MESSAGES", MESSAGES);

    send = cJSON_Print(NEW_MESSAGES);

//    write(user_sock, send, strlen(send));

    cJSON_Delete(NEW_MESSAGES);
    free(send);
}