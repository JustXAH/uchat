//
// Created by mac on 19.01.2021.
//

#include "server.h"

void mx_json_struct_initialization(t_json *json) {
    json->USER_JSON = NULL;
    json->USER_ID = NULL;
    json->FOUND_USERNAMES = NULL;
    json->FOUND_LOGIN = NULL;
    json->LOGIN = NULL;
    json->PASS = NULL;
    json->TYPE = NULL;
    json->SEND = NULL;
    json->CONTACT_ID = NULL;
    json->CONTACTS_COUNT = NULL;
    json->CONTACTS_LOGIN_ARR = NULL;
    json->CONTACTS_ID_ARR = NULL;
    json->CHATS_COUNT = NULL;
    json->CHATS_NAME_ARR = NULL;
    json->CHATS_ID_ARR = NULL;
    json->RESULT = NULL;
    json->CHAT_ID = NULL;
    json->COUNT_MESSAGES_ARR = NULL;
    json->MESSAGE = NULL;
    json->MESSAGES_TIME = NULL;
    json->MESSAGES_ARR = NULL;
    json->MESSAGES_ID = NULL;
    json->FILENAME = NULL;
    json->VOICE_ID = NULL;
    json->POSITION = NULL;
}
