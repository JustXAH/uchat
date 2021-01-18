#include "client.h"
extern t_contact_list *contact_list;
extern t_chat_win chat_win;
//----------------------------------------------------------------------------//
static void mb_load_chat_history(t_message *history);
static void mb_form_msg_str(t_message *history);
static void mb_clear_chat_viewer();
///////////////////////////////////////////////////////////////////////////////
void mb_display_chat_with_contact(int user_id) {
    t_contact_list *temp = contact_list;

    if (temp && user_id != 0) {
        do {
            if (temp->user_id == user_id) {
                if(temp->chat_history)
                    printf("chat history exists\n");
                mb_load_chat_history(temp->chat_history);
                return;
            }
        } while ((temp = temp->next_contact));  
    }  
}///////////////////////////////////////////////////////////////////////////////
static void mb_load_chat_history(t_message *history) {
    mb_clear_chat_viewer();
    while (history) {
        printf("%s\n",history->text);
        mb_display_msg(history);
        history = history->next;
    }
}
static void mb_form_msg_str(t_message *history) {
    printf("pishov v zhopu\n");
}
static void mb_clear_chat_viewer() {
    GtkListBoxRow *temp = gtk_list_box_get_row_at_index(chat_win.chat_viewer,0);
    while (temp) {
        gtk_widget_destroy(GTK_WIDGET(temp));
        temp = gtk_list_box_get_row_at_index(chat_win.chat_viewer,0);
    }
}
