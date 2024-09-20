#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j2"
perror_exit() { echo "$1" >&2 ; exit 1 ; }

HEXTD="$( pwd )"
LIBHEXTD="$HEXTD/libhext"
cd "$LIBHEXTD/test/build"
CMAKE_PREFIX_PATH="$HEXT_BOOST_INSTALL_PATH:$HEXT_GUMBO_INSTALL_PATH" cmake \
  -DBoost_USE_STATIC_RUNTIME=On \
  ..
make $CMAKE_MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
CMAKE_PREFIX_PATH="$HEXT_BOOST_INSTALL_PATH:$HEXT_GUMBO_INSTALL_PATH" cmake \
  -DBoost_USE_STATIC_RUNTIME=On \
  -DBUILD_SHARED_LIBS=Off \
  -DCMAKE_POSITION_INDEPENDENT_CODE=On ..
make $CMAKE_MAKE_FLAGS
sudo make install
sudo strip /usr/local/bin/htmlext

