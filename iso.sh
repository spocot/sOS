#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/sos.kernel isodir/boot/sos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "sos" {
    multiboot /boot/sos.kernel
}
EOF
grub-mkrescue -o sos.iso isodir
