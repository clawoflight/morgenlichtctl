#! /bin/sh

aclocal \
&& automake --add-missing --foreign \
&& autoconf -I config
