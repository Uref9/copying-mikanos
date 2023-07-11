#!/bin/bash

cd /workspaces/mikanos-devcontainer/copying-mikanos/kernel
source ~/osbook/devenv/buildenv.sh
make
make dclean
cd -

cd ~/edk2
source edksetup.sh
build
cd -

cd /workspaces/mikanos-devcontainer/copying-mikanos
~/osbook/devenv/run_qemu.sh \
  ~/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi \
  /workspaces/mikanos-devcontainer/copying-mikanos/kernel/kernel.elf
cd -
