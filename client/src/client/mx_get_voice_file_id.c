//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_get_voice_file_id(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    json->VOICE_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "VOICE_ID");
    json->POSITION = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "POSITION");

    if (cJSON_IsFalse(json->RESULT)) {
        printf("ERROR saving voice file\n");
    }
    else { // RESULT = TRUE
        user->voices_id[json->POSITION->valueint] = json->VOICE_ID->valueint;
        printf("Successfully saved voice file info in DB (POSITION: %d; VOICE_ID: %d)\n",
               json->POSITION->valueint, json->VOICE_ID->valueint);
        mx_send_voice_file_to_server(sys, sys->file_path);
        printf("Successfully saved voice file in SERVER!\n");
    }
}
