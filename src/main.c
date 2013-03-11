/* $Id: main.c,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $ 
 * 
 * Numakiti Editor for GTK+
 * Copyright (c) Kazuya NUMATA <kaznum@gol.com>
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include <gtk/gtk.h>
#include <locale.h> 
#include <stdio.h>
#include "intl.h"
#include "main.h"
#include "menu.h"
//#include "nkfile.h"
#include "callbacks.h"

/* ToolBar pixmaps */
#include "pixmaps/new.xpm"
#include "pixmaps/open.xpm"
#include "pixmaps/save.xpm"
#include "pixmaps/save_as.xpm"
#include "pixmaps/print.xpm"
#include "pixmaps/cut.xpm"
#include "pixmaps/copy.xpm"
#include "pixmaps/paste.xpm"
#include "pixmaps/exit.xpm"

NKEdit nkdoc;
void itemfact_cb(GtkWidget *widget, guint action);

/* The quit_tmp_cb is accessed from "delete_event") */
void quit_tmp_cb(GtkWidget *widget, gpointer data); 

static GtkItemFactoryEntry menu_items[] = {
  {N_("/_File"),NULL,NULL,0,"<Branch>" },
  {N_("/_File/_New"),"<control>N", itemfact_cb, NEW_CB ,NULL },
  {N_("/_File/_Open"), "<control>O", &itemfact_cb, OPEN_CB, NULL},
  {N_("/_File/_Save"), "<control>S", &itemfact_cb, SAVE_CB,NULL },
  {N_("/_File/Save _as"), NULL, &itemfact_cb, SAVE_AS_CB, NULL },
  {N_("/_File/---"),NULL,NULL,0,"<Separator>" },
  {N_("/_File/_Print"),"<control>P", &itemfact_cb, PRINT_CB, NULL },
  {N_("/_File/---"),NULL,NULL,0,"<Separator>" },
  {N_("/_File/_Quit"),"<control>Q", &itemfact_cb,QUIT_CB,NULL },

  {N_("/_Edit"),NULL,NULL,0,"<Branch>" },
  {N_("/_Edit/_Cut"),"<control>X", &itemfact_cb, CUT_CB, NULL },
  {N_("/_Edit/C_opy"),"<control>C", &itemfact_cb, COPY_CB, NULL },
  {N_("/_Edit/_Paste"),"<control>V", &itemfact_cb, PASTE_CB, NULL },
  {N_("/_Edit/Select _All"),"<control>A", &itemfact_cb, SELECT_ALL_CB, NULL },
  {N_("/_Edit/---"), NULL, NULL, 0, "<Separator>"},
  {N_("/_Edit/P_references..."), NULL, &itemfact_cb, PREFERENCE_CB, NULL },

  {N_("/_Help"),NULL,NULL,0,"<LastBranch>" },
  {N_("/_Help/About"),NULL, &nk_about_cb,0,NULL},
};

int main(int argc, char *argv[])
{
  GtkWidget *main_window;
  GtkWidget *vbox, *hbox;
  GtkWidget *vscrollbar;
  GtkWidget *menu_bar;
  GtkWidget *handle_box;
  GtkWidget *toolbar, *button;
  GdkPixmap *icon;
  GdkBitmap *mask;
  GtkWidget *iconw;
  GtkStyle *style;
  gint n_menu_entries;

  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE); 

  gtk_set_locale();
  gtk_init(&argc, &argv);

  //  nkedit_init(&nkdoc);

  main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //  The following line does not work well 
  //  gtk_signal_connect(GTK_OBJECT(main_window), "delete_event",
  //		     GTK_SIGNAL_FUNC(nk_quit_cb), &nkdoc);

  gtk_signal_connect(GTK_OBJECT(main_window), "delete_event",
		     GTK_SIGNAL_FUNC(&quit_tmp_cb), NULL);
  gtk_window_set_title(GTK_WINDOW(main_window), _("Numakiti"));
  gtk_container_set_border_width(GTK_CONTAINER(main_window),0);

  vbox=gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(main_window),vbox);


  /* Menu Bar */
  n_menu_entries = sizeof(menu_items) /sizeof(menu_items[0]);
  menu_bar = menubar_create(main_window ,menu_items, n_menu_entries, 
			    "<Main>", NULL);
  gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, TRUE, 0);

  gtk_widget_show(menu_bar);

  /* Toolbar */
  handle_box = gtk_handle_box_new();
  gtk_box_pack_start(GTK_BOX(vbox), handle_box, FALSE, FALSE, 0);
  gtk_widget_show(handle_box);

  toolbar = gtk_toolbar_new(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_BOTH);
  gtk_container_add(GTK_CONTAINER(handle_box), toolbar);
  /* Toolbar's buttons were connected fluently */
  gtk_toolbar_set_button_relief(GTK_TOOLBAR(toolbar), GTK_RELIEF_NONE);
  /* Toolbar's buttons were separatly with lines */
  gtk_toolbar_set_space_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_SPACE_LINE);

  /* When using pixmap, you need realize the window */
  gtk_widget_realize(main_window);
  style = gtk_widget_get_style(main_window);
  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)new_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("New"),
				   _("New Document"),
				   "New",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_new_cb),
				   &nkdoc);

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)open_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Open"),
				   _("Open Document"),
				   "Open",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_open_cb),
				   &nkdoc);

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)save_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Save"),
				   _("Save Document"),
				   "Save",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_save_cb),
				   &nkdoc);

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)save_as_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Save As"),
				   _("Save Document As..."),
				   "Save As",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_save_as_cb),
				   &nkdoc);

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)print_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Print"),
				   _("Print Document"),
				   "Print",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_print_cb),
				   &nkdoc);

  gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)cut_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Cut"),
				   _("Cut Selected Text"),
				   "Cut",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_cut_cb),
				   &nkdoc);

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)copy_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Copy"),
				   _("Copy Selected Text"),
				   "Copy",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_copy_cb),
				   &nkdoc);

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)paste_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Paste"),
				   _("Paste Buffered Text"),
				   "Paste",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_paste_cb),
				   &nkdoc);
			  
  gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

  icon=gdk_pixmap_create_from_xpm_d(main_window->window, &mask, 
				    &style->bg[GTK_STATE_NORMAL],
				    (gchar **)exit_xpm);
  iconw = gtk_pixmap_new(icon,mask);
  button = gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
				   _("Quit"),
				   _("Quit Numakiti"),
				   "Quit",
				   iconw,
				   GTK_SIGNAL_FUNC(nk_quit_cb),
				   &nkdoc);

  gtk_widget_show(toolbar);


  /* Text Widget and vscrollbar */
  hbox=gtk_hbox_new(FALSE,1);
  gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);

  nkdoc.text = gtk_text_new(NULL, NULL);
  nkdoc.changed = FALSE;
  gtk_signal_connect(GTK_OBJECT(nkdoc.text), "changed",
		     GTK_SIGNAL_FUNC(&nk_text_changed_cb),&nkdoc);
  gtk_box_pack_start(GTK_BOX(hbox), nkdoc.text, TRUE, TRUE, 0);
  gtk_widget_show(nkdoc.text);
  gtk_widget_grab_focus(nkdoc.text);
  vscrollbar = gtk_vscrollbar_new(GTK_TEXT(nkdoc.text)->vadj);

  gtk_box_pack_end(GTK_BOX(hbox), vscrollbar, FALSE, FALSE, 0);
  gtk_widget_show(vscrollbar);

  /* Make TextWidget Editable */
  gtk_text_set_editable(GTK_TEXT(nkdoc.text),TRUE);

  gtk_widget_show(hbox);

  /* Status Bar initialize */
  nkdoc.status_bar =  gtk_statusbar_new();

  gtk_box_pack_start(GTK_BOX(vbox), nkdoc.status_bar, FALSE, FALSE, 0);
  gtk_widget_show(nkdoc.status_bar);
  nkdoc.statusbar_context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(nkdoc.status_bar),
						      "Statusbar");
  gtk_statusbar_push(GTK_STATUSBAR(nkdoc.status_bar), 
		     nkdoc.statusbar_context_id,
		     _("Not Changed"));
  /* nkdoc.w_mode initialize */
  nkdoc.w_mode = TRUE;

  gtk_widget_show(vbox);

  gtk_widget_show(main_window);
  gtk_main();

  return 0;
}

/* callback for ItemFactoryEntry */
void itemfact_cb(GtkWidget *widget, guint action) {
  switch(action) {
  case NEW_CB:
    nk_new_cb(widget, &nkdoc);
    break;
  case OPEN_CB:
    nk_open_cb(widget, &nkdoc);
    break;
  case SAVE_CB:
    nk_save_cb(widget, &nkdoc);
    break;
  case SAVE_AS_CB:
    nk_save_as_cb(widget, &nkdoc);
    break;
  case QUIT_CB:
    nk_quit_cb(widget, &nkdoc);
    break;
  case PRINT_CB:
    nk_print_cb(widget, &nkdoc);
    break;
  case CUT_CB:
    nk_cut_cb(widget, &nkdoc);
    break;
  case COPY_CB:
    nk_copy_cb(widget, &nkdoc);
    break;
  case PASTE_CB:
    nk_paste_cb(widget, &nkdoc);
    break;
  case SELECT_ALL_CB:
    nk_select_all_cb(widget, &nkdoc);
    break;
  case PREFERENCE_CB:
    nk_preference_cb(widget, &nkdoc);
    break;
  }
  
  return;
}

/* the explanation of the following function is in upper */
void quit_tmp_cb(GtkWidget *widget, gpointer data) {
  nk_quit_cb(widget, &nkdoc);

  return;
}
























