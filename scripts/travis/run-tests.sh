#!/usr/bin/env bash

set -e

MAKE_FLAGS="-j2"

hash sudo >/dev/null 2>&1 || {
  apt-get update -q
  apt-get install -y sudo software-properties-common
}

hash apt-add-repository >/dev/null 2>&1 || {
  apt-get update -q
  apt-get install -y software-properties-common
}

[[ -d libhext ]] || {
  apt-get install -y git
  TMPD=$(mktemp -d)
  git clone https://github.com/thomastrapp/hext.git "$TMPD"
  cd "$TMPD"
}

sudo apt-add-repository -y "ppa:ubuntu-toolchain-r/test"
sudo apt-get -q update
sudo apt-get -q -y install gcc-8 g++-8 cmake libgumbo-dev rapidjson-dev \
  libboost-regex-dev libboost-program-options-dev libgtest-dev bats jq curl \
  swig ruby ruby-dev
curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash -
sudo apt-get install -y nodejs

export CC=/usr/bin/gcc-8 CXX=/usr/bin/g++-8

HEXTD=$(readlink -f .)
LIBHEXTD="$HEXTD/libhext"
LIBHEXTTESTD="$HEXTD/libhext/test"
LIBHEXTEXAMPLESD="$HEXTD/libhext/examples"
LIBHEXTBINDINGSD="$HEXTD/libhext/bindings"

GTESTD=$(mktemp -d)
cd "$GTESTD"
cmake -H/usr/src/gtest/ -B.
make $MAKE_FLAGS
sudo cp *.a /usr/lib

cd "$LIBHEXTTESTD/build"
cmake -DCMAKE_BUILD_TYPE=Debug ..
make $MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=On ..
make $MAKE_FLAGS
sudo make install
sudo ldconfig

cd "$LIBHEXTEXAMPLESD/build"
cmake -DCMAKE_BUILD_TYPE=Debug ..
make $MAKE_FLAGS
./mixed
./chaining-rules

cd "$HEXTD/test"
./blackbox.sh case/*hext

bats bats/htmlext.bats

cd "$LIBHEXTBINDINGSD/ruby/build"
cmake ..
make $MAKE_FLAGS
../test/blackbox.rb.sh

cd "$LIBHEXTBINDINGSD/nodejs"
npm install
npx -s /bin/bash cmake-js --runtime=node --runtime-version=12.0.0 build
./test/blackbox.js.sh

echo
echo "### Testing 'npm install hext'"
cd "$HEXTD/test"
cp "$LIBHEXTBINDINGSD/nodejs/htmlext.js" .
echo
# make sure that hext is not available yet
echo "### This error is deliberate:"
node ./htmlext.js && exit 2
npm install hext
node ./htmlext.js
HTMLEXT="node ./htmlext.js" ./blackbox.sh case/*hext

