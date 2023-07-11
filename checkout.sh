#!/bin/bash

version=$1

cd /workspaces/mikanos-devcontainer/mikanos
git checkout osbook_day$1 && echo --- now osbook_day$1 ---
cd -./