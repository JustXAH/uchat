#include "client.h"

extern t_chat_win chat_win;



void send_msg(GtkButton *btn, GtkBuilder *builder) {
    char *str_msg = (char *)gtk_entry_get_text(chat_win.chat_msg);

    if (strlen(str_msg) > 0) {
        printf("%s\n", str_msg);    
        mb_display_messge(str_msg);
        gtk_entry_set_text(chat_win.chat_msg, "");
    }
}
