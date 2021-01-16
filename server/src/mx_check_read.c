//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

static void read_and_write(t_server *serv, int user_num) {
    t_json *json = (t_json *)malloc(sizeof(t_json));
    char buff_message[MAX];

    write(1, "Waiting for a message...\n", 25);
    read(serv->user_socket[user_num], buff_message, MAX);

//        Send the message back to client
    if (buff_message[0] != '\0') {
        json->USER_JSON = cJSON_Parse(buff_message);
        json->TYPE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "TYPE");
        serv->type_enum = json->TYPE->valueint;
        switch (serv->type_enum) {
            case TYPE_NULL: // создана из-за того что enum начинает отсчет с 0, а типы с 1
                break;
            case MESSAGES:
//                json->MESSAGE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "MESSAGE");
//                json->TO = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "TO");
//                printf("Sender = %s\nmessage = %s\n", cJSON_Print(json->LOGIN),
//                       cJSON_Print(json->MESSAGE));
//                if (serv->cli_connect - 1 >= json->TO->valueint) {
//                    printf("%s\n", cJSON_Print(json->USER_JSON));
//                    write(serv->user_socket[json->TO->valueint], cJSON_Print(json->USER_JSON),
//                          mx_strlen(cJSON_Print(json->USER_JSON)));
//                } else {
//                    cJSON_DeleteItemFromObject(json->USER_JSON, "MESSAGE");
//                    cJSON_DeleteItemFromObject(json->USER_JSON, "TO");
//                    json->TO = cJSON_CreateString(mx_itoa(user_num));
//                    json->MESSAGE = cJSON_CreateString("User not found");
//                    cJSON_AddItemToObject(json->USER_JSON, "TO", json->TO);
//                    cJSON_AddItemToObject(json->USER_JSON, "MESSAGE", json->MESSAGE);
//                    printf("%s\n", cJSON_Print(json->USER_JSON));
//                    write(serv->user_socket[user_num], cJSON_Print(json->USER_JSON), mx_strlen(cJSON_Print(json->USER_JSON)));
//                }
//              free(buff_message);
                memset(&buff_message, '\0', sizeof(buff_message));
                break;
            case AUTHENTICATION:
                json->LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "LOGIN");
                json->PASS = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "PASS");
                mx_login_and_pass_authentication(serv, json, serv->user_socket[user_num]);
                break;
            case REGISTRATION:
                json->LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "LOGIN");
                json->PASS = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "PASS");
                mx_user_registration(serv, json, serv->user_socket[user_num]);
                break;
            case USER_SEARCH_BY_SUBSTRING:
                mx_user_search_by_substr(serv, json, serv->user_socket[user_num]);
                break;
            case USER_SEARCH_BY_LOGIN:
                mx_user_search_by_login(serv, json, serv->user_socket[user_num]);
                break;
            case NEW_CONTACT:
                mx_add_new_contact(serv, json, serv->user_socket[user_num]);
                break;
            case NEW_CHAT:
                mx_add_new_chat(serv, json, serv->user_socket[user_num]); // нужно доделать
                break;
            case GET_LOGIN:
                mx_get_login(serv, json, serv->user_socket[user_num]); // нужно доделать
                break;
            case NEW_MESSAGE:
                mx_add_new_message(serv, json);
                break;
            case LAST_MESSAGES:
//                mx_last_messages(serv, json); //переделай под json структуру
                break;
        }
//        if (TYPE->valueint == 2) { // аутентификация
//            PASS = cJSON_GetObjectItemCaseSensitive(USER_JSON, "PASS");
//            mx_login_and_pass_authentication(serv, LOGIN->valuestring, PASS->valuestring, serv->user_socket[user_num]);
//        else if (TYPE->valueint == 3) { // регистрация
//            PASS = cJSON_GetObjectItemCaseSensitive(USER_JSON, "PASS");
//            mx_user_registration(serv, LOGIN->valuestring, PASS->valuestring, serv->user_socket[user_num]);
//        }
//        else if (TYPE->valueint == 4) { // поиск контакта по полному логину
//            mx_user_search(serv, LOGIN->valuestring, serv->user_socket[user_num]);
//        }
//        else if (TYPE->valueint == 5) { // create new contact
//            mx_add_new_contact(serv, USER_ID->valueint, CONTACT_ID->valueint, serv->user_socket[user_num]);
//        }
//        else if (TYPE->valueint == 6) { // create new chat
//            mx_add_new_chat(serv, USER_ID->valueint, CONTACT_ID->valueint, serv->user_socket[user_num]);
//        }
//        else if (TYPE->valueint == 10) { // system calls (now just db_init)
//            mx_db_init(serv->db);
//        }
//        else { //это TYPE = 1 - сообщения!
//            MESSAGE = cJSON_GetObjectItemCaseSensitive(USER_JSON, "MESSAGE");
//            TO = cJSON_GetObjectItemCaseSensitive(USER_JSON, "TO");
//            printf("Sender = %s\nmessage = %s\n", cJSON_Print(LOGIN),
//                   cJSON_Print(MESSAGE));
//            if (serv->cli_connect - 1 >= TO->valueint) {
//                printf("%s\n", cJSON_Print(USER_JSON));
//                write(serv->user_socket[TO->valueint], cJSON_Print(USER_JSON),
//                      mx_strlen(cJSON_Print(USER_JSON)));
//            }
//            else {
//                cJSON_DeleteItemFromObject(USER_JSON, "MESSAGE");
//                cJSON_DeleteItemFromObject(USER_JSON, "TO");
//                TO = cJSON_CreateString(mx_itoa(user_num));
//                MESSAGE = cJSON_CreateString("User not found");
//                cJSON_AddItemToObject(USER_JSON, "TO", TO);
//                cJSON_AddItemToObject(USER_JSON, "MESSAGE", MESSAGE);
//                printf("%s\n", cJSON_Print(USER_JSON));
//                write(serv->user_socket[user_num], cJSON_Print(USER_JSON), mx_strlen(cJSON_Print(USER_JSON)));
//            }
////            free(buff_message);
//            memset(&buff_message, '\0', sizeof(buff_message));
//        }
    }
    cJSON_Delete(json->USER_JSON);
    free(json);
}

void mx_check_read(t_server *serv, int i) {
    struct pollfd poll_set[1];
    int ret = 0;

    printf("------------------------------\n");
    printf("CHECK READ CLIENT SOCKET\n");
    printf("cli_connect = %d\n", serv->cli_connect);
    // от socket[i] мы будем ожидать входящих данных

    poll_set->fd = serv->user_socket[i];
    poll_set->events = POLLIN;

    // ждём до 1 секунд
    ret = poll(poll_set, 1, 3000);
    printf("ret = %d\n", ret);
    printf("socket = %d[%d]\n", serv->user_socket[i], i);

    // проверяем успешность вызова
    if (ret == -1) {
        // ошибка
        printf("ERROR, poll checking client socket #%d\n", i);
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
            read_and_write(serv, i);
        }
    }
    printf("------------------------------\n");
}
