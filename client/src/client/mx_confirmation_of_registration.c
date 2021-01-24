//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

extern t_reg_win reg_win;

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
        sys->reg_confirmation = false;
        write(1, "Such an account already exists\n", 31); // это заглушка
        gtk_label_set_text(reg_win.reg_log_label, "Login is already taken");
    }
    else { // RESULT = TRUE (регистрация прошла успешно)
        user->my_id = json->USER_ID->valueint;
        sys->reg_confirmation = true;
        sys->reg_request = false;
        gtk_stack_set_visible_child_name(reg_win.stk, "loading_log_window");
        mx_registration_or_login_request(sys, user, json);
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "USER_ID");
}
