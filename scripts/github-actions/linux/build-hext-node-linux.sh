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
hash gcc-9 && export CC=gcc-9 CXX=g++-9
hash gcc-10 && export CC=gcc-10 CXX=g++-10
hash gcc-11 && export CC=gcc-11 CXX=g++-11
hash gcc-12 && export CC=gcc-12 CXX=g++-12
hash gcc-13 && export CC=gcc-13 CXX=g++-13
hash gcc-14 && export CC=gcc-14 CXX=g++-14
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
  -DBoost_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  -DBoost_USE_STATIC_RUNTIME=On ..
make -j$THREADS
./libhext-test


cd "$HEXTD/build"
cmake -DBUILD_SHARED_LIBS=Off \
      -DCMAKE_POLICY_DEFAULT_CMP0074=NEW \
      -DBoost_ROOT="$HEXT_BOOST_INSTALL_PATH" \
      -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
      -DCMAKE_POSITION_INDEPENDENT_CODE=On \
      -DCMAKE_EXE_LINKER_FLAGS=" -static-libgcc -static-libstdc++ " \
      -DBoost_USE_STATIC_LIBS=On \
      -DBoost_USE_STATIC_RUNTIME=On \
      ..
make -j$THREADS
sudo make install


cd "$LIBHEXTD/bindings/nodejs"
npm install
npm install prebuild
cat node_modules/node-abi/package.json || true
npm install "node-abi@^4.8.0"
cat node_modules/node-abi/package.json || true
npx prebuild \
  -t "$HEXT_NODE_API_VERSION1" \
  -t "$HEXT_NODE_API_VERSION2" \
  -t "$HEXT_NODE_API_VERSION3" \
  -t "$HEXT_NODE_API_VERSION4" \
  --strip --verbose \
  --backend cmake-js \
  -- \
  --CDHEXT_BUILD_STATIC_RELEASE=On \
  --CDCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  --CDBoost_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  --CDGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  --CDBUILD_SHARED_LIBS=On \
  --CDBoost_USE_STATIC_LIBS=On \
  --CDBoost_USE_STATIC_RUNTIME=On \
  --CDCMAKE_BUILD_TYPE=Release


grep "define NODE_MODULE_VERSION" $(find "$HOME" -name node_version.h)
ls -1 prebuilds/


cd prebuilds
for i in *.tar.gz ; do
  tar xf "$i"
  ldd build/Release/hext.node
  echo -n "Minimum GLIBC version: "
  objdump -T build/Release/hext.node | grep -oE 'GLIBC_[.0-9]*' | sort --version-sort | tail -n1
  cp build/Release/hext.node "$OUTD/${i%%.tar.gz}.node"
done

