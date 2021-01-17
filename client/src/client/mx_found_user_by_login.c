//
// Created by mac on 15.01.2021.
//

#include "client.h"

void mx_found_user_by_login(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "RESULT");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "USER_ID");

    if (cJSON_IsFalse(json->RESULT)) {
        write (1, "LOGIN DOESN'T EXIST\n", 20); // это затычка!
        // нужно вывести сообщение о ошибке на экран
    }
    else { //RESULT = TRUE (user found successfully)
        sys->found_user_id = json->USER_ID->valueint;

        // дальше нужно сделать запрос на сервер о возвращении профайла найденного юзера,
        // или мы добавим сразу возврат полного профиля юзера при нахождении его по логину
        // это нужно обсудить
        // на экран нужно выводить профиль юзера
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "USER_ID");
}
