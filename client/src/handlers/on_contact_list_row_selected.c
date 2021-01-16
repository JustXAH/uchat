#include "client.h"

extern t_contact_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;

void on_contact_list_row_selected() {
    t_contact_list *con_buff = contact_list;

    while (con_buff) {
        if (gtk_widget_is_focus(con_buff->contact_gui)) {
            cl_listener.user_in_focus = con_buff->user_id;
            mb_display_chat_with_contact(con_buff->user_id);
            return;
        }
        con_buff = con_buff->next_contact;
    }
}
