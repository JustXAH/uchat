//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

void mx_login_and_pass_authentication(cJSON *user_JSON, int user_sock) {
    char *send = NULL;
//    cJSON *user = user_JSON;
    cJSON *AUTHENTICATION = mx_database_stub(user_JSON);
//    cJSON *login = cJSON_GetObjectItemCaseSensitive(user, "LOGIN");
//    cJSON *pass = cJSON_GetObjectItemCaseSensitive(user, "PASS");

    send = cJSON_Print(AUTHENTICATION);

    write(user_sock, send, strlen(send));

    cJSON_Delete(AUTHENTICATION);
//    cJSON_Delete(user);
//    printf("LOGIN = %s\n", login->valuestring);
//    printf("PASS = %s\n", pass->valuestring);
//    printf("%s\n", cJSON_Print(user));
}
