#!/usr/bin/env bash

set -e

THREADS=2

perror_exit() { echo "$1" >&2 ; exit 1 ; }

OUTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/output"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$OUTD')"

[[ ":$PATH:" == *":/usr/local/bin:"* ]] || export PATH="/usr/local/bin:$PATH"
[[ ":$PATH:" == *":/Applications/CMake.app/Contents/bin:"* ]] || export PATH="/Applications/CMake.app/Contents/bin:$PATH"
export CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++

for dependency in cmake node git ; do
  hash $dependency 2>/dev/null || perror_exit "cannot find '$dependency'"
done


HEXTD=$(mktemp -d)
git clone "https://github.com/html-extract/hext.git" "$HEXTD"
LIBHEXTD="$HEXTD/libhext"


cd "$LIBHEXTD/build"
cmake -DBUILD_SHARED_LIBS=Off \
      -DCMAKE_POSITION_INDEPENDENT_CODE=On \
      -DCMAKE_EXE_LINKER_FLAGS=" -static-libgcc -static-libstdc++ " \
      ..
make -j$THREADS
sudo make install


cd "$LIBHEXTD/test/build"
cmake -DBUILD_SHARED_LIBS=Off ..
make -j$THREADS
./libhext-test


cd "$LIBHEXTD/bindings/nodejs"
npm install
echo 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ ")' >> CMakeLists.txt
npx -s /bin/bash prebuild \
  -t 8.0.0 -t 10.0.0 -t 11.0.0 -t 12.0.0 \
  --strip --verbose \
  --backend cmake-js \
  -- \
  --CDBUILD_SHARED_LIBS=On \
  --CDCMAKE_BUILD_TYPE=Release


cd prebuilds
for i in *.tar.gz ; do
  tar xf "$i"
  otool -L build/Release/hext.node
  cp build/Release/hext.node "$OUTD/${i%%.tar.gz}.node"
done

