/* $Id: about.c,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $ 
 *
 * Numakiti Editor for GTK+
 * Copyright (c) Kazuya NUMATA <kaznum@gol.com>
 * This program can be distributed under GPL.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtk.h>
#include "intl.h"
#include "pixmaps/numakiti.xpm"

void about_dlg_cb(void)
{
  GtkWidget *about_dlg;
  GtkWidget *button;
  GtkWidget *label;
  gchar buffer[1024];
  /* Next 4 entry are used pixmap */
  GdkPixmap *logoxpm;
  GdkBitmap *logoxpmmask;
  GtkWidget *pixmap;
  GtkStyle *style;
  GtkWidget *bbox; /* contains OK button */

  about_dlg = gtk_dialog_new();
  gtk_window_set_modal(GTK_WINDOW(about_dlg), TRUE);
  GTK_WINDOW(about_dlg)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title(GTK_WINDOW(about_dlg), _("About"));
  gtk_window_set_policy(GTK_WINDOW(about_dlg), FALSE, FALSE, TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(about_dlg),10);
  gtk_window_position(GTK_WINDOW(about_dlg), GTK_WIN_POS_MOUSE);
  gtk_widget_show(about_dlg);

  gtk_widget_realize(about_dlg);
  style = gtk_widget_get_style(about_dlg);
  logoxpm = gdk_pixmap_create_from_xpm_d(about_dlg->window, &logoxpmmask,
					&style->bg[GTK_STATE_NORMAL],
					(gchar **)numakiti_xpm);
  pixmap = gtk_pixmap_new(logoxpm, logoxpmmask);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dlg)->vbox), pixmap,
		     FALSE, FALSE, 0);
  gtk_widget_show(pixmap);
		     
  label = gtk_label_new(_("Numakiti Editor for GTK+"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dlg)->vbox),label,
		     FALSE,FALSE,10);
  gtk_widget_show(label); 


  g_snprintf(buffer, sizeof(buffer),
	     _("version %s"), VERSION);
  label = gtk_label_new(buffer);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dlg)->vbox),label,
		     FALSE, FALSE, 10);
  gtk_widget_show(label);

  label = gtk_label_new(_("Copyright (C) 2000-2001  Kazuya NUMATA <kaznum@gol.com>"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dlg)->vbox),label,
		     FALSE,FALSE,10);
  gtk_widget_show(label); 

  bbox = gtk_hbutton_box_new();
  gtk_container_set_border_width(GTK_CONTAINER(bbox), 2);
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(about_dlg)->action_area), bbox,
		     TRUE, TRUE, 2);

  gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox), GTK_BUTTONBOX_END);
  gtk_button_box_set_child_size(GTK_BUTTON_BOX(bbox), 85, 20);
  
  gtk_widget_show(bbox);

  button=gtk_button_new_with_label(_("OK"));

  gtk_container_add(GTK_CONTAINER(bbox), button);
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
			    GTK_SIGNAL_FUNC(gtk_widget_destroy),
			    GTK_OBJECT(about_dlg));
  gtk_widget_show(button); 
  GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);

  return;
}












