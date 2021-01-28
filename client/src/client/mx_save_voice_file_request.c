//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_save_voice_file_request(t_system *sys, t_user *user, t_json *json) {
    char *str_user = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_VOICE);
    json->USER_ID = cJSON_CreateNumber(user->my_id);
    json->POSITION = cJSON_CreateNumber(sys->position);
    json->FILENAME = cJSON_CreateString(sys->filename);
    json->VOICE_NAME = cJSON_CreateString(sys->voice_name);
    json->FILE_SIZE = cJSON_CreateNumber(mx_file_size_measurement(sys->file_path));

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "USER_ID", json->USER_ID);
    cJSON_AddItemToObject(json->SEND, "POSITION", json->POSITION);
    cJSON_AddItemToObject(json->SEND, "FILENAME", json->FILENAME);
    cJSON_AddItemToObject(json->SEND, "VOICE_NAME", json->VOICE_NAME);
    cJSON_AddItemToObject(json->SEND, "FILE_SIZE", json->FILE_SIZE);

    str_user = cJSON_Print(json->SEND);

    write(sys->sockfd, str_user, strlen(str_user));

    printf("Successfully sent JSON with request to save voice file!\n");

    cJSON_Delete(json->SEND);
    free(str_user);
}
