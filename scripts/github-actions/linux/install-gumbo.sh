#!/usr/bin/env bash

set -e
set -x

perror_exit() { echo "$1" >&2 ; exit 1 ; }

deps=(
  "HEXT_GUMBO_VERSION"
  "HEXT_GUMBO_SHA256"
  "HEXT_GUMBO_INSTALL_PATH"
)
for dep in "${deps[@]}" ; do
  [[ -z "${!dep}" ]] && perror_exit "missing env var '$dep'"
done

hash meson || perror_exit "missing dependency 'meson'"

[[ -f "$HEXT_GUMBO_INSTALL_PATH/include/gumbo.h" ]] \
  && perror_exit "gumbo is already installed in $HEXT_GUMBO_INSTALL_PATH"

gumbo_dl_url="https://codeberg.org/gumbo-parser/gumbo-parser/archive/${HEXT_GUMBO_VERSION}.tar.gz"

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
hash gcc-9 && export CC=gcc-9 CXX=g++-9
hash gcc-10 && export CC=gcc-10 CXX=g++-10
hash gcc-11 && export CC=gcc-11 CXX=g++-11
hash gcc-12 && export CC=gcc-12 CXX=g++-12
hash gcc-13 && export CC=gcc-13 CXX=g++-13
hash gcc-14 && export CC=gcc-14 CXX=g++-14
hash gcc-15 && export CC=gcc-15 CXX=g++-15
$CXX --version

meson_dir=$(mktemp -d)
meson setup "$meson_dir" -Dtests=false -Dc_args=-fPIC --prefix="$HEXT_GUMBO_INSTALL_PATH" -Ddefault_library=static
meson compile -C "$meson_dir"
meson install -C "$meson_dir"
