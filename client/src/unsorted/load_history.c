#include "client.h"

extern t_chat_win chat_win;

void on_edge_reach(GtkScrolledWindow *scrl_win, GtkPositionType pos,
                                                    gpointer user_data) {
    printf("edge reached\n\n\n");

}
