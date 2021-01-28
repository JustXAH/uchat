//
// Created by Igor Khanenko on 1/25/21.
//

#include "server.h"

void mx_sorting_users_and_sockets(t_server *serv) {
    int *tmp_sockets_arr = serv->user_socket;
    int *tmp_id_arr = serv->users_id;
    time_t *tmp_lst_arr = serv->last_voice_send;
    int socket;
    int id;
    time_t lst;

    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < MAX_USERS - i - 1; j++) {
            if (tmp_sockets_arr[j] < tmp_sockets_arr[j + 1]) {
                socket = tmp_sockets_arr[j + 1];
                id = tmp_id_arr[j + 1];
                lst = tmp_lst_arr[j + 1];
                tmp_sockets_arr[j + 1] = tmp_sockets_arr[j];
                tmp_id_arr[j + 1] = tmp_id_arr[j];
                tmp_lst_arr[j + 1] = tmp_lst_arr[j];
                tmp_sockets_arr[j] = socket;
                tmp_id_arr[j] = id;
                tmp_lst_arr[j] = lst;
            }
        }
    }
    serv->user_socket = tmp_sockets_arr;
    serv->users_id = tmp_id_arr;
    serv->last_voice_send = tmp_lst_arr;
}
