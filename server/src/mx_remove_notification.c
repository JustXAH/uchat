//
// Created by Dima Voichuck on 1/28/21.
//

#include "server.h"

void mx_remove_notification(t_server *serv, t_json *json) {
    json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "CHAT_ID");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "USER_ID");

    mx_db_clear_notification(serv->db, json->CHAT_ID->valueint, json->USER_ID->valueint);
}
