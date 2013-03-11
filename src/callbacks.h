/*
 * $Id: callbacks.h,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $
 * Numakiti Editor for GTK+
 * Copyright (c) Kazuya NUMATA
 * GPL.
 */

#define FROM_NEW_CB 0
#define FROM_OPEN_FILE_DLG 1

/*
 * callbacks for MenuList
 */
void nk_new_cb(GtkWidget *widget, NKEdit *doc);
void nk_open_cb(GtkWidget *widget, NKEdit *doc);
void nk_save_cb(GtkWidget *widget, NKEdit *doc);
void nk_save_as_cb(GtkWidget *widget, NKEdit *doc);
void nk_print_cb(GtkWidget *widget, NKEdit *doc);
void nk_quit_cb(GtkWidget *widget, NKEdit *doc);

void nk_copy_cb(GtkWidget *widget, NKEdit *doc);
void nk_paste_cb(GtkWidget *widget, NKEdit *doc);
void nk_cut_cb(GtkWidget *widget, NKEdit *doc);
void nk_select_all_cb(GtkWidget *widget, NKEdit *doc);
void nk_preference_cb(GtkWidget *widget, gpointer data);
void nk_about_cb(GtkWidget *widget, gpointer data);

/*
 * Useful callback
 */
void check_write_mode(NKEdit *doc, gboolean mode);
void nk_text_clean(GtkWidget *widget, NKEdit *doc);
void nk_text_changed_cb(GtkWidget *widget, NKEdit *doc);
void nk_text_check_changed(NKEdit *data, gboolean mode);

