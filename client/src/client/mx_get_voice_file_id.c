//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_get_voice_file_id(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    json->VOICE_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "VOICE_ID");
    if (cJSON_IsFalse(json->RESULT)) {
        printf("ERROR saving voice file\n");
    }
    else { // RESULT = TRUE
        user->voices_id[sys->position] = json->VOICE_ID->valueint;
        printf("Successfully saved voice file info in DB (POSITION: %d; VOICE_ID: %d)\n",
               sys->position, json->VOICE_ID->valueint);
        // отправка аватарки на сервер
        mx_send_file_to_server(sys, sys->file_path);
        mx_strdel(&sys->file_path);
        mx_strdel(&sys->voice_name);
        printf("Successfully saved voice file to SERVER!\n");

    }
}
