//
// Created by Maksym Tsyfir on 1/28/21.
//
#include "client.h"

extern t_chat *chat;
extern t_chat_win chat_win;
extern t_message *msg;
extern t_client_st cl_listener;
extern t_chat_list *contact_list;

static void send_voice_file(int i) {
    int con_id = 0;

    t_chat_list *con_buf = contact_list;
    do {
        if (con_buf->chat_id == cl_listener.chat_in_focus)
            con_id = con_buf->user_id;
    } while ((con_buf = con_buf->next_chat));

    mx_send_voice_file_to_user_request(chat->sys, chat->json, chat->user->voices_id[i], con_id);
    printf("Vox %d sended\n", i);

}

void on_Vox_1_activate(GtkButton *btn) {
    send_voice_file(0);
}
void on_Vox_2_activate(GtkButton *btn) {
    send_voice_file(1);
}
void on_Vox_3_activate(GtkButton *btn) {
    send_voice_file(2);
}
void on_Vox_4_activate(GtkButton *btn) {
    send_voice_file(3);
}
void on_Vox_5_activate(GtkButton *btn) {
    send_voice_file(4);
}
void on_Vox_6_activate(GtkButton *btn) {
    send_voice_file(5);
}
void on_Vox_7_activate(GtkButton *btn) {
    send_voice_file(6);
}
void on_Vox_8_activate(GtkButton *btn) {
    send_voice_file(7);
}

//user.voices_name