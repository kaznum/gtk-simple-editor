/* $Id: nkfile.h,v 1.1.1.1 2002/12/28 19:53:03 kaz Exp $ *
 * Numakiti Editor for GTK+
 * Copyright (c) Kazuya NUMATA <kaznum@gol.com>
 * This program can be distributed under GNU General Public License.
 */
#define READ_BUFFER_SIZE 4096
void open_file_dlg(NKEdit *doc);
void save_file_dlg(NKEdit *doc);
void confir_save_dlg(NKEdit *doc, gint from);
