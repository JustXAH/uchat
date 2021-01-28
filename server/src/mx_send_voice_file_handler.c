//
// Created by Igor Khanenko on 1/27/21.
//

#include "server.h"

static int checking_contact_status_and_taking_socket(t_server *serv,
                                                     t_json *json) {
    int socket = 0;

    for (int i = 0; i != serv->cli_connect; i++) {
        if (serv->users_id[i] == json->CONTACT_ID->valueint) {
           socket = serv->user_socket[i];
        }
    }
    return socket;
}

void mx_send_voice_file_handler(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;
    char *filename = NULL;
    int to_whom_socket = 0;

    json->VOICE_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "VOICE_ID");
    json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "CONTACT_ID");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(SEND_VOICE_TO_USER);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);

    to_whom_socket = checking_contact_status_and_taking_socket(serv, json);

    if (to_whom_socket == 0) { // user is offline and we can't send voice file
        json->RESULT = cJSON_CreateFalse();
        cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
        send_str = cJSON_Print(json->SEND);
        write(serv->user_socket[user_index], send_str, strlen(send_str));
    }
    else {
        filename = mx_db_get_filename(serv->db, json->VOICE_ID->valueint);

        json->RESULT = cJSON_CreateTrue();
        json->FILENAME = cJSON_CreateString(filename);

        cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
        cJSON_AddItemToObject(json->SEND, "FILENAME", json->FILENAME);

        send_str = cJSON_Print(json->SEND);
        write(to_whom_socket, send_str, strlen(send_str));

        // функция отправки голосового файла юзеру
        mx_send_voice_file_to_user(filename, to_whom_socket);
    }
    cJSON_Delete(json->SEND);
    free(send_str);
}
