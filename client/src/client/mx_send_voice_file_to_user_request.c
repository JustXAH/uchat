//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_send_voice_file_to_user_request(t_system *sys, t_json *json,
                                        int voice_id, int contact_id) {
    char *str_user = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(SEND_VOICE_TO_USER);
    json->VOICE_ID = cJSON_CreateNumber(voice_id);
    json->CONTACT_ID = cJSON_CreateNumber(contact_id);

    printf("\nVOICE_ID: |%d|\n", voice_id);
    printf("\nCONTACT_ID: |%d|\n", contact_id);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "VOICE_ID", json->VOICE_ID);
    cJSON_AddItemToObject(json->SEND, "CONTACT_ID", json->CONTACT_ID);

    str_user = cJSON_Print(json->SEND);

    write(sys->sockfd, str_user, strlen(str_user));

    printf("Successfully sent JSON with request to send voice file to USER!\n");

    cJSON_Delete(json->SEND);
    free(str_user);
}
