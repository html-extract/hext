#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j3"
THREADS=3

perror_exit() { echo "$1" >&2 ; exit 1 ; }

[[ $HEXT_MANYLINUX_VERSION == manylinux* ]] || perror_exit "unknown HEXT_MANYLINUX_VERSION '$HEXT_MANYLINUX_VERSION'"
HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../../"
ASSETD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../pypi/assets"
[[ -d "$ASSETD" ]] || perror_exit "cannot access asset directory (expected '$ASSETD')"
OUTD="$( cd "$WHEEL_OUT" >/dev/null && pwd )/"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$WHEEL_OUT')"

[[ -d "$HEXTD/libhext" ]] || {
  HEXTD=$(mktemp -d)
  git clone "https://github.com/html-extract/hext.git" "$HEXTD"
}

LIBHEXTD="$HEXTD/libhext"
cd "$LIBHEXTD/test/build"
CMAKE_PREFIX_PATH="$HEXT_BOOST_INSTALL_PATH:$HEXT_GUMBO_INSTALL_PATH" cmake \
  -DBUILD_SHARED_LIBS=Off \
  -DCMAKE_BUILD_TYPE=Release \
  ..
make $CMAKE_MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
CMAKE_PREFIX_PATH="$HEXT_BOOST_INSTALL_PATH:$HEXT_GUMBO_INSTALL_PATH" cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=Off \
  -DBoost_USE_STATIC_LIBS=On \
  -DBoost_USE_STATIC_RUNTIME=On \
  -DCMAKE_POSITION_INDEPENDENT_CODE=On \
  -DCMAKE_EXE_LINKER_FLAGS=" -static-libgcc -static-libstdc++ " \
  ..
make $CMAKE_MAKE_FLAGS
make install

PYTHOND="$LIBHEXTD/bindings/python"
cd "$PYTHOND"
for i in /opt/python/cp* ; do
  V=$(basename $i)
  mkdir $V
  cd $V
  mkdir -p wheel/hext
  cp "$ASSETD/setup.py" "$ASSETD/README.md" "$ASSETD/MANIFEST.in" "$ASSETD/gumbo.license" "$ASSETD/rapidjson.license" wheel/

  PIP=$(readlink -f /opt/python/$V/bin/pip)
  $PIP install -U setuptools wheel
  HEXT_PYTHON_PREFIX=$(readlink -f /opt/python/$V/)
  CMAKE_PREFIX_PATH="$HEXT_PYTHON_PREFIX:$HEXT_BOOST_INSTALL_PATH:$HEXT_GUMBO_INSTALL_PATH" cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=On \
    -DCMAKE_CXX_FLAGS=" -static-libgcc -static-libstdc++ " ..
  make $CMAKE_MAKE_FLAGS
  cp hext.py wheel/hext/__init__.py
  strip --strip-unneeded _hext.so
  cp _hext.so wheel/hext

  mkdir wheel/bin
  cp /usr/local/bin/htmlext wheel/bin
  strip --strip-unneeded wheel/bin/htmlext

  cd wheel
  /opt/python/$V/bin/python -m build --wheel

  WHEEL=$(find . -iname "*linux*.whl")
  [[ -f "$WHEEL" ]] || perror_exit "cannot find wheel (*linux*.whl)"
  MANYLINUX_WHEEL="$(echo $WHEEL | sed "s/linux/$HEXT_MANYLINUX_VERSION/")"
  mv "$WHEEL" "$MANYLINUX_WHEEL"

  cp "$MANYLINUX_WHEEL" "$OUTD"
  cd ../..
done
