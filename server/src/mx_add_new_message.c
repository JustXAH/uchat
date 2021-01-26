//
// Created by dima on 12.01.2021.
//

#include "server.h"


void mx_add_new_message(t_server *serv, t_json *json, int user_index) {
    // mx_printstr("mx_add_new_message started\n");
    char *send_str = NULL;
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"USER_ID");
    json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"CHAT_ID");
    json->MESSAGE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"MESSAGE");
 
    json->XYI = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_MESSAGE);

    // mx_printstr("mx_add_new_message 1\n");
    // printf("!: %d %d %s\n", json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring);
    json->MESSAGE_ID = cJSON_CreateNumber(
                        mx_db_create_new_message(serv->db, 
                                                json->USER_ID->valueint, 
                                                json->CHAT_ID->valueint, 
                                                json->MESSAGE->valuestring));
    // printf("w: %d\n",w);
    // json->RESULT = json->MESSAGE_ID->valueint == 0 ? cJSON_CreateFalse() : cJSON_CreateTrue();

    // mx_printstr("mx_add_new_message 2\n");
   

    // mx_printstr("mx_add_new_message 3\n");
    if (json->MESSAGE_ID->valueint == 0) {
        json->RESULT = cJSON_CreateFalse();
    // mx_printstr("mx_add_new_message 4\n");
    }
    else {
    // mx_printstr("mx_add_new_message 5\n");
        json->RESULT = cJSON_CreateTrue();
    }

    cJSON_AddItemToObject(json->XYI, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->XYI, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->XYI, "CHAT_ID", json->CHAT_ID);
    cJSON_AddItemToObject(json->XYI, "MESSAGE", json->MESSAGE);
    cJSON_AddItemToObject(json->XYI, "USER_ID", json->USER_ID);

    // printf("%d\n", cJSON_GetObjectItemCaseSensitive(json->SEND,"USER_ID")->valueint);
    // mx_printstr("mx_add_new_message 6\n");
    send_str = cJSON_Print(json->XYI);
    // write(1, send_str, strlen(send_str));
    write(1, "\nRABOTAET\n", 10);
    // mx_printstr("mx_add_new_message 7\n");
    mx_printstr(send_str);
    mx_printstr(mx_itoa(strlen(send_str)));
    mx_printstr("\n");
    write(serv->user_socket[user_index], send_str, strlen(send_str));
    // mx_printstr("mx_add_new_message ended\n");
     write(1, "\nRABOTAET2\n", 11);
}

