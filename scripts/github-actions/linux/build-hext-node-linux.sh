#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j3"
THREADS=3

perror_exit() { echo "$1" >&2 ; exit 1 ; }

HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../../"
OUTD="$(readlink -f "$NODE_OUT")"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$NODE_OUT')"
LIBHEXTD="$HEXTD/libhext"


export CC=gcc CXX=g++
hash gcc-8 && export CC=gcc-8 CXX=g++-8
hash gcc-9 && export CC=gcc-9 CXX=g++-9
hash gcc-10 && export CC=gcc-10 CXX=g++-10
hash gcc-11 && export CC=gcc-11 CXX=g++-11
$CXX --version


find /usr/lib -iname "libgtest*.a" | grep . > /dev/null || {
  GTESTD=$(mktemp -d)
  cd "$GTESTD"
  cmake -H/usr/src/gtest/ -B.
  make $MAKE_FLAGS
  sudo cp $(find . -iname "*libgtest*.a") /usr/lib
}


cd "$LIBHEXTD/test/build"
cmake \
  -DBUILD_SHARED_LIBS=Off \
  -DBoost_USE_STATIC_LIBS=On \
  -DCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  -DBOOST_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  -DBoost_USE_STATIC_RUNTIME=On ..
make -j$THREADS
./libhext-test


cd "$HEXTD/build"
cmake -DBUILD_SHARED_LIBS=Off \
      -DCMAKE_POLICY_DEFAULT_CMP0074=NEW \
      -DBOOST_ROOT="$HEXT_BOOST_INSTALL_PATH" \
      -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
      -DCMAKE_POSITION_INDEPENDENT_CODE=On \
      -DCMAKE_EXE_LINKER_FLAGS=" -static-libgcc -static-libstdc++ " \
      -DBoost_USE_STATIC_LIBS=On \
      -DBoost_USE_STATIC_RUNTIME=On \
      ..
make -j$THREADS
sudo make install


hash node 2>/dev/null || {
  curl -fsSL https://deb.nodesource.com/setup_17.x | sudo bash -
  sudo apt-get install -y nodejs
}


cd "$LIBHEXTD/bindings/nodejs"
npm install
npm install prebuild
npx prebuild \
  -t "$HEXT_NODE_API_VERSION1" \
  -t "$HEXT_NODE_API_VERSION2" \
  -t "$HEXT_NODE_API_VERSION3" \
  -t "$HEXT_NODE_API_VERSION4" \
  --strip --verbose \
  --backend cmake-js \
  -- \
  --CDCMAKE_CXX_FLAGS=" -static-libgcc -static-libstdc++ -Wl,-as-needed " \
  --CDCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  --CDBOOST_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  --CDGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  --CDBUILD_SHARED_LIBS=On \
  --CDBoost_USE_STATIC_LIBS=On \
  --CDBoost_USE_STATIC_RUNTIME=On \
  --CDCMAKE_BUILD_TYPE=Release


cd prebuilds
for i in *.tar.gz ; do
  tar xf "$i"
  ldd build/Release/hext.node
  objdump -T build/Release/hext.node | grep -oE 'GLIBC_[.0-9]*' | sort | uniq
  cp build/Release/hext.node "$OUTD/${i%%.tar.gz}.node"
done

