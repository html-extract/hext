#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j2"
perror_exit() { echo "$1" >&2 ; exit 1 ; }

HEXTD="$( pwd )"
LIBHEXTD="$HEXTD/libhext"
cd "$LIBHEXTD/test/build"
cmake \
  -DCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  -DBOOST_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  -DBoost_USE_STATIC_RUNTIME=On \
  -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" ..
make $CMAKE_MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
cmake \
  -DCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  -DBOOST_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  -DBoost_USE_STATIC_RUNTIME=On \
  -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  -DBUILD_SHARED_LIBS=Off \
  -DCMAKE_POSITION_INDEPENDENT_CODE=On ..
make $CMAKE_MAKE_FLAGS
sudo make install
sudo strip /usr/local/bin/htmlext

