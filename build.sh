#!/bin/sh -eu

#make ${MAKE_OPTS:-} -C kernel kernel.elf
cd /Users/yuu/mikanOS_yuu/kernel
source ~/osbook/devenv/buildenv.sh
make
rm ./.*.d
rm ./*.o
rm ./usb/.*.d
rm ./usb/*.o
rm ./usb/xhci/.*.d
rm ./usb/xhci/*.o
rm ./usb/classdriver/.*.d
rm ./usb/classdriver/*.o
cd -

for MK in $(ls apps/*/Makefile)
do
  APP_DIR=$(dirname $MK)
  APP=$(basename $APP_DIR)
  make ${MAKE_OPTS:-} -C $APP_DIR $APP
done

if [ "${1:-}" = "run" ]
then
  MIKANOS_DIR=$PWD $HOME/osbook/devenv/run_mikanos.sh
fi
