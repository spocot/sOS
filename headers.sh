#!/bin/sh
set -e
. ./config.sh

mkdir -p "$SYSROOT"

for i in $SYSTEM_HEADER_PROJECTS; do
    (cd $i && DESTDIR="$SYSROOT" $MAKE install-headers)
done
