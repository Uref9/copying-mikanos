#!/bin/bash

DIR=$1

if [ "$DIR" = "kernel" ]; then
  cd /workspaces/mikanos-devcontainer/copying-mikanos/kernel
  make clean
  make dclean
  cd -
fi
# elif [ "$DIR" = "MikanLoaderPkg/Main.c" ]; then
#   cd ~/edk2
#   source edksetup.sh
#   build
#   cd -


# apps make?

git diff --ignore-all-space --ignore-blank-lines \
  /workspaces/mikanos-devcontainer/copying-mikanos/$DIR \
  /workspaces/mikanos-devcontainer/mikanos/$DIR