#!/bin/sh

if [ -z "$1" ]; then
    echo "arg1 (COMIPLER_FLAGS) is unset";
    exit -1
fi

set -e
set -x

#-mmacosx-version-min=10.7 -stdlib=libc++

P=x86_64-apple-darwin21
export P=$P

MYFLAGS="-mtune=generic -mfpmath=sse -msse2  -Wno-gnu-designator -fvisibility=default"

COMPILER_FLAGS="$1 -I/opt/local/include  -Llocal/lib"

SYSTEM=darwinx64

CC=$P-clang
CCC=$P-clang++

COMPILER_FLAGS=$COMPILER_FLAGS ./build_kokkinizita.sh $CC $CCC build/$SYSTEM/build_mcp build/$SYSTEM/dlls
COMPILER_FLAGS=$COMPILER_FLAGS ./build_lmms.sh $CC $CCC build/$SYSTEM/build_lmms build/$SYSTEM/dlls
