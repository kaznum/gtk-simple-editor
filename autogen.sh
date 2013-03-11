#!/bin/sh

aclocal && autoconf && autoheader && automake --add-missing --foreign --copy
####aclocal && autoconf && autoheader && automake --add-missing --foreign --copy && ./configure
