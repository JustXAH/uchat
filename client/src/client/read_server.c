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
            case AUTHENTICATION:
                mx_authentication_client(sys, user, json);
                break;
            case REGISTRATION:
                mx_confirmation_of_registration(sys, user, json);
                break;
            case WHO_ONLINE:
                mx_who_online_update(sys, user, json);
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
                mx_add_new_chat(sys, user, json);
                break;
            case GET_LOGIN:
                mx_get_login(sys, user, json);
                break;
            case NEW_MESSAGE:
                write(1, "NEW MESSAGE\n", 12);
                // функция, которая принимает ответ от запроса на подгрузку последних сообщений
                break;
            case LAST_MESSAGES:
                write(1, "LAST MESSAGES\n", 14);
                // функция, которая принимает ответ от запроса на подгрузку последних сообщений
                break;
        }
        cJSON_Delete(json->SERVER_JSON);
    }
    free(json);
    return 0;
}
