#include "client.h"

extern t_client_st cl_listener;

gboolean mb_event_listener(gpointer data) {
    mb_auth_event_check();
    mb_incoming_msg_check();
    return true;
}