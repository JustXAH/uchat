//
// Created by mac on 15.01.2021.
//

#include "client.h"

extern t_client_st cl_listener;

void *read_server(void *data) {
    t_chat *chat = (t_chat *)data;
    t_system *sys = chat->sys;
    t_user *user = chat->user;
    t_json *json = (t_json *)malloc(sizeof(t_json));
    char buff[MAX_LEN];

    while (chat->sys->exit != 1) {
        read(sys->sockfd, buff, sizeof(buff));
        json->SERVER_JSON = cJSON_Parse(buff);
        json->TYPE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "TYPE");
        sys->type_enum = json->TYPE->valueint;
        switch (sys->type_enum) {
            case AUTHENTICATION:
                mx_authentication_client(sys, user, json);
                cl_listener.pending_requests[AUTHENTICATION] = false;
                break;
            case REGISTRATION:
                mx_confirmation_of_registration(sys, user, json);
                cl_listener.pending_requests[REGISTRATION] = false;
                break;
            case WHO_ONLINE:
                mx_who_online_update(sys, user, json);
                cl_listener.pending_requests[WHO_ONLINE] = false;
                break;
            case USER_SEARCH_BY_SUBSTRING:
                mx_found_users_by_substr(sys, user, json);
                cl_listener.pending_requests[USER_SEARCH_BY_SUBSTRING] = false;
                break;
            case USER_SEARCH_BY_LOGIN:
                mx_found_user_by_login(sys, user, json);
                cl_listener.pending_requests[USER_SEARCH_BY_LOGIN] = false;
                break;
            case NEW_CONTACT:
                mx_add_new_contact(sys, user, json);
                cl_listener.pending_requests[NEW_CONTACT] = false;
                break;
            case NEW_CHAT:
                mx_add_new_chat(sys, user, json);
                cl_listener.pending_requests[NEW_CHAT] = false;
                break;
            case GET_LOGIN:
                mx_get_login(sys, user, json);
                cl_listener.pending_requests[GET_LOGIN] = false;
                break;
            case NEW_MESSAGE:
                mx_add_new_message(sys, user, json);
                cl_listener.pending_requests[NEW_MESSAGE] = false;
                break;
            case HISTORY_CHAT:
                mx_get_history_chat(sys, user, json);
                cl_listener.pending_requests[HISTORY_CHAT] = false;
                break;
            case NEW_VOICE:
                mx_get_voice_file_id(sys, user, json);
                break;
            case SEND_VOICE_TO_USER:
                mx_get_voice_file_from_user(sys, user, json);
                break;
            case NEW_USER_PIC:
                mx_get_user_pic_id(sys, user, json);
                break;
            case REMOVE_NOTIFICATION:
                break;
        }
        cJSON_Delete(json->SERVER_JSON);
        memset(buff, '\0', sizeof(buff));
    }
    free(json);
    chat->sys->exit = 2;
    return 0;
}
