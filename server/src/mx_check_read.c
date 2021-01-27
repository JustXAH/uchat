//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

static void read_and_write(t_server *serv, int user_index) {
    t_json *json = (t_json *)malloc(sizeof(t_json));
    char buff_message[MAX_LEN];

    serv->type_enum = -1;
    mx_json_struct_initialization(json);
    write(1, "Waiting for a json from client...\n", 25);
    read(serv->user_socket[user_index], buff_message, MAX_LEN);

//        Send the message back to client
    if (buff_message[0] != '\0') {

        json->USER_JSON = cJSON_Parse(buff_message);
        json->TYPE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "TYPE");
        mx_printstr(buff_message);
        mx_printstr("\n");
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
                mx_user_search_by_login(serv, json, user_index); // добавить аватарку
                break;
            case NEW_CONTACT:
                mx_printstr("about to add a new contact\n");
                mx_add_new_contact(serv, json, user_index);
                mx_printstr("succesfully added a new contact\n");
                break;
            case NEW_CHAT:
                mx_printstr("about to add a new chat\n");
                mx_add_new_chat(serv, json, user_index);
                mx_printstr("succesfully added a new chat\n");
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
        }
        printf("\nServer sent a response to the USER (SOCKET: %d ID: %d)\n",
               serv->user_socket[user_index], serv->users_id[user_index]);
    }
    cJSON_Delete(json->USER_JSON);
    free(json);
}

void mx_check_read(t_server *serv, int user_index) {
    struct pollfd poll_set[1];
    int ret = 0;

    printf("------------------------------\n");
    printf("CHECK READ CLIENT SOCKET\n");
    printf("cli_connect = %d\n", serv->cli_connect);
    // от socket[i] мы будем ожидать входящих данных

    poll_set->fd = serv->user_socket[user_index];
    poll_set->events = POLLIN;

    // ждём до 1 секунд
    ret = poll(poll_set, 1, 1);
    printf("ret = %d\n", ret);
    printf("socket = %d[%d]\n", serv->user_socket[user_index], user_index);
    printf("user id = %d\n", serv->users_id[user_index]);

    // проверяем успешность вызова
    if (ret == -1) {
        // ошибка
        printf("ERROR, poll checking client socket #%d\n", user_index);
    }
    else if (ret == 0) {
        // таймаут, событий не произошло
        write(1, "No events happened\n", 19);
    }
    else {
        // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
        if (poll_set->revents & POLLIN) {
            // обработка входных данных от sock1
            poll_set->revents = 0;
            read_and_write(serv, user_index);
        }
    }
    printf("------------------------------\n");
}
