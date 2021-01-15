//
// Created by dima on 14.01.2021.
//

#include "server.h"

//void mx_last_messages(t_server *serv, int chat_id) {
//    cJSON *LAST_MESSAGES = cJSON_CreateObject();
//    cJSON *TYPE = cJSON_CreateNumber(LAST_MESSAGES); // create new messages
//    cJSON *RESULT = NULL; // результат аутентификации: FALSE - неудачно, TRUE - успешно
//    cJSON *MESSAGES_ID = NULL;
//    cJSON *CHAT_ID = cJSON_CreateNumber(chat_id);
//    cJSON *MESSAGES = cJSON_CreateString(message);
//    t_message *chat_message = NULL;
//
//    chat_message = mx_db_get_last_messages(serv->db, chat_id);
//    RESULT = chat_message == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();
//
//}
