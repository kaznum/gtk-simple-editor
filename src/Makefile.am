bin_PROGRAMS = numakiti

numakiti_SOURCES = \
	main.c main.h \
	about.c about.h \
	menu.c menu.h \
	nkfile.c nkfile.h \
	callbacks.c callbacks.h \
	preference.c preference.h \
	intl.h

EXTRA_DIST = \
	pixmaps/numakiti.xpm \
	pixmaps/new.xpm \
	pixmaps/open.xpm \
	pixmaps/save.xpm \
	pixmaps/save_as.xpm \
	pixmaps/print.xpm \
	pixmaps/cut.xpm \
	pixmaps/copy.xpm \
	pixmaps/paste.xpm \
	pixmaps/exit.xpm

INCLUDES = \
	-I$(top_srcdir)/intl \
	$(GTK_CFLAGS) \
	-I$(includedir)

numakiti_LDADD = \
	$(GTK_LIBS) \
	$(INTLLIBS)

# C Preprocessor Flags
CPPFLAGS = \
	-DLOCALEDIR=\""$(localedir)"\"

CFLAGS = @CFLAGS@ -Wall

check-value:
	echo "GTK_CFLAGS: $(GTK_CFLAGS)"
	echo "top_srcdir/intl: $(top_srcdir)/intl"
	echo "GTK_LIBS: $(GTK_LIBS)"
	echo "CFLAGS: $(CFLAGS)"
