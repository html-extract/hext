#!/usr/bin/env bash

set -e

HEXTD=$(readlink -f .)
LIBHEXTD="$HEXTD/libhext"
LIBHEXTTESTD="$HEXTD/libhext/test"
LIBHEXTEXAMPLESD="$HEXTD/libhext/examples"
LIBHEXTBINDINGSD="$HEXTD/libhext/bindings"

sudo apt-get -q update
sudo apt-get -q -y install cmake libgumbo-dev rapidjson-dev \
  libboost-regex-dev libboost-program-options-dev libgtest-dev \
  jq curl build-essential libpcre3-dev wget swig \
  cppcheck php-cli php-dev ruby ruby-dev

curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash -
sudo apt-get install -y nodejs

BATSD=$(mktemp -d)
cd "$BATSD"
BATS_RELEASE="v0.4.0.tar.gz"
wget "https://github.com/bats-core/bats-core/archive/$BATS_RELEASE"
sha256sum -c <(echo "e3b65b50a26e3f0c33b5d0a57d74101acf096e39473294d4840635ca6206fec7 $BATS_RELEASE")
tar xvf "$BATS_RELEASE"
cd */
sudo ./install.sh /usr/local

GTESTD=$(mktemp -d)
cd "$GTESTD"
cmake -H/usr/src/gtest/ -B.
make $MAKE_FLAGS
sudo cp $(find . -iname "*libgtest*.a") /usr/lib

cd "$LIBHEXTTESTD/build"
cmake -DCMAKE_BUILD_TYPE=Debug ..
make $MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=On ..
make $MAKE_FLAGS
sudo make install
sudo ldconfig

cd "$HEXTD"
cppcheck --version
cppcheck --quiet --error-exitcode=1 --enable=warning,portability\
  -I htmlext/htmlext/ build/Version.cpp
cppcheck --quiet --error-exitcode=1 --enable=warning,portability\
  -I htmlext/htmlext/ htmlext/main.cpp
cppcheck --quiet --error-exitcode=1 --enable=warning,portability\
  -I htmlext/htmlext/ htmlext/htmlext
cppcheck --quiet --error-exitcode=1 --enable=warning,portability\
  -I libhext/include build/libhext/Version.cpp
# false positive: [Parser.cpp.rl:372]: (error) Invalid number of character '{'
cppcheck --quiet --error-exitcode=1 --enable=warning,portability\
  -i libhext/src/Parser.cpp -I libhext/include libhext/src

cd "$LIBHEXTEXAMPLESD/build"
cmake -DCMAKE_BUILD_TYPE=Debug ..
make $MAKE_FLAGS
./mixed
./chaining-rules

cd "$HEXTD/test"
./blackbox.sh case/*hext

bats bats/htmlext.bats

cd "$LIBHEXTBINDINGSD/python/build"
cmake ..
make $MAKE_FLAGS
../test/blackbox.py.sh
pip --version
export PATH="/home/runner/.local/bin:$PATH"
pip install pytest
PYTHONPATH=. pytest ../pytest

cd "$LIBHEXTBINDINGSD/php/build"
cmake ..
make $MAKE_FLAGS
../test/blackbox.php.sh

cd "$LIBHEXTBINDINGSD/ruby/build"
cmake ..
make $MAKE_FLAGS
../test/blackbox.rb.sh

cd "$LIBHEXTBINDINGSD/nodejs"
# protect against CI env by prioritizing system installed node
export PATH="/usr/bin:$PATH"
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

