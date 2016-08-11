#!/bin/sh


# COMPILER_FLAGS="-msse2 -mfpmath=sse -O2" ./build_kokkinizita.sh x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++ build/build_mcp build/dlls


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

ROOT=`pwd`

mkdir -p $DEST

rm -fr ${BUILD}_old
mkdir -p $BUILD
mv -f $BUILD ${BUILD}_old

mkdir -p $BUILD

cd $BUILD

function build {

    cp -a $1 .
    cd $2

    if [[ $BUILD == *darwin* ]]
    then
        cat Makefile | sed s/g++/$CCC/g >Makefile.cross
    elif [[ $BUILD == *linux* ]]
    then
        cat Makefile | sed s/g++/$CCC/g >Makefile.cross
    else
        cat Makefile | sed s/g++/$CCC/g | sed 's/\.so/\.dll/g' >Makefile.cross
    fi
    
    CXX="$CCC" CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" make -f Makefile.cross

    if [[ $BUILD == *darwin* ]]
    then
        cp *.so $ROOT/$DEST/
    elif [[ $BUILD == *linux* ]]
    then
        cp *.so $ROOT/$DEST/
    else
        cp *.dll $ROOT/$DEST/
    fi


    cd ..
}

function build_kokkinizita {
    build $ROOT/kokkinizita/$1 $1
}

build_kokkinizita tap-plugins-0.7.3

build_kokkinizita MCP-plugins-0.4.0
build_kokkinizita AMB-plugins-0.8.1
build_kokkinizita STE-plugins-0.0.2
build_kokkinizita REV-plugins-0.7.1
build_kokkinizita VCO-plugins-0.3.0
build_kokkinizita FIL-plugins-0.3.0
build_kokkinizita WAH-plugins-0.1.0
build_kokkinizita g2reverb-0.7.1
