//
// Created by Igor Khanenko on 1/28/21.
//

#include "client.h"

void mx_get_user_pic_id(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    json->USER_PIC_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "USER_PIC_ID");

    if (cJSON_IsFalse(json->RESULT)) {
        printf("ERROR saving user pic\n");
    }
    else { // RESULT = TRUE
        user->user_pic_id = json->USER_PIC_ID->valueint;
        printf("Successfully saved user pic info to DB (USER_PIC ID: %d)\n",
               json->USER_PIC_ID->valueint);
        //отправка аватарки на сервер

        mx_send_file_to_server(sys, sys->file_path);
        mx_strdel(&sys->file_path);
//        mx_strdel(&sys->filename);
        printf("Successfully saved user pic to SERVER!\n");
    }
}
