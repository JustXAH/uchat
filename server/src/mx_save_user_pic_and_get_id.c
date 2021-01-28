//
// Created by Igor Khanenko on 1/28/21.
//
#include "server.h"

void mx_save_user_pic_and_get_id(t_server *serv, t_json *json,
                                   int user_index) {
    char *send_str = NULL;
    char *unique_user_pic_name = NULL;

    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                     "USER_ID");
    json->FILENAME = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                      "FILENAME");
        json->FILE_SIZE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                      "FILE_SIZE");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_USER_PIC);

    json->USER_PIC_ID = cJSON_CreateNumber(
            mx_db_set_user_picture(serv->db, json->USER_ID->valueint,
                                   json->FILENAME->valuestring));

    unique_user_pic_name = mx_db_get_filename(serv->db,
                                              json->USER_PIC_ID->valueint);
    if (json->USER_PIC_ID == 0) {
        // "0" - ошибка при сохранении имени файла в БД и получении уникального ID файла
        json->RESULT = cJSON_CreateFalse();
    } else {
        // аватарка сохранена успешно и ей присвоен уникальный айди
        json->RESULT = cJSON_CreateTrue();
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "USER_PIC_ID", json->USER_PIC_ID);

    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    // функция приёма и сохранения аватарки
    mx_user_pic_receiver(serv, unique_user_pic_name, json->FILE_SIZE->valueint, user_index);

    cJSON_Delete(json->SEND);
    free(unique_user_pic_name);
    free(send_str);
}
