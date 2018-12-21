#!/usr/bin/env bash

set -e

THREADS=3

perror_exit() { echo "$1" >&2 ; exit 1 ; }


PACKD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/packages"
[[ -d "$PACKD" ]] || perror_exit "cannot access packages directory (expected '$PACKD')"


BUILDD=$(mktemp -d)
cd "$BUILDD"


yum -y install libicu libicu-devel pcre pcre-devel
yum -y clean all


tar -x -f "$PACKD"/gcc*
cd gcc*
./contrib/download_prerequisites
./configure --enable-languages=c,c++ --disable-multilib
make -j$THREADS
make install
export PATH="/usr/local/bin:$PATH"
export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++
cd ..
rm -rf gcc*


tar -x -f "$PACKD"/boost*
cd boost*
./bootstrap.sh --with-libraries=regex,program_options
./b2 -j$THREADS cxxflags="-fPIC" runtime-link=static variant=release link=static install
cd ..
rm -rf boost*


tar -x -f "$PACKD"/cmake*
cd cmake*
./bootstrap --parallel=$THREADS
make -j$THREADS
make install
cd ..
rm -rf cmake*


tar -x -f "$PACKD"/rapidjson*
cd rapidjson*
mkdir build
cd build
cmake -DRAPIDJSON_BUILD_DOC=Off -DRAPIDJSON_BUILD_EXAMPLES=Off -DRAPIDJSON_BUILD_TESTS=Off ..
make install
cd ../..
rm -rf rapidjson*


tar -x -f "$PACKD"/google*
cd google*
mkdir build
cd build
cmake ..
make -j$THREADS
make install
cd ../..
rm -rf google*


tar -x -f "$PACKD"/swig*
cd swig*
./configure --disable-perl --disable-ruby --disable-csharp --disable-r --disable-java
make -j$THREADS
make install
cd ..
rm -rf swig*


tar -x -f "$PACKD"/gumbo*
cd gumbo*
./autogen.sh
CFLAGS="-fPIC" ./configure --enable-shared=no
make -j$THREADS
make install
cd ..
rm -rf gumbo*


rm -rf "$PACKD"


