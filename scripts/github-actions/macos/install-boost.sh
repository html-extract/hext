#!/usr/bin/env bash

set -e
set -x

perror_exit() { echo "$1" >&2 ; exit 1 ; }

THREADS=2

deps=(
  "HEXT_BOOST_VERSION"
  "HEXT_BOOST_SHA256"
  "HEXT_BOOST_INSTALL_PATH"
  "MACOSX_DEPLOYMENT_TARGET"
)
for dep in "${deps[@]}" ; do
  [[ -z "${!dep}" ]] && perror_exit "missing env var '$dep'"
done

[[ -f "$HEXT_BOOST_INSTALL_PATH/include/boost/version.hpp" ]] \
  && perror_exit "boost is already installed in $HEXT_BOOST_INSTALL_PATH"

boost_dl_url="https://boostorg.jfrog.io/artifactory/main/release/${HEXT_BOOST_VERSION}/source/boost_${HEXT_BOOST_VERSION//./_}.tar.gz"

build_dir=$(mktemp -d)
echo $build_dir
cd "$build_dir"

curl -L -o boost.tar.gz "$boost_dl_url"
shasum -a 256 -c <(echo "$HEXT_BOOST_SHA256  boost.tar.gz")

tar zxf boost.tar.gz
cd */

./bootstrap.sh --with-libraries=regex,program_options
./b2 -j$THREADS --prefix="$HEXT_BOOST_INSTALL_PATH" cxxflags="-fPIC" runtime-link=static variant=release link=static install

ls -lah "$HEXT_BOOST_INSTALL_PATH"

file "$HEXT_BOOST_INSTALL_PATH/lib/libboost_regex.a"
otool -l "$HEXT_BOOST_INSTALL_PATH/lib/libboost_regex.a" | grep -EA7 '(LC_VERSION_MIN_MACOSX|LC_BUILD_VERSION)'
file "$HEXT_BOOST_INSTALL_PATH/lib/libboost_program_options.a"
otool -l "$HEXT_BOOST_INSTALL_PATH/lib/libboost_program_options.a" | grep -EA7 '(LC_VERSION_MIN_MACOSX|LC_BUILD_VERSION)'

