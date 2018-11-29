#!/bin/sh
set -e
. ./iso.sh

export DISPLAY=0:0

qemu-system-$(./trip-to-arch.sh $HOST) -cdrom sos.iso
