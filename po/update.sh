#!/bin/sh

xgettext --default-domain=numakiti --directory=.. \
  --add-comments --keyword=_ --keyword=N_ \
  --files-from=./POTFILES.in \
&& test ! -f numakiti.po \
   || ( rm -f ./numakiti.pot \
    && mv numakiti.po ./numakiti.pot )
