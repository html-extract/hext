#!/usr/bin/env bash

set -e

BUILDD=$(mktemp -d)
cd "$BUILDD"

apt-get update && apt-get upgrade -y
apt-get install -y build-essential cmake libgumbo-dev rapidjson-dev libboost-regex-dev libboost-program-options-dev swig git php-cli php-dev

git clone https://github.com/html-extract/hext.git
cd hext/libhext/build/
cmake -DBUILD_SHARED_LIBS=On ..
make -j4
make install

cd "$BUILDD"
cd hext/libhext/bindings/php/build
cmake ..
make -j4

../test/blackbox.php.sh

