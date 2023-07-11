#!/bin/bash

DIR=$1

if [ "$DIR" = "kernel" ]; then
  cd /workspaces/mikanos-devcontainer/copying-mikanos/kernel
  make
  make dclean
  cd -
elif [ "$DIR" = "MikanLoaderPkg/Main.c" ]; then
  cd ~/edk2
  source edksetup.sh
  build
  cd -
fi


# apps make?

git diff --ignore-all-space --ignore-blank-lines \
  /workspaces/mikanos-devcontainer/copying-mikanos/$DIR \
  /workspaces/mikanos-devcontainer/mikanos/$DIR