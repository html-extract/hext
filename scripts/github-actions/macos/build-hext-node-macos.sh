#!/usr/bin/env bash

set -e

perror_exit() { echo "$1" >&2 ; exit 1 ; }

HEXTD="$( pwd )"
LIBHEXTD="$HEXTD/libhext"
OUTD="$( cd "$NODE_OUT" >/dev/null && pwd )"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$NODE_OUT')"


cd "$LIBHEXTD/bindings/nodejs"
npm install
npm install prebuild

# Fix for "node-abi@3.75.0, node-abi@4.8.0 ABI version mismatch for Node 24.0.0 (v134 vs v137)"
# https://github.com/electron/node-abi/issues/208
sed -i '' 's/"abi": "134"/"abi": "137"/' $(find . -wholename "*node-abi/abi_registry.json")

npx prebuild \
  -t "$HEXT_NODE_API_VERSION1" \
  -t "$HEXT_NODE_API_VERSION2" \
  -t "$HEXT_NODE_API_VERSION3" \
  -t "$HEXT_NODE_API_VERSION4" \
  --strip --verbose \
  --backend cmake-js \
  -- \
  --CDBUILD_SHARED_LIBS=On \
  --CDCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  --CDCMAKE_CXX_FLAGS=" -Wl,-undefined,dynamic_lookup " \
  --CDBoost_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  --CDGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  --CDBoost_USE_STATIC_LIBS=On \
  --CDBoost_USE_STATIC_RUNTIME=On \
  --CDCMAKE_BUILD_TYPE=Release


ls -1 prebuilds/


cd prebuilds
for i in *.tar.gz ; do
  tar xf "$i"
  otool -L build/Release/hext.node
  cp build/Release/hext.node "$OUTD/${i%%.tar.gz}.node"
done

