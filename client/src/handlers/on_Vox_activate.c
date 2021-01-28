//
// Created by Maksym Tsyfir on 1/28/21.
//
#include "client.h"

extern t_chat *chat;
extern t_chat_win chat_win;
extern t_message *msg;
extern t_client_st cl_listener;
extern t_chat_list *contact_list;

void on_Vox_1_activate(GtkButton *btn) {
    int con_id = 0;

    t_chat_list *con_buf = contact_list;
    do {
        if (con_buf->chat_id == cl_listener.chat_in_focus)
            con_id = con_buf->user_id;
    } while ((con_buf = con_buf->next_chat));

    mx_send_voice_file_to_user_request(chat->sys, chat->json, chat->user->voices_id[0], con_id);
    printf("Vox 1 sended");
}

//user.voices_name