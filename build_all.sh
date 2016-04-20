#!/bin/sh

# todo: Dynamically set CMAKE_SYSTEM_NAME and CMAKE_AR


set -e
set -x

COMPILER_FLAGS="-mtune=generic -msse2 -mfpmath=sse -O3"

unset CFLAGS
unset CFLAGS
unset CPPFLAGS
unset LDFLAGS
unset CXXFLAGS

export CFLAGS="$COMPILER_FLAGS"
export CPPFLAGS="$COMPILER_FLAGS"
export CXXFLAGS="$COMPILER_FLAGS"


# Makes sense to build one at a time. Something is usually not working:

./build_linux64.sh "$COMPILER_FLAGS"
#./build_darwinx64.sh "$COMPILER_FLAGS"
#./build_mingw64.sh "$COMPILER_FLAGS"
#./build_mingw32.sh "$COMPILER_FLAGS"
