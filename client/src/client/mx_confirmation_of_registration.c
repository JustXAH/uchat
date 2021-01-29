//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

extern t_reg_win reg_win;

void mx_confirmation_of_registration(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "RESULT");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "USER_ID");

    if (cJSON_IsFalse(json->RESULT)) { // ошибка при регистрации
        sys->reg_confirmation = false;
        gtk_label_set_text(reg_win.reg_log_label, "Login is already taken");
    }
    else { // RESULT = TRUE (регистрация прошла успешно)
        user->my_id = json->USER_ID->valueint;
        sys->reg_confirmation = true;
        sys->reg_request = false;
        gtk_stack_set_visible_child_name(reg_win.stk, "log_window");

    }
}
