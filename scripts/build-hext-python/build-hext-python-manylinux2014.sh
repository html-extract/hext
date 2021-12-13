#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j3"
THREADS=3

perror_exit() { echo "$1" >&2 ; exit 1 ; }
download_and_verify() {
  curl -vL -o "$1" "$2"
  echo "$3  $1" | sha256sum -c || {
    echo "Error: invalid checksum for $1, expected $3"
    exit 1
  } > /dev/stderr
}

HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../"
ASSETD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/assets"
[[ -d "$ASSETD" ]] || perror_exit "cannot access asset directory (expected '$ASSETD')"
OUTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/output"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$OUTD')"

yum -y install pcre pcre-devel swig3 rapidjson-devel gtest-devel

BUILDD=$(mktemp -d)
cd "$BUILDD"

download_and_verify \
  "boost_1_78_0.tar.gz" \
  "https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz" \
  "94ced8b72956591c4775ae2207a9763d3600b30d9d7446562c552f0a14a63be7"

download_and_verify \
  "gumbo-parser-v0.10.1.tar.gz" \
  "https://github.com/google/gumbo-parser/archive/refs/tags/v0.10.1.tar.gz" \
  "28463053d44a5dfbc4b77bcf49c8cee119338ffa636cc17fc3378421d714efad"

tar -x -f boost*
cd boost*/
./bootstrap.sh --with-libraries=regex,program_options
./b2 -j$THREADS cxxflags="-fPIC" runtime-link=static variant=release link=static install
cd ..

tar -x -f gumbo*
cd gumbo*/
./autogen.sh
CFLAGS="-fPIC" ./configure --enable-shared=no
make -j$THREADS
make install
cd ..

[[ -d "$HEXTD/libhext" ]] || {
  HEXTD=$(mktemp -d)
  git clone "https://github.com/html-extract/hext.git" "$HEXTD"
}

LIBHEXTD="$HEXTD/libhext"
cd "$LIBHEXTD/test/build"
cmake -DBUILD_SHARED_LIBS=Off -DBoost_USE_STATIC_LIBS=On -DBoost_USE_STATIC_RUNTIME=On ..
make $CMAKE_MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
cmake -DBUILD_SHARED_LIBS=Off -DBoost_USE_STATIC_LIBS=On -DBoost_USE_STATIC_RUNTIME=On -DCMAKE_POSITION_INDEPENDENT_CODE=On ..
make $CMAKE_MAKE_FLAGS
make install

PYTHOND="$LIBHEXTD/bindings/python"
cd "$PYTHOND"
for i in /opt/python/cp* ; do
  V=$(basename $i)
  mkdir $V
  cd $V
  mkdir -p wheel/hext
  cp "$ASSETD/setup.py" "$ASSETD/README.md" "$ASSETD/MANIFEST.in" "$ASSETD/gumbo.license" "$ASSETD/rapidjson.license" wheel/

  PIP=$(readlink -f /opt/python/$V/bin/pip)
  $PIP install -U setuptools wheel
  PYTHON_INCLUDE_DIR=$(readlink -f /opt/python/$V/include/python*/)
  PYTHON_LIBRARY=$(readlink -f /opt/python/$V/lib/python*/)
  cmake -DPYTHON_LIBRARY="$PYTHON_LIBRARY" -DPYTHON_INCLUDE_DIR="$PYTHON_INCLUDE_DIR" -DBUILD_SHARED_LIBS=On -DBoost_USE_STATIC_LIBS=On -DBoost_USE_STATIC_RUNTIME=On ..
  make $CMAKE_MAKE_FLAGS
  cp hext.py wheel/hext/__init__.py
  strip --strip-unneeded _hext.so
  cp _hext.so wheel/hext

  mkdir wheel/bin
  cp /usr/local/bin/htmlext wheel/bin
  strip --strip-unneeded wheel/bin/htmlext

  cd wheel
  /opt/python/$V/bin/python setup.py bdist_wheel

  WHEEL=$(find . -iname "*linux*.whl")
  [[ -f "$WHEEL" ]] || perror_exit "cannot find wheel (*linux*.whl)"
  MANYLINUX_WHEEL="$(echo $WHEEL | sed 's/linux/manylinux2014/')"
  mv "$WHEEL" "$MANYLINUX_WHEEL"

  cp "$MANYLINUX_WHEEL" "$OUTD"
  cd ../..
done
