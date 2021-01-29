//
// Created by mac on 09.01.2021.
//

#include "server.h"

void mx_user_search_by_login(t_server *serv, t_json *json, int user_index) {
    t_user_info *user = NULL;
    char *send_str = NULL;
    char *filename = NULL;
    char *file_path = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_LOGIN);
    json->SEARCHED_LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,
                                                            "SEARCHED_LOGIN");
    json->FOUND_USER_ID = cJSON_CreateNumber(mx_db_check_login_exist(serv->db,
                                                                     json->SEARCHED_LOGIN->valuestring));

    if (json->FOUND_USER_ID->valueint == 0) { // "0" - login doesn't exist
        json->RESULT = cJSON_CreateFalse();
    }
    else {  // юзер найден успешно
        user = mx_db_get_user(serv->db, json->FOUND_USER_ID->valueint);
        json->RESULT = cJSON_CreateTrue();
        json->FOUND_LOGIN = cJSON_CreateString(user->login);

        cJSON_AddItemToObject(json->SEND, "FOUND_USER_ID",
                              json->FOUND_USER_ID);
        cJSON_AddItemToObject(json->SEND, "FOUND_LOGIN", json->FOUND_LOGIN);
        if (user->photo_file_id != 0) {
            filename = mx_db_get_filename(serv->db, user->photo_file_id);
            file_path = mx_get_file_path("server/media/users_pic/", filename);

            json->FILENAME = cJSON_CreateString(filename);
            json->FILE_SIZE = cJSON_CreateNumber(mx_file_size_measurement(file_path));
            json->DISPATCH = cJSON_CreateTrue();

            cJSON_AddItemToObject(json->SEND, "FILENAME", json->FILENAME);
            cJSON_AddItemToObject(json->SEND, "FILE_SIZE", json->FILE_SIZE);
        } else {
            json->DISPATCH = cJSON_CreateFalse();
        }
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "DISPATCH", json->DISPATCH);

    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));


    if (cJSON_IsTrue(json->DISPATCH)) {
        // функция отправки аватарки на клиент для просмотра профайла
        mx_send_user_pic_to_user(file_path, serv->user_socket[user_index]);
    }

    cJSON_Delete(json->SEND);
    free(filename);
    free(file_path);
    free(send_str);
}
