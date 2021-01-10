//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

void mx_struct_initialization(t_client *cli) {
    cli->login = NULL;
    cli->password = NULL;
    cli->sockfd = 0;
    cli->first_reg = true;
    cli->authentication = false;
    cli->registration = false;
    //cli->reg_window = NULL;
}
