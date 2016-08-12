#!/bin/sh

if [ -z "$1" ]; then
    echo "arg1 (COMIPLER_FLAGS) is unset";
    exit -1
fi


set -e
set -x


COMPILER_FLAGS=$1

SYSTEM=mingw64

CC=x86_64-w64-mingw32.shared-gcc
CCC=x86_64-w64-mingw32.shared-g++

COMPILER_FLAGS=$COMPILER_FLAGS ./build_kokkinizita.sh $CC $CCC build/$SYSTEM/build_mcp build/$SYSTEM/dlls
COMPILER_FLAGS=$COMPILER_FLAGS ./build_lmms.sh $CC $CCC build/$SYSTEM/build_lmms build/$SYSTEM/dlls
