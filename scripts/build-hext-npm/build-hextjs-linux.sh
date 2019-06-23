#!/usr/bin/env bash

set -e

perror_exit() { echo "$1" >&2 ; exit 1 ; }

OUTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/output"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$OUTD')"


export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++
THREADS=3


hash node 2>/dev/null || {
  curl -sL https://deb.nodesource.com/setup_10.x | bash - 
  apt-get install -y nodejs
}


HEXTD=$(mktemp -d)
git clone "https://github.com/html-extract/hext.git" "$HEXTD"
LIBHEXTD="$HEXTD/libhext"


cd "$LIBHEXTD/test/build"
cmake -DBUILD_SHARED_LIBS=Off ..
make -j$THREADS
./libhext-test


cd "$LIBHEXTD/build"
cmake -DBUILD_SHARED_LIBS=Off \
      -DCMAKE_POSITION_INDEPENDENT_CODE=On \
      -DCMAKE_EXE_LINKER_FLAGS=" -static-libgcc -static-libstdc++ " \
      ..
make -j$THREADS
make install


cd "$LIBHEXTD/bindings/nodejs"
npm install
npx -s /bin/bash prebuild \
  -t 8.0.0 -t 10.0.0 -t 11.0.0 -t 12.0.0 \
  --strip --verbose \
  --backend cmake-js \
  -- \
  --CDCMAKE_CXX_FLAGS=\" -static-libgcc -static-libstdc++ -Wl,-as-needed \" \
  --CDBUILD_SHARED_LIBS=On \
  --CDCMAKE_BUILD_TYPE=Release


cd prebuilds
for i in *.tar.gz ; do
  tar xf "$i"
  ldd build/Release/hext.node
  objdump -T build/Release/hext.node | grep -oE 'GLIBC_[.0-9]*' | sort | uniq
  cp build/Release/hext.node "$OUTD/${i%%.tar.gz}.node"
done

