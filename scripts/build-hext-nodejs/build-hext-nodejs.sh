#!/usr/bin/env bash

set -e

BUILDD=$(mktemp -d)
cd "$BUILDD"

apt-get update && apt-get upgrade -y
apt-get install -y build-essential cmake libgumbo-dev rapidjson-dev libboost-regex-dev libboost-program-options-dev git nodejs npm

git clone https://github.com/thomastrapp/hext.git
cd hext/libhext/build/
cmake -DBUILD_SHARED_LIBS=On ..
make -j4
make install

cd "$BUILDD"
cd hext/libhext/bindings/nodejs
npm install
npm run build

test/blackbox.js.sh ../../../../test/case/*hext

