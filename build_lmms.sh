#!/bin/sh

# cmake is a nightmare. There's always lots of different ways to do things, and if you are lucky, one of the ways work, if you can find it.


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

WINDRES=i686-w64-mingw32.shared-windres
PKGCONFIG=i686-w64-mingw32.shared-pkg-config

ROOT=`pwd`
COMPILER_FLAGS="$COMPILER_FLAGS -I$ROOT/include"

mkdir -p $DEST

rm -fr ${BUILD}_old
mkdir -p $BUILD
mv -f $BUILD ${BUILD}_old

mkdir -p $BUILD


cd $BUILD


cp -a $ROOT/lmms/lmms/plugins/LadspaEffect .
cp -a $ROOT/lmms/lmms/include .

cd LadspaEffect

# Belowy, change toolchain-template file to the right one.
cat $ROOT/toolchain-template.cmake | sed s/__CC__/$CC/g | sed s/__CCC__/$CCC/g | sed s/__WINDRES__/$WINDRES/g | sed s:__ROOT__:$ROOT/$BUILD:g >toolchain.cmake


function build {
    cd $1
    
    rm -fr CMakeFiles CMakeCache.txt cmake_install.cmake Makefile


    if [[ $BUILD == *darwin* ]]
    then
        sed -i s/-Wl,-no-undefined//g CMakeLists.txt
        sed -i s/-Wl,-Bsymbolic//g CMakeLists.txt
        sed -i s/-shared//g CMakeLists.txt
    fi
    
#    CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" i686-w64-mingw32.shared-cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake .
#    CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" i686-w64-mingw32.shared-cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw32.cmake .
#    CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" i686-w64-mingw32.shared-cmake .
    #CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" x86_64-w64-mingw32.shared-cmake .
    if [[ $BUILD == *darwin* ]]
    then
        CMAKE_AR=x86_64-apple-darwin17-ar CMAKE_RANLIB=x86_64-apple-darwin17-ranlib CFLAGS="$COMPILER_FLAGS $2" CXXFLAGS="$COMPILER_FLAGS $2" CMAKE_C_COMPILER="$CC $COMPILER_FLAGS $2" CMAKE_CXX_COMPILER="$CCC $COMPILER_FLAGS $2" CMAKE_EXE_LINKER_FLAGS="$2" CMAKE_MODULE_LINKER_FLAGS="$2" CMAKE_SHARED_LINKER_FLAGS="$2" CMAKE_CXX_LINK_EXECUTABLE="$CCC $2" CMAKE_CC_LINK_EXECUTABLE="$CC $2" CC="$CC" CXX="$CCC" LD="$CC $2" LD_FLAGS="$2" LDFLAGS="$2" LINKER="$CC $2" CMAKE_LINKER="$CC $2" cmake .
    elif [[ $BUILD == *linux* ]]
    then
        CFLAGS="$COMPILER_FLAGS $2" CXXFLAGS="$COMPILER_FLAGS $2" cmake .
    elif [[ $BUILD == *mingw32* ]]
    then
        CFLAGS="$COMPILER_FLAGS $2" CXXFLAGS="$COMPILER_FLAGS $2" i686-w64-mingw32.shared-cmake .
    else
        CFLAGS="$COMPILER_FLAGS $2" CXXFLAGS="$COMPILER_FLAGS $2" x86_64-w64-mingw32.shared-cmake .
    fi
    
    if [[ $BUILD == *darwin* ]]
    then
        for a in CMakeFiles/*.dir/link.txt ; do
            sed -i s:-Wl,-soname,:"-o ":g $a
            sed -i s:"/usr/bin/ar ":"x86_64-apple-darwin17-ar ":g $a
            sed -i s:"/usr/bin/ranlib ":"x86_64-apple-darwin17-ranlib ":g $a
            #sed -i s/-Wl,-soname,$1.so//g $a
        done
    fi

    CFLAGS="$COMPILER_FLAGS" CXXFLAGS="$COMPILER_FLAGS" LDFLAGS="$2" make VERBOSE=1

    if [[ $BUILD == *darwin* ]]
    then
        cp *.so $ROOT/$DEST/
    elif [[ $BUILD == *linux* ]]
    then
        cp *.so $ROOT/$DEST/
    else
        cp *.dll $ROOT/$DEST/
    fi

    rm -f $ROOT/$DEST/ladspa-util.*
    
    cd ..
}

#build tap # Built in build_kokkiniza.sh instead.build caps
build calf
build caps

if [[ $BUILD == *darwin* ]]
then
    build cmt  `x86_64-apple-darwin17-pkg-config --cflags --libs fftw3`
    build swh "`x86_64-apple-darwin17-pkg-config --cflags --libs fftw3`"
elif [[ $BUILD == *linux* ]]
then
    build cmt ""
    build swh "-lrt"
else
    build cmt ""
    build swh ""
fi

