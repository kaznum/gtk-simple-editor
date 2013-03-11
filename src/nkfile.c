/*
 * $Id: nkfile.c,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $
 *
 * Numakiti Editor for GTK
 * Copyright (c) Kazuya NUMATA <kaznum@gol.com>
 * This program can be redistributed under GPL.
 *
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h> /* needed for realpath() */
#include <string.h>
#include "main.h"
#include "nkfile.h"
#include "intl.h"
#include "callbacks.h"

GtkWidget *file_dlg;

/* 
 * Path name conversion.
 */

char *force_realpath(char *check_path, char *full_path, char *path)
{
  char resolved_path[PATH_MAX];
  char opath[PATH_MAX];
  char *op, *bp;
  char *p;

  strcpy(opath, check_path);
  bp = strrchr(opath, '/'); // refer to man strrchr
  if (bp == NULL) {
    op = ".";
    bp = opath;
  } else {
    *bp++ = '\0';
    op = opath;
  }
  p = realpath(op, resolved_path);
  if(!p)
    return NULL;

  g_snprintf(full_path, PATH_MAX, "%s/%s", p, bp);
  g_snprintf(path, PATH_MAX, "%s", p);

  return full_path;
}


void nk_load_file(NKEdit *doc, gchar *filename)
{
  FILE *infile;
  gchar buffer[READ_BUFFER_SIZE];
  gint nchars;

#ifdef NK_DEBUG
#  printf("nk_load_file\n");
#endif

  if((infile = fopen(filename, "r")) == NULL) {
    fclose(infile);
    return;
  }
  nk_text_clean(NULL, doc);

  gtk_widget_realize(doc->text);
  gtk_text_freeze(GTK_TEXT(doc->text));

  while (1) {
    nchars = fread(buffer, 1, READ_BUFFER_SIZE, infile);
    gtk_text_insert(GTK_TEXT(doc->text), NULL, NULL, NULL, buffer, nchars);

    if (nchars < READ_BUFFER_SIZE) break;
  }
  fclose(infile);

  gtk_text_set_point(GTK_TEXT(doc->text), 0);

  gtk_text_thaw(GTK_TEXT(doc->text));
  g_snprintf(doc->filename, sizeof(doc->filename),filename);

  check_write_mode(doc, TRUE);

  return;
}

void nk_save_file(NKEdit * data, gchar *filename)
{
  printf("filename is %s\n" "nk_save_file",filename);

  g_snprintf(data->filename, sizeof(data->filename),"%s", filename);

  check_write_mode(data, TRUE);
  gtk_widget_destroy(file_dlg);

  return;
}

void open_dlg_ok(GtkWidget *widget, NKEdit *doc)
{
  gchar filename[PATH_MAX];
  g_snprintf(filename, sizeof(filename), "%s",
	     gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_dlg)));

  if (filename) {
    nk_load_file(doc, filename);
  }
  gtk_widget_destroy(file_dlg);

  return;
}

void save_dlg_ok(GtkWidget *widget, NKEdit *doc)
{
  gchar filename[PATH_MAX];
  g_snprintf(filename, sizeof(filename), "%s",
	     gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_dlg)));

  if(filename) {
    nk_save_file(doc, filename);
  }

  return;
}

void confir_save_yes(GtkWidget *widget, NKEdit *doc)
{
  gtk_widget_destroy(file_dlg);
  save_file_dlg(doc);

  return;
}

void confir_save_no_from_open_file_dlg(GtkWidget *widget, NKEdit *doc)
{
  gtk_widget_destroy(file_dlg);
  nk_text_check_changed(doc, FALSE);
  open_file_dlg(doc);

  return;
}

void confir_save_no_from_new_cb(GtkWidget *widget, NKEdit *doc)
{
  gtk_widget_destroy(file_dlg);
  nk_text_check_changed(doc, FALSE);
  nk_new_cb(widget, doc);

  return;
}

void confir_save_dlg(NKEdit *doc, gint from)
{
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *button;

  file_dlg = gtk_dialog_new();
  dialog = file_dlg;
  gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
  GTK_WINDOW(dialog)->type = GTK_WINDOW_DIALOG;
  gtk_window_set_title(GTK_WINDOW(dialog), _("Confirmation"));
  gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(dialog),10);

  label = gtk_label_new(_("The document is not saved. Do you save it?"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, FALSE, FALSE,
		     10);
  gtk_widget_show(label);

  button = gtk_button_new_with_label(_("Yes"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),button,
                     TRUE, TRUE, 2);
  gtk_signal_connect(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(confir_save_yes), doc);

  gtk_widget_show(button);
  GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);

  button = gtk_button_new_with_label(_("No"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),button,
                     TRUE, TRUE, 2);
  if (from == FROM_OPEN_FILE_DLG) {
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
		       GTK_SIGNAL_FUNC(confir_save_no_from_open_file_dlg), doc);
  } else if (from == FROM_NEW_CB) {
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
		       GTK_SIGNAL_FUNC(confir_save_no_from_new_cb), doc);
  }
  gtk_widget_show(button);

  button = gtk_button_new_with_label(_("Cancel"));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button,
		     TRUE, TRUE, 2);
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(dialog));
  gtk_widget_show(button);

  gtk_widget_show(dialog);

  return;
}

void open_file_dlg(NKEdit *doc)
{

  if (doc->changed) {
    confir_save_dlg(doc, FROM_OPEN_FILE_DLG);
    return;
  }

  file_dlg = gtk_file_selection_new(_("Numakiti: Open..."));
  gtk_window_set_modal(GTK_WINDOW(file_dlg), TRUE);
  GTK_WINDOW(file_dlg)->type = GTK_WINDOW_DIALOG;
  gtk_signal_connect_object(GTK_OBJECT(file_dlg), "destroy",
		            GTK_SIGNAL_FUNC(gtk_widget_destroy),
			    GTK_OBJECT(file_dlg));
  gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(file_dlg)->ok_button),
			    "clicked", GTK_SIGNAL_FUNC(open_dlg_ok),
			    doc);
  gtk_signal_connect_object(GTK_OBJECT(
                            GTK_FILE_SELECTION(file_dlg)->cancel_button),
			    "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy),
			    GTK_OBJECT(file_dlg));
  gtk_widget_show(file_dlg);

  return;
}

void save_file_dlg(NKEdit *doc)
{
  file_dlg = gtk_file_selection_new(_("Numakiti: Save as..."));
  gtk_window_set_modal(GTK_WINDOW(file_dlg), TRUE);
  GTK_WINDOW(file_dlg)->type = GTK_WINDOW_DIALOG;
  gtk_signal_connect_object(GTK_OBJECT(file_dlg), "destroy",
		            GTK_SIGNAL_FUNC(gtk_widget_destroy),
			    GTK_OBJECT(file_dlg));
  gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(file_dlg)->ok_button),
			    "clicked", GTK_SIGNAL_FUNC(save_dlg_ok),
			    doc);
  gtk_signal_connect_object(GTK_OBJECT(
                            GTK_FILE_SELECTION(file_dlg)->cancel_button),
			    "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy),
			    GTK_OBJECT(file_dlg));
  gtk_widget_show(file_dlg);

  return;
}














































