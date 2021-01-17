//
// Created by mac on 15.01.2021.
//

#include "client.h"

void *read_server(void *data) {
    t_chat *chat = (t_chat *)data;
    t_system *sys = chat->sys;
    t_user *user = chat->user;
    t_json *json = (t_json *)malloc(sizeof(t_json));
    char buff[MAX_LEN];

    while (read(sys->sockfd, buff, sizeof(buff))) {
        json->SERVER_JSON = cJSON_Parse(buff);
        json->TYPE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "TYPE");
        sys->type_enum = json->TYPE->valueint;
        switch (sys->type_enum) {
            case TYPE_NULL: // создана из-за того что enum начинает отсчет с 0, а типы с 1
                // stub
                write(1, "\nIt's stub for TYPE_NULL enum\n", 30);
                break;
            case MESSAGES:
                // nothing here
                break;
            case AUTHENTICATION:
                mx_authentication_client(sys, user, json);
                break;
            case REGISTRATION:
                mx_confirmation_of_registration(sys, user, json);
                break;
            case USER_SEARCH_BY_SUBSTRING:
                mx_found_users_by_substr(sys, user, json);
                break;
            case USER_SEARCH_BY_LOGIN:
                mx_found_user_by_login(sys, user, json);
                break;
            case NEW_CONTACT:
                mx_add_new_contact(sys, user, json);
                break;
            case NEW_CHAT:
                // функция, которая принимает ответ от запроса на создание нового чата
                break;
            case GET_LOGIN:
                // функция, которая принимает ответ от запроса на получение логина юзера по ID
                break;
            case NEW_MESSAGE:
                // функция, которая принимает ответ от запроса на создание нового сообщения
                break;
            case LAST_MESSAGES:
                // функция, которая принимает ответ от запроса на подгрузку последних сообщений
                break;
        }
        cJSON_Delete(json->SERVER_JSON);
    }
    free(json);
    return 0;
//        if (TYPE != NULL) {
//            if (TYPE->valueint == 2) { //аутентификация
//                mx_authentication_client(sys, user, SERVER_JSON);
//            }
//            else if (TYPE->valueint == 3) { //подтверждение регистрации
//                mx_confirmation_of_registration(sys, user, SERVER_JSON);
//                if (sys->registration == true) {
//                    mx_account_login_request(sys, user);
//                }
//            }
//            else { //TYPE == 1 (сообщения)
////                pthread_mutex_lock(&sys->mutex);
//                SENDER = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                                          "LOGIN");
//                MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                                           "MESSAGE");
//                write (1, "\nFrom ", 6);
//                write(1, SENDER->valuestring, strlen(SENDER->valuestring));
//                write(1, ": ", 2);
//                write(1, MESSAGE->valuestring, strlen(MESSAGE->valuestring));
//                cJSON_DeleteItemFromObject(SERVER_JSON, "LOGIN");
////                pthread_mutex_unlock(&sys->mutex);
//            }
//            cJSON_DeleteItemFromObject(SERVER_JSON, "TYPE");
//            cJSON_DeleteItemFromObject(SERVER_JSON, "TO");
//            cJSON_DeleteItemFromObject(SERVER_JSON, "MESSAGE");
////        cJSON_free(MESSAGE);
//            memset(buff, '\0', sizeof(buff));
//        }
//        cJSON_Delete(SERVER_JSON);
//    }
}
