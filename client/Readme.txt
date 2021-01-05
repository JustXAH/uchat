Компилить все из папки сорс с флагами
clang client.c login_btn_clicked_cb.c mx_gtk_window.c mx_struct_initialization.c -rdynamic `pkg-config --cflags --libs gtk+-3.0`
