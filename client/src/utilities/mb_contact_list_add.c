#include "client.h"

extern t_chat_win chat_win;
extern t_contact_list *contact_list;

static void mb_display_new_contact(t_contact_list *new_cont) {
    GtkTextBuffer *buffer;

    new_cont->contact_gui = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(new_cont->contact_gui));
    gtk_text_buffer_set_text (buffer, new_cont->user_name, -1);

    gtk_container_add(GTK_CONTAINER(chat_win.contact_list), new_cont->contact_gui);
    gtk_widget_show(new_cont->contact_gui);  
}
void mb_contact_list_add(int user_id, char *user_name) {
    if (contact_list == NULL) {
        contact_list = (t_contact_list *)malloc(sizeof(t_contact_list));
        contact_list->next_contact = NULL;
    } else {
        t_contact_list *temp;

        temp = (t_contact_list *)malloc(sizeof(t_contact_list));
        temp->next_contact = contact_list;
        contact_list = temp;
    }
    contact_list->user_id = user_id;
    contact_list->user_name = user_name;
    contact_list->chat_history = NULL;
    mb_display_new_contact(contact_list);
}
