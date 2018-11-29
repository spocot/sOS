#!/bin/sh
set -e
. ./config.sh

for i in $PROJECTS; do
    (cd $i && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf sos.iso
