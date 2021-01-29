#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;

static void mb_display_new_contact(t_chat_list *new_cont) {
    GtkStyleContext *context_contact;

    new_cont->contact_gui = gtk_label_new((const gchar *)new_cont->user_name);
    context_contact = gtk_widget_get_style_context(new_cont->contact_gui);

   if (new_cont->is_online)
       gtk_style_context_add_class(context_contact, "cont_list_online");
   else
       gtk_style_context_add_class(context_contact, "cont_list_ofline");

    //gtk_style_context_add_class(context_contact, "cont_list_ofline");

    gtk_container_add(GTK_CONTAINER(chat_win.contacts_list), new_cont->contact_gui);
    gtk_widget_show(new_cont->contact_gui);
}
void mb_contact_list_add(int user_id, char *user_name, bool is_online) {
    //mx_printstr("mb_contact_list_add started\n");
    if (contact_list == NULL) {
        contact_list = (t_chat_list *)malloc(sizeof(t_chat_list));
        contact_list->next_chat = NULL;
    } else {
        t_chat_list *temp;

        temp = (t_chat_list *)malloc(sizeof(t_chat_list));
        temp->next_chat = contact_list;
        contact_list = temp;
    }
    contact_list->user_amount = 1;
    contact_list->user_id = user_id;
    contact_list->user_name = mx_strdup(user_name);
    contact_list->is_online = is_online;
    mb_display_new_contact(contact_list);
    //mx_printstr("mb_contact_list_add finished successfully\n");
}
