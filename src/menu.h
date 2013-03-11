/* $Id: menu.h,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $
 *
 * Numakiti Editor for GTK.
 * Copyright (C) 2000 Kazuya NUMATA.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __MENU_H__
#define __MENU_H__

#define MENUITEM_ADD(menu, menuitem, label, data) \
{ \
	menuitem = gtk_menu_item_new_with_label(label); \
	gtk_widget_show(menuitem); \
	gtk_menu_append(GTK_MENU(menu), menuitem); \
	if (data) \
		gtk_object_set_user_data(GTK_OBJECT(menuitem), \
					 GINT_TO_POINTER(data)); \
}

GtkWidget *menubar_create	(GtkWidget		*window,
				 GtkItemFactoryEntry	*entries,
				 guint			 n_entries,
				 const gchar		*path,
				 gpointer		 data);
GtkWidget *menu_create_items	(GtkItemFactoryEntry	*entries,
				 guint			 n_entries,
				 const gchar		*path,
				 GtkItemFactory	       **factory,
				 gpointer		 data);
void menu_set_sensitive		(GtkItemFactory		*ifactory,
				 const gchar		*path,
				 gboolean		 sensitive);
void menu_set_insensitive_all	(GtkMenuShell		*menu_shell);

#endif /* __MENU_H__ */
