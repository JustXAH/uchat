#include "client.h"

t_reg_win reg_win;
t_chat_win chat_win;
t_client_st cl_listener;
t_message *incoming_msg_buffer;
t_chat_list *contact_list;
t_chat_list *chat_list;
t_message *chat_history;

void reg_win_init(t_system *sys) {
    reg_win.log_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "log_login_field"));
    reg_win.pass_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "log_pass_field"));
    reg_win.err_log_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "log_login_lable"));
    reg_win.err_pas_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "log_pass_lable"));
    reg_win.stk = GTK_STACK(gtk_builder_get_object(sys->builder,
                                                        "autoriz_stack"));
    reg_win.reg_log = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_login_field"));
    reg_win.reg_pass1 = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_field"));
    reg_win.reg_pass2 = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_check_field"));
    reg_win.reg_email = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_email_field"));
    reg_win.reg_log_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_login_lable"));
    reg_win.reg_pas_label1 = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_lable"));
    reg_win.reg_pas_label2 = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_conf_lable"));
    reg_win.reg_email_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_email_lable"));
}
void chat_win_init(t_system *sys) {
    chat_win.msg_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "chat_msg_entry"));
    chat_win.msg_viewer = GTK_LIST_BOX(gtk_builder_get_object(sys->builder,
                                                        "chat_msg_lst_box"));    
    chat_win.contacts_list = GTK_LIST_BOX(gtk_builder_get_object(sys->builder,
                                                        "contact_list"));
    chat_win.chats_list = GTK_LIST_BOX(gtk_builder_get_object(sys->builder,
                                                        "chat_list"));
    chat_win.search_list = GTK_LIST_BOX(gtk_builder_get_object(sys->builder,
                                                        "search_list"));                                                     
    chat_win.switcher = GTK_STACK_SWITCHER(gtk_builder_get_object(sys->builder,
                                                        "chat_switcher"));
    chat_win.msg_box = GTK_BOX(gtk_builder_get_object(sys->builder,
                                                        "msg_box"));
    chat_win.search_stack = GTK_STACK(gtk_builder_get_object(sys->builder,
                                                        "search_stk"));
    chat_win.all_stack = GTK_STACK(gtk_builder_get_object(sys->builder,
                                                        "msg_config_stk"));
    chat_win.my_profile_box = GTK_FIXED(gtk_builder_get_object(sys->builder,
                                                        "profile_fixed"));
     chat_win.u_profile_box = GTK_FIXED(gtk_builder_get_object(sys->builder,
                                                        "add_ban_profile"));
    chat_win.edit_vax_box = GTK_BOX(gtk_builder_get_object(sys->builder,
                                                              "edit_vax"));
    chat_win.edit_profile = GTK_FIXED(gtk_builder_get_object(sys->builder,
                                                              "edit_profile"));
    chat_win.Vox_1 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_1"));
    chat_win.Vox_2 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_2"));
    chat_win.Vox_3 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_3"));
    chat_win.Vox_4 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_4"));
    chat_win.Vox_5 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_5"));
    chat_win.Vox_6 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_6"));
    chat_win.Vox_7 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_7"));
    chat_win.Vox_8 = GTK_BUTTON(gtk_builder_get_object(sys->builder, "Vox_8"));
    //Search                                                    
    chat_win.fsearch_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "friends_search_entry"));
    chat_win.csearch_entry = GTK_SEARCH_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "chat_search_entry"));
    chat_win.edit_vax1_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                     "edit_vax1_entry"));
    chat_win.edit_vax2_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                     "edit_vax2_entry"));
    chat_win.edit_vax3_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                       "edit_vax3_entry"));
    chat_win.edit_vax4_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                       "edit_vax4_entry"));
    chat_win.edit_vax5_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                       "edit_vax5_entry"));
    chat_win.edit_vax6_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                       "edit_vax6_entry"));
    chat_win.edit_vax7_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                       "edit_vax7_entry"));
    chat_win.edit_vax8_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                                       "edit_vax8_entry"));
    chat_win.profile_login = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                           "profile_login"));
    chat_win.err_msg_lbl = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                           "err_msg_lbl"));
    chat_win.err_pop = GTK_DIALOG(gtk_builder_get_object(sys->builder,
                                                           "err_pop"));
    chat_win.msg_entry_stk = GTK_STACK(gtk_builder_get_object(sys->builder,
                                                        "msg_entry_stk"));
    chat_win.msg_entry_box = GTK_BOX(gtk_builder_get_object(sys->builder,
                                                              "msg_entry_box"));
    chat_win.vox_entry_box = GTK_BOX(gtk_builder_get_object(sys->builder,
                                                              "vox_entry_box"));

    chat_win.fresults = NULL;

    chat_win.add_remove_stk = GTK_STACK(gtk_builder_get_object(sys->builder,
                                                              "add_remove_stk"));
    chat_win.add_user = GTK_BUTTON(gtk_builder_get_object(sys->builder,
                                                              "add_user"));
    chat_win.remove_user = GTK_BUTTON(gtk_builder_get_object(sys->builder,
                                                              "remove_user"));

    /*
    chat_win.s_comp = gtk_entry_completion_new ();
    gtk_entry_set_completion (GTK_ENTRY (chat_win.search_entry), chat_win.s_comp);  
    chat_win.s_comp_model = GTK_TREE_MODEL(gtk_list_store_new(1, G_TYPE_STRING));
    gtk_entry_completion_set_model (chat_win.s_comp, chat_win.s_comp_model);
    gtk_entry_completion_set_text_column (chat_win.s_comp, 0);
    g_signal_connect(G_OBJECT(chat_win.s_comp),"match-selected", G_CALLBACK(on_search_entry_match_select), NULL);
    */
    chat_win.welcome_user = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "welcome_user"));
    chat_win.friend_login = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "friend_login"));
    chat_win.file_choose_window = GTK_WIDGET(gtk_builder_get_object(sys->builder,
                                                           "file_choose"));
    chat_win.scrl_chat_box = GTK_SCROLLED_WINDOW(gtk_builder_get_object(sys->builder,
                                                           "chat_msg_scrld"));
    chat_win.edit_avatar_img = GTK_IMAGE(gtk_builder_get_object(sys->builder,
                                                                      "edit_avatar_img"));
    chat_win.profile_avatar_img = GTK_IMAGE(gtk_builder_get_object(sys->builder,
                                                                      "profile_avatar_img"));
}
void mb_client_globals_initialization() {
    cl_listener.logged_in = 0;
    cl_listener.authentication = 0;
    
    cl_listener.message_in_buffer = false;
    cl_listener.chat_in_focus = 0;

    cl_listener.fsearch = false;
    cl_listener.dont_bother_search = false;

    cl_listener.new_contact_received = false;

    cl_listener.vox_not_msg = false;

    cl_listener.requested_user_name = NULL;

    cl_listener.just_added_new_friend = 0;

    cl_listener.pending_requests = (bool *)malloc(HISTORY_CHAT + 1);
    for (int i = 0; i <= HISTORY_CHAT; i++)
        cl_listener.pending_requests[i] = false;
    
    incoming_msg_buffer = NULL;
    chat_history = NULL;
    contact_list = NULL;
    chat_list = NULL;
    
}
