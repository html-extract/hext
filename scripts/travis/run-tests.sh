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
  bats jq curl build-essential libpcre3-dev wget python3-pip swig \
  cppcheck php-cli php-dev

curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash -
sudo apt-get install -y nodejs

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
pip3 --version
pip3 install pytest
PYTHONPATH=. pytest ../pytest

cd "$LIBHEXTBINDINGSD/php/build"
phpenv global system
cmake ..
make $MAKE_FLAGS
../test/blackbox.php.sh

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

