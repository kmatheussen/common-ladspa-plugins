#!/bin/sh

# COMPILER_FLAGS="-msse2 -mfpmath=sse -O2" ./build_lmms.sh x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++ build/build_lmms build/dlls


if [ -z "$1" ]; then
    echo "arg1 (CC) is unset";
    exit -1
fi

if [ -z "$2" ]; then
    echo "arg1 (CCC) is unset";
    exit -1
fi

if [ -z "$3" ]; then
    echo "arg1 (BUILD) is unset";
    exit -1
fi

if [ -z "$4" ]; then
    echo "arg1 (DEST) is unset";
    exit -1
fi

set -e
set -x



CC=$1
CCC=$2
BUILD=$3
DEST=$4

WINDRES=i686-w64-mingw32-windres
PKGCONFIG=x86_64-apple-darwin12-pkg-config

ROOT=`pwd`

mkdir -p $DEST

rm -fr ${BUILD}_old
mkdir -p $BUILD
mv -f $BUILD ${BUILD}_old

mkdir -p $BUILD


cd $BUILD


cp -a $ROOT/lmms/lmms/plugins/LadspaEffect .
cp -a $ROOT/lmms/lmms/include .

cd LadspaEffect

cat $ROOT/toolchain-template.cmake | sed s/__CC__/$CC/g | sed s/__CCC__/$CCC/g | sed s/__WINDRES__/$WINDRES/g | sed s:__ROOT__:$ROOT/$BUILD:g >toolchain.cmake



function build {
    cd $1

    rm -fr CMakeFiles CMakeCache.txt 

    if [[ $BUILD == *darwin* ]]
    then
        sed -i s/-Wl,-no-undefined//g CMakeLists.txt
        sed -i s/-Wl,-Bsymbolic//g CMakeLists.txt
        sed -i s/-shared//g CMakeLists.txt 
    fi
    
    CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake .
    CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" make VERBOSE=1
    
    cp *.so $ROOT/$DEST/
    
    cd ..
}

build calf
build caps
build cmt
build swh
build tap
