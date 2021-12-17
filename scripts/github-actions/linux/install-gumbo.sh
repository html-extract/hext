#!/usr/bin/env bash

set -e
set -x

perror_exit() { echo "$1" >&2 ; exit 1 ; }

THREADS=2

deps=(
  "HEXT_GUMBO_VERSION"
  "HEXT_GUMBO_SHA256"
  "HEXT_GUMBO_INSTALL_PATH"
)
for dep in "${deps[@]}" ; do
  [[ -z "${!dep}" ]] && perror_exit "missing env var '$dep'"
done

[[ -f "$HEXT_GUMBO_INSTALL_PATH/include/gumbo.h" ]] \
  && perror_exit "gumbo is already installed in $HEXT_GUMBO_INSTALL_PATH"

gumbo_dl_url="https://github.com/google/gumbo-parser/archive/refs/tags/v${HEXT_GUMBO_VERSION}.tar.gz"

build_dir=$(mktemp -d)
echo $build_dir
cd "$build_dir"

curl -L -o gumbo.tar.gz "$gumbo_dl_url"

SHASUM=sha256sum
hash $SHASUM || SHASUM="shasum -a 256"

$SHASUM -c <(echo "$HEXT_GUMBO_SHA256  gumbo.tar.gz")

tar zxf gumbo.tar.gz
cd */

export CC=gcc CXX=g++
hash gcc-8 && export CC=gcc-8 CXX=g++-8
hash gcc-9 && export CC=gcc-9 CXX=g++-9
hash gcc-10 && export CC=gcc-10 CXX=g++-10
hash gcc-11 && export CC=gcc-11 CXX=g++-11
$CXX --version

./autogen.sh
CFLAGS="-fPIC" ./configure --enable-shared=no --prefix="$HEXT_GUMBO_INSTALL_PATH"
make -j$THREADS
make install

