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
    mx_send_voice_file_to_user_request(chat->sys, chat->json, chat->user->voices_id[i], cl_listener.user_in_focus);
    printf("Vox %d sent\n", i);
}

void on_Vox_1_clicked(GtkButton *btn) {
    send_voice_file(0);
}
void on_Vox_2_clicked(GtkButton *btn) {
    send_voice_file(1);
}
void on_Vox_3_clicked(GtkButton *btn) {
    send_voice_file(2);
}
void on_Vox_4_clicked(GtkButton *btn) {
    send_voice_file(3);
}
void on_Vox_5_clicked(GtkButton *btn) {
    send_voice_file(4);
}
void on_Vox_6_clicked(GtkButton *btn) {
    send_voice_file(5);
}
void on_Vox_7_clicked(GtkButton *btn) {
    send_voice_file(6);
}
void on_Vox_8_clicked(GtkButton *btn) {
    send_voice_file(7);
}

//user.voices_name
