//
// Created by Maksym Tsyfir on 1/28/21.
//
#include "client.h"

extern t_chat_win chat_win;

void playSound( char *filename ) {
    char command[256];
    int status;

    /* create command to execute */
    sprintf( command, "afplay %s", filename );

    /* play sound */
    status = system( command );
}

void on_edit_vax1_play_btn_clicked(GtkButton *btn) {


        /* play the wav file 3 times in a row */
//        playSound( argv[1] );


}
