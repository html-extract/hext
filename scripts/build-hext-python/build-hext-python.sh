#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j3"

perror_exit() { echo "$1" >&2 ; exit 1 ; }

HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../"
[[ -d "$HEXTD/libhext" ]] || {
  HEXTD=$(mktemp -d)
  git clone "https://github.com/html-extract/hext.git" "$HEXTD"
}
ASSETD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/assets"
[[ -d "$ASSETD" ]] || perror_exit "cannot access asset directory (expected '$ASSETD')"
OUTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/output"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$OUTD')"

LIBHEXTD="$HEXTD/libhext"
cd "$LIBHEXTD/test/build"
cmake -DBUILD_SHARED_LIBS=Off -DBoost_USE_STATIC_LIBS=On -DBoost_USE_STATIC_RUNTIME=On ..
make $CMAKE_MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
cmake -DBUILD_SHARED_LIBS=Off -DBoost_USE_STATIC_LIBS=On -DBoost_USE_STATIC_RUNTIME=On -DCMAKE_POSITION_INDEPENDENT_CODE=On ..
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
  PYTHON_INCLUDE_DIR=$(readlink -f /opt/python/$V/include/python*/)
  PYTHON_LIBRARY=$(readlink -f /opt/python/$V/lib/python*/)
  cmake -DPYTHON_LIBRARY="$PYTHON_LIBRARY" -DPYTHON_INCLUDE_DIR="$PYTHON_INCLUDE_DIR" -DBUILD_SHARED_LIBS=On -DBoost_USE_STATIC_LIBS=On -DBoost_USE_STATIC_RUNTIME=On ..
  make $CMAKE_MAKE_FLAGS
  cp hext.py wheel/hext/__init__.py
  strip --strip-unneeded _hext.so
  cp _hext.so wheel/hext

  mkdir wheel/bin
  cp /usr/local/bin/htmlext wheel/bin
  strip --strip-unneeded wheel/bin/htmlext

  cd wheel
  /opt/python/$V/bin/python setup.py bdist_wheel

  WHEEL=$(find . -iname "*linux*.whl")
  [[ -f "$WHEEL" ]] || perror_exit "cannot find wheel (*linux*.whl)"
  MANYLINUX_WHEEL="$(echo $WHEEL | sed 's/linux/manylinux2014/')"
  mv "$WHEEL" "$MANYLINUX_WHEEL"

  cp "$MANYLINUX_WHEEL" "$OUTD"
  cd ../..
done
