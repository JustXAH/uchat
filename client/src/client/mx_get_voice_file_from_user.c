//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_get_voice_file_from_user(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");

    if (cJSON_IsFalse(json->RESULT)) {
        printf("ERROR sending voice file!\n");
    }
    else { // RESULT = TRUE
        user->voices_id[json->POSITION->valueint] = json->VOICE_ID->valueint;
        printf("You have been sent a voice file. Voice file receiving...\n");
        mx_voice_file_receiving(sys);
        printf("Successfully received voice file from USER!\n");

        /*
         * тут должна быть функция воспроизведения войса
         */
        printf("Successfully played voice message!\n");

         // удаление голосового файла и папки cash
        if (remove("client/cache/voice_message") == 0) {
            printf("Successfully removed voice_message from cache directory\n");
        }
        else {
            printf("ERROR while deleting voice message!\n");
        }
        if (rmdir("client/cache") == 0) {
            printf("Successfully removed cache directory\n");
        }
        else {
            printf("ERROR deleting the cache folder!\n");
        }
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
}
