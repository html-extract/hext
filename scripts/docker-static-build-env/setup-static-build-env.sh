#!/usr/bin/env bash

set -e

THREADS=3

perror_exit() { echo "$1" >&2 ; exit 1 ; }


PACKD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/packages"
[[ -d "$PACKD" ]] || perror_exit "cannot access packages directory (expected '$PACKD')"


BUILDD=$(mktemp -d)
cd "$BUILDD"


yum -y install pcre pcre-devel swig3 rapidjson-devel gtest-devel
yum -y clean all


tar -x -f "$PACKD"/boost*
cd boost*
./bootstrap.sh --with-libraries=regex,program_options
./b2 -j$THREADS cxxflags="-fPIC" runtime-link=static variant=release link=static install
cd ..
rm -rf boost*


tar -x -f "$PACKD"/gumbo*
cd gumbo*
./autogen.sh
CFLAGS="-fPIC" ./configure --enable-shared=no
make -j$THREADS
make install
cd ..
rm -rf gumbo*


rm -rf "$PACKD"


