#!/usr/bin/env bash

set -e
set -x

perror_exit() { echo "$1" >&2 ; exit 1 ; }

THREADS=2

deps=(
  "HEXT_GUMBO_VERSION"
  "HEXT_GUMBO_SHA256"
  "HEXT_GUMBO_INSTALL_PATH"
  "MACOSX_DEPLOYMENT_TARGET"
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
shasum -a 256 -c <(echo "$HEXT_GUMBO_SHA256  gumbo.tar.gz")

tar zxf gumbo.tar.gz
cd */

./autogen.sh
CFLAGS="-fPIC" ./configure --enable-shared=no --prefix="$HEXT_GUMBO_INSTALL_PATH"
make -j$THREADS
make install

ls -lah "$HEXT_GUMBO_INSTALL_PATH"

file "$HEXT_GUMBO_INSTALL_PATH/lib/libgumbo.a"
otool -l "$HEXT_GUMBO_INSTALL_PATH/lib/libgumbo.a" | grep -EA7 '(LC_VERSION_MIN_MACOSX|LC_BUILD_VERSION)'

