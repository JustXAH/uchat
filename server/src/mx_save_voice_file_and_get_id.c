//
// Created by Igor Khanenko on 1/26/21.
//

#include "server.h"

void mx_save_voice_file_and_get_id(t_server *serv, t_json *json,
                                   int user_index) {
    char *send_str = NULL;
    char *unique_voice_name = NULL;
    printf("\n1\n");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                     "USER_ID");
    json->POSITION = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                      "POSITION");
    json->FILENAME = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                      "FILENAME");
    json->VOICE_NAME = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                        "VOICE_NAME");
    json->FILE_SIZE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                        "FILE_SIZE");
    printf("\n2\n");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_VOICE);
    printf("\n3\n");
    json->VOICE_ID = cJSON_CreateNumber(mx_db_insert_new_voice(serv->db,
                                               json->USER_ID->valueint,
                                               json->POSITION->valueint,
                                               json->FILENAME->valuestring,
                                               json->VOICE_NAME->valuestring));
    printf("\n4\n");
    unique_voice_name = mx_db_get_filename(serv->db, json->VOICE_ID->valueint);
    printf("\n5\n");
    if (json->VOICE_ID == 0) {
        // "0" - ошибка при сохранении имени файла в БД и получении уникального ID файла
        json->RESULT = cJSON_CreateFalse();
    } else {
        // аудизапись сохранена успешно и ей присвоен уникальный айди
        json->RESULT = cJSON_CreateTrue();
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "VOICE_ID", json->VOICE_ID);
    send_str = cJSON_Print(json->SEND);
    printf("\n6\n");
    write(serv->user_socket[user_index], send_str, strlen(send_str));

    printf("\n7\n");
    // функция приёма и сохранения аудиофайла
    mx_voice_file_receiver(serv, unique_voice_name, json->FILE_SIZE->valueint, user_index);
    printf("\n8\n");

    cJSON_Delete(json->SEND);
    free(unique_voice_name);
    free(send_str);
}
