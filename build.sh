#!/bin/sh
set -e
. ./headers.sh

for i in $PROJECTS; do
    (cd $i && DESTDIR="$SYSROOT" $MAKE install)
done
