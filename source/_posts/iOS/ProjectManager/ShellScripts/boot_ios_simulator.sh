#!/bin/sh
set -xeuo pipefail

simulator=$1

export LC_ALL="en_US.UTF-8"

bootSimulator() {
    xcrun instruments -w simulator
}

if [[ -n $simulator ]] then
    bootSimulator
else
    echo "q"
fi
