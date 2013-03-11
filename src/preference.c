/*
 * $Id: preference.c,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $
 * Numakiti Editor for GTK+
 * Copyright (C) Kazuya NUMATA <kaznum@gol.com>
 * This program can be redistributed under GPL.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include "intl.h"

GtkWidget *prefer_dialog;

void prefer_dlg_apply(void) {
  printf(_("Numakiti: Not implemented!\n"));

  return;
}

void preference_dlg(void) {
  GtkWidget *button;
  GtkWidget *bbox;
  GtkWidget *frame;

  prefer_dialog = gtk_dialog_new();
  gtk_window_set_modal(GTK_WINDOW(prefer_dialog), TRUE);
  GTK_WINDOW(prefer_dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title(GTK_WINDOW(prefer_dialog), _("Preference"));
  gtk_window_set_policy(GTK_WINDOW(prefer_dialog), FALSE, FALSE, TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(prefer_dialog), 10);
  gtk_window_position(GTK_WINDOW(prefer_dialog), GTK_WIN_POS_MOUSE);
  gtk_widget_show(prefer_dialog);
  
  frame = gtk_frame_new(_("Not implemented!!"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(prefer_dialog)->vbox), frame , TRUE, TRUE, 2);
  gtk_widget_show(frame);

  bbox = gtk_hbutton_box_new();
  gtk_container_set_border_width(GTK_CONTAINER(bbox), 0);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(prefer_dialog)->action_area), bbox, TRUE, TRUE, 2);
  gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
  gtk_button_box_set_spacing(GTK_BUTTON_BOX(bbox), 10);
  gtk_button_box_set_child_size(GTK_BUTTON_BOX(bbox), 85, 20);
  gtk_widget_show(bbox);
  button = gtk_button_new_with_label(_("OK"));
  gtk_container_add(GTK_CONTAINER(bbox),button);
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(gtk_widget_destroy),
		     GTK_OBJECT(prefer_dialog));
  gtk_widget_show(button);
  GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);

  button = gtk_button_new_with_label(_("Apply"));
  gtk_container_add(GTK_CONTAINER(bbox),button);
  gtk_signal_connect(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(prefer_dlg_apply),
		     NULL);
  gtk_widget_show(button);

  button = gtk_button_new_with_label(_("Close"));
  gtk_container_add(GTK_CONTAINER(bbox),button);
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(gtk_widget_destroy),
		     GTK_OBJECT(prefer_dialog));
  gtk_widget_show(button);

  return;
}




