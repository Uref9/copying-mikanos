#!/bin/bash

cd ~/edk2
source edksetup.sh
build
cd -

git diff --ignore-all-space --ignore-blank-lines \
  /workspaces/mikanos-devcontainer/copying-mikanos/MikanLoaderPkg/Main.c \
  /workspaces/mikanos-devcontainer/mikanos/MikanLoaderPkg/Main.c