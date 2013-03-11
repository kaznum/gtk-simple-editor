/**
 * $Id: callbacks.c,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $
 * Numakiti Editor for GTK.
 * Copyright (c) Kazuya NUMATA.
 * GPL 
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include "intl.h"
#include "main.h"
#include "nkfile.h"
#include "about.h"
#include "callbacks.h"
#include "preference.h"

void nk_open_cb(GtkWidget *widget, NKEdit *doc) {
  open_file_dlg(doc);
  return;
}

void nk_save_cb(GtkWidget *widget, NKEdit *doc) {
  printf("nk_save_cb() not implemented\n");

  return;
}

void nk_save_as_cb(GtkWidget *widget, NKEdit *doc) {
  save_file_dlg(doc);

  return;
}

void nk_print_cb(GtkWidget *widget, NKEdit *doc) {
  printf("nk_print_cb() not implemented\n");
  
  return;
}

void nk_copy_cb(GtkWidget *widget, NKEdit *doc) {
  if(doc->text) {
    gtk_editable_copy_clipboard(GTK_EDITABLE(doc->text));
  }

  return;
}

void nk_paste_cb(GtkWidget *widget, NKEdit *doc) {
  if(doc->text) {
    gtk_editable_paste_clipboard(GTK_EDITABLE(doc->text));
  }

  return;
}

void nk_cut_cb(GtkWidget *widget, NKEdit *doc) {
  if (doc->text) {
    gtk_editable_cut_clipboard(GTK_EDITABLE(doc->text));
  }

  return;
}

void nk_select_all_cb(GtkWidget *widget, NKEdit *doc) {
  if(doc->text) {
    gtk_editable_select_region(GTK_EDITABLE(doc->text),0,-1);
  }

  return;
}

void nk_preference_cb(GtkWidget *widget, gpointer data) {
  preference_dlg();
  return;
}

void nk_about_cb(GtkWidget *widget, gpointer data) {
  about_dlg_cb();
  return;
}

void confir_quit_cb(void) {
  GtkWidget *confir_dlg;
  GtkWidget *button;
  GtkWidget *label;

  confir_dlg=gtk_dialog_new();
  gtk_window_set_modal(GTK_WINDOW(confir_dlg), TRUE);
  GTK_WINDOW(confir_dlg)->type = GTK_WINDOW_DIALOG;
  gtk_window_position(GTK_WINDOW(confir_dlg), GTK_WIN_POS_MOUSE);
  gtk_window_set_title(GTK_WINDOW(confir_dlg), _("Confirmation"));
  gtk_window_set_policy(GTK_WINDOW(confir_dlg), FALSE, FALSE, TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(confir_dlg),10);

  label = gtk_label_new(_("The document is not saved. Are you really quit?"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(confir_dlg)->vbox),label,
		     FALSE, FALSE, 10);
  gtk_widget_show(label);

  button = gtk_button_new_with_label(_("OK"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(confir_dlg)->action_area),button,
		     TRUE, TRUE, 2);
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
  gtk_widget_show(button);

  button = gtk_button_new_with_label(_("Cancel"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(confir_dlg)->action_area),button,
		     TRUE, TRUE, 2);
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(gtk_widget_destroy),
		     GTK_OBJECT(confir_dlg));
  gtk_widget_show(button);
  GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);

  gtk_widget_show(confir_dlg);

  return;
}

void nk_quit_cb(GtkWidget *widget, NKEdit *doc) {
  if (doc->changed) {
    confir_quit_cb();
  } else {
    gtk_main_quit();
  }

  return;
}

void nk_text_clean(GtkWidget *widget, NKEdit *doc) {
  gtk_widget_realize(doc->text);
  gtk_text_freeze(GTK_TEXT(doc->text));
  gtk_text_set_point(GTK_TEXT(doc->text), 0);
  /*
   *  gtk_text_forward_delete(GTK_TEXT(doc->text), -1);
   */
  gtk_text_forward_delete(GTK_TEXT(doc->text), 
  			    gtk_text_get_length(GTK_TEXT(doc->text)));

  gtk_text_thaw(GTK_TEXT(doc->text));

  return;
}

void nk_new_cb(GtkWidget *widget, NKEdit *doc) {
  if(doc->changed) {
    confir_save_dlg(doc, FROM_NEW_CB);
    return;
  }
  nk_text_clean(widget, doc);
  g_snprintf(doc->filename, sizeof(doc->filename),"");

  check_write_mode(doc, TRUE);

  return;
}

void nk_text_check_changed(NKEdit *doc, gboolean changed) {
  if(doc->w_mode) {
    doc->changed = changed;
    if(changed) {
      gtk_statusbar_push(GTK_STATUSBAR(doc->status_bar),
			 doc->statusbar_context_id,
			 _("Changed"));
    } else {
      gtk_statusbar_push(GTK_STATUSBAR(doc->status_bar),
			 doc->statusbar_context_id,
			 _("Not Changed"));
    }
  } else {
    doc->changed = FALSE;
    gtk_statusbar_push(GTK_STATUSBAR(doc->status_bar),
		       doc->statusbar_context_id,
		       _("ReadOnly"));
  }
  
  return;
}

void check_write_mode(NKEdit *doc, gboolean mode) {
  /* if mode is unsure then put TRUE!! */
  struct stat st;

  if(stat(doc->filename, &st) == -1) {
    doc->w_mode = mode;
  } else {
    doc->w_mode = ((st.st_mode & S_IWUSR) && mode);
  }
  
  gtk_editable_set_editable(GTK_EDITABLE(doc->text), doc->w_mode);
  nk_text_check_changed(doc, FALSE);

  return;
}


void nk_text_changed_cb(GtkWidget *widget, NKEdit *doc) {
  if (doc->changed) return;

  nk_text_check_changed(doc, TRUE);
  
  return;
}
