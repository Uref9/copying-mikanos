#!/bin/bash

cd /workspaces/mikanos-devcontainer/copying-mikanos/kernel
source ~/osbook/devenv/buildenv.sh
make
make dclean

git diff --ignore-all-space --ignore-blank-lines \
  /workspaces/mikanos-devcontainer/copying-mikanos/kernel \
  /workspaces/mikanos-devcontainer/mikanos/kernel