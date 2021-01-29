#include "client.h"

extern t_client_st cl_listener;

gboolean mb_event_listener(gpointer data) {
    //printf("fsearch = %d\n", cl_listener.fsearch);
    mb_auth_event_check();
    mb_incoming_msg_check();
   // mb_new_contact_check();
    return true;
}