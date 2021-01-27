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
                break;
            case REGISTRATION:
                mx_confirmation_of_registration(sys, user, json);
                break;
            case WHO_ONLINE:
                write(1, "Who is on duty today?\n", 22);
                mx_who_online_update(sys, user, json);
                break;
            case USER_SEARCH_BY_SUBSTRING:
//                write(1, "Replied recieved from server!!!\n", 32);
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
                // this is the stub
                break;
            case LAST_MESSAGES:
                mx_get_last_messages(sys, user, json);
                write(1, "LAST MESSAGES\n", 14);
                // функция, которая принимает ответ от запроса на подгрузку последних сообщений
                break;
            case NEW_VOICE:
                write(1, "SAVE AUDIO\n", 11);
                mx_get_voice_file_id(sys, user, json);
                break;
            case SEND_VOICE_TO_USER:
                write(1, "SEND AUDIO\n", 11);
                mx_get_voice_file_from_user(sys, user, json);
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
