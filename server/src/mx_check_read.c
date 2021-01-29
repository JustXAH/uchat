//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

static void read_and_write(t_server *serv, int user_index) {
    t_json *json = (t_json *)malloc(sizeof(t_json));
    char buff_message[MAX_LEN];

    serv->type_enum = -1;
    mx_json_struct_initialization(json);
    read(serv->user_socket[user_index], buff_message, MAX_LEN);

//        Send the message back to client
    if (buff_message[0] != '\0') {
        json->USER_JSON = cJSON_Parse(buff_message);
        json->TYPE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "TYPE");
        serv->type_enum = json->TYPE->valueint;
        switch (serv->type_enum) {
            case AUTHENTICATION:
                mx_login_and_pass_authentication(serv, json, user_index);
                break;
            case REGISTRATION:
                mx_user_registration(serv, json, user_index);
                break;
            case WHO_ONLINE:
                mx_sending_who_online(serv, user_index);
                break;
            case USER_SEARCH_BY_SUBSTRING:
                mx_user_search_by_substr(serv, json, user_index);
                break;
            case USER_SEARCH_BY_LOGIN:
                mx_user_search_by_login(serv, json, user_index);
                break;
            case NEW_CONTACT:
                mx_add_new_contact(serv, json, user_index);
                break;
            case NEW_CHAT:
                mx_add_new_chat(serv, json, user_index);
                break;
            case GET_LOGIN:
                mx_get_login(serv, json, user_index);
                break;
            case NEW_MESSAGE:
                mx_add_new_message(serv, json, user_index);
                break;
            case HISTORY_CHAT:
                mx_history_chat(serv, json, user_index);
                break;
            case NEW_VOICE:
                mx_save_voice_file_and_get_id(serv, json, user_index);
                break;
            case SEND_VOICE_TO_USER:
                mx_send_voice_file_handler(serv, json, user_index);
                break;
            case NEW_USER_PIC:
                mx_save_user_pic_and_get_id(serv, json, user_index);
                break;
            case REMOVE_NOTIFICATION:
                mx_remove_notification(serv, json);
        }
    }
    cJSON_Delete(json->USER_JSON);
    free(json);
}

void mx_check_read(t_server *serv, int user_index) {
    struct pollfd poll_set[1];
    int ret = 0;

    // от socket[i] мы будем ожидать входящих данных
    poll_set->fd = serv->user_socket[user_index];
    poll_set->events = POLLIN;

    // ждём до 1 секунд
    ret = poll(poll_set, 1, 1);

    if (ret != -1 && ret != 0) {
        // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
        if (poll_set->revents & POLLIN) {
            // обработка входных данных от sock1
            poll_set->revents = 0;
            read_and_write(serv, user_index);
        }
    }
}
