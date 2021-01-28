//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_get_voice_file_from_user(t_system *sys, t_user *user, t_json *json) {
    char command[256];
    char *file_path = NULL;
    int status;

    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    json->FILENAME = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "FILENAME");
    json->FILE_SIZE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "FILE_SIZE");


    if (cJSON_IsFalse(json->RESULT)) {
        printf("ERROR sending voice file!\n");
    }
    else { // RESULT = TRUE
//        user->voices_id[json->POSITION->valueint] = json->VOICE_ID->valueint;
        printf("You have been sent a voice file. Voice file receiving...\n");
        file_path = mx_file_receiving(sys, json->FILENAME->valuestring, json->FILE_SIZE->valueint);

        printf("Successfully received and save voice file from USER!\n");

        sprintf(command, "afplay -t 3 %s", file_path);
        status = system(command);

        printf("Successfully played voice message!\n");

         // удаление голосового файла и папки cash
        if (unlink(file_path) == 0) {
            printf("Successfully removed voice_message from cache directory\n");
        }
        else {
            printf("ERROR while deleting voice message!\n");
        }
    }
    free(file_path);
}
