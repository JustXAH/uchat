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
    mx_send_voice_file_to_user_request(chat->sys, chat->json, chat->user->voices_id[0], cl_listener.user_in_focus);
    printf("Vox 1 sended");
}

//user.voices_name
