#!/bin/sh

# todo: Dynamically set CMAKE_SYSTEM_NAME and CMAKE_AR


set -e
set -x

COMPILER_FLAGS="-mtune=generic -msse2 -mfpmath=sse -O3 -g"

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
./build_darwinx64.sh "$COMPILER_FLAGS"
./build_mingw64.sh "$COMPILER_FLAGS"
./build_mingw32.sh "$COMPILER_FLAGS"


# This plugin is very unstable. Crashes 50% of the time immediately after creation, and it often crashes later as well. Bug seems to be caused by overwriting unrelated memory areas,
# which in the best case causes an immediate segfault, but in worst case (and this happens too), overwrites unrelated data in other parts of the program, causing very strange bugs.
# (Also, from the swh documentation: "N.B. as far as I know, noone has tried to use this (I certainly haven't), so it may be full of bugs and what not.". That's definitely correct.)
rm -f build/*/dlls/hermes_filter_1200.*

# This plugin seems likely to be unstable.
# From the swh documentation: "I haven't been able to test this plugin, so there may be bugs. I have successfully tested the algorithm, but the implementation is suspect. "
# So remove it, just in case.
rm -f build/*/dlls/surround_encoder_1401.*


