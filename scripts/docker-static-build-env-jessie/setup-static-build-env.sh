#!/usr/bin/env bash

set -e

THREADS=3

perror_exit() { echo "$1" >&2 ; exit 1 ; }


PACKD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/packages"
[[ -d "$PACKD" ]] || perror_exit "cannot access packages directory (expected '$PACKD')"


BUILDD=$(mktemp -d)
cd "$BUILDD"


apt-get update
apt-get upgrade -y
apt-get install -y build-essential git curl libtool automake libicu-dev
apt-get clean


[[ -x /usr/local/bin/gcc ]] || {
  tar -x -f "$PACKD"/gcc*
  cd gcc*
  ./contrib/download_prerequisites
  ./configure --enable-languages=c,c++ --disable-multilib --disable-nls
  make -j$THREADS
  make install
  cd ..
  rm -rf gcc*
}

[[ -f /etc/ld.so.conf.d/usr-local-lib64.conf ]] || {
  echo "/usr/local/lib64" > /etc/ld.so.conf.d/usr-local-lib64.conf
}
ldconfig


[[ ":$PATH:" == *":/usr/local/bin:"* ]] || export PATH="/usr/local/bin:$PATH"
export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++


cd "$BUILDD"
[[ -f /usr/local/lib/libboost_regex.a ]] || {
  tar -x -f "$PACKD"/boost*
  cd boost*
  ./bootstrap.sh --with-libraries=regex,program_options
  ./b2 -j$THREADS cxxflags="-fPIC" runtime-link=static variant=release link=static install
  cd ..
  rm -rf boost*
}


cd "$BUILDD"
[[ -x /usr/local/bin/cmake ]] || {
  tar -x -f "$PACKD"/cmake*
  cd cmake*
  ./bootstrap --parallel=$THREADS
  make -j$THREADS
  make install
  cd ..
  rm -rf cmake*
}


cd "$BUILDD"
[[ -f /usr/local/lib/libgtest.a ]] || {
  tar -x -f "$PACKD"/google*
  cd google*
  mkdir build
  cd build
  cmake ..
  make -j$THREADS
  make install
  cd ../..
  rm -rf google*
}


cd "$BUILDD"
[[ -f /usr/local/lib/libgumbo.a ]] || {
  tar -x -f "$PACKD"/gumbo*
  cd gumbo*
  ./autogen.sh
  CFLAGS="-fPIC" ./configure --enable-shared=no
  make -j$THREADS
  make install
  cd ..
  rm -rf gumbo*
}


rm -rf "$PACKD"

