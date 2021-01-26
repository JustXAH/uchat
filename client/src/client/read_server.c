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

    while (sys->exit != true) {
        read(sys->sockfd, buff, sizeof(buff));
//        write(1, "YUHU! I just received a response from the server\n", 49);
        json->SERVER_JSON = cJSON_Parse(buff);
        json->TYPE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "TYPE");
        sys->type_enum = json->TYPE->valueint;
        printf("\nSwitch starting enum: %d  buff: %s\n",sys->type_enum, buff);
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
                mx_printstr("new contact about to be recieved from the server\n");
                mx_add_new_contact(sys, user, json);
                cl_listener.pending_requests[NEW_CONTACT] = false;
                mx_printstr("new contact recieved from the server\n");
                break;
            case NEW_CHAT:
                mx_add_new_chat(sys, user, json);
                cl_listener.pending_requests[NEW_CHAT] = false;
                mx_printstr("new chat recieved from the server\n");
                break;
            case GET_LOGIN:
                mx_get_login(sys, user, json);
                cl_listener.pending_requests[GET_LOGIN] = false;
                break;
            case NEW_MESSAGE:
                mx_add_new_message(sys, user, json);
                cl_listener.pending_requests[NEW_MESSAGE] = false;
                break;
            case LAST_MESSAGES:
                mx_get_last_messages(sys, user, json);
                write(1, "LAST MESSAGES\n", 14);
                cl_listener.pending_requests[LAST_MESSAGES] = false;
                // функция, которая принимает ответ от запроса на подгрузку последних сообщений
                break;
            case SAVE_AUDIO:
                write(1, "SAVE AUDIO\n", 11);
                break;
            case SEND_AUDIO:
                write(1, "SEND AUDIO\n", 11);
                break;
        }
        printf("Switch ending\n");
        cJSON_Delete(json->SERVER_JSON);
        memset(buff, '\0', sizeof(buff));
    }
    free(json);
    printf("Read fucking done\n");
    return 0;
}
