/* $Id: main.h,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $
 *
 * Numakiti Editor for GTK+
 * Copyright (c) Kazuya NUMATA <kaznum@gol.com>
 * This program can be distributed under GNU General Public License.
 */

#define NEW_CB 1
#define OPEN_CB 2
#define SAVE_CB 3
#define SAVE_AS_CB 4
#define PRINT_CB 5
#define CUT_CB 6
#define COPY_CB 7
#define PASTE_CB 8
#define SELECT_ALL_CB 9
#define QUIT_CB 10
#define PREFERENCE_CB 11

typedef struct {
  GtkWidget *text;
  gboolean changed;
  gchar filename[PATH_MAX];
  guint statusbar_context_id;
  GtkWidget *status_bar;
  gboolean w_mode;
} NKEdit;

/*
 *  typedef struct {
 *  NKEdit *nkedit;
 *  GtkWidget *parent_window;
 *} NKEdit_with_parent;
 */
