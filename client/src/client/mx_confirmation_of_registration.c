//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

//static void registration_request(t_system *sys, t_user *user) {
//    char *str_user_json;
//
//    sys->registration = false;
//
//    if (malloc_size(user->login)) {
//        free(user->login);
//    }
//    if (malloc_size(user->password)) {
//        free(user->password);
//    }
//    str_user_json = mx_create_user_profile(sys, user);
//    write(sys->sockfd, str_user_json, strlen(str_user_json));
//    free(str_user_json);
//}

void mx_confirmation_of_registration(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "RESULT");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "USER_ID");

    if (cJSON_IsFalse(json->RESULT)) { // ошибка при регистрации
        sys->registration = false;
        write(1, "Such an account already exists\n", 31); // это заглушка
        //нужно вывести ошибку на экран и запустить повторную регистрацию
        
    }
    else { // RESULT = TRUE (регистрация прошла успешно)
       // вывести сообщение о успешной регистрации и кнопку для перехода на окно ЛОГИНА
        user->my_id = json->USER_ID->valueint;
        sys->registration = true;
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "USER_ID");
}
