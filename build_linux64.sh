#!/bin/sh

if [ -z "$1" ]; then
    echo "arg1 (COMIPLER_FLAGS) is unset";
    exit -1
fi

set -e
set -x


COMPILER_FLAGS=$1

SYSTEM=linux64

CC=`which gcc` #x86_64-redhat-linux-gcc
CCC=`which g++` #x86_64-redhat-linux-g++

COMPILER_FLAGS=$COMPILER_FLAGS ./build_kokkinizita.sh $CC $CCC build/$SYSTEM/build_mcp build/$SYSTEM/dlls
COMPILER_FLAGS=$COMPILER_FLAGS ./build_lmms.sh $CC $CCC build/$SYSTEM/build_lmms build/$SYSTEM/dlls
