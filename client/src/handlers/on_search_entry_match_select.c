#include "client.h"

extern t_chat_win chat_win;

gboolean on_search_entry_match_select(GtkEntryCompletion *widget,
                                        GtkTreeModel       *model,
                                        GtkTreeIter        *iter,
                                        gpointer            user_data) {
    printf("match selected\n");
    return false;
}