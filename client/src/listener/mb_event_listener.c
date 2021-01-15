#include "client.h"

extern t_client_st cl_listener;

void mb_event_listener() {
    mb_auth_event_check();
    
}