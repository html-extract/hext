#!/usr/bin/env bash

set -e

CMAKE_APP="/Applications/CMake.app/Contents/bin/cmake"
CMAKE_MAKE_FLAGS="-j2"

perror_exit() { echo "$1" >&2 ; exit 1 ; }

PYTHON_BUILDS_DIR="$HOME/python-build"
[[ -d "$PYTHON_BUILDS_DIR" ]] || perror_exit "cannot access python build directory (expected '$PYTHON_BUILDS_DIR')"
ASSETD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/assets"
[[ -d "$ASSETD" ]] || perror_exit "cannot access asset directory (expected '$ASSETD')"
OUTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/output"
[[ -d "$OUTD" ]] || perror_exit "cannot access output directory (expected '$OUTD')"

HEXTD=$(mktemp -d)
git clone "https://github.com/html-extract/hext.git" "$HEXTD"

LIBHEXTD="$HEXTD/libhext"
cd "$LIBHEXTD/test/build"
$CMAKE_APP -DBUILD_SHARED_LIBS=Off ..
make $CMAKE_MAKE_FLAGS
./libhext-test

cd "$HEXTD/build"
$CMAKE_APP -DBUILD_SHARED_LIBS=Off -DCMAKE_POSITION_INDEPENDENT_CODE=On -DCMAKE_EXE_LINKER_FLAGS=" -static-libgcc -static-libstdc++ " ..
make $CMAKE_MAKE_FLAGS
sudo make install

HTMLEXT="/usr/local/bin/htmlext" "$HEXTD/test/blackbox.sh" "$HEXTD/test/case/"*hext

PYTHOND="$LIBHEXTD/bindings/python"
cd "$PYTHOND"
for i in "$PYTHON_BUILDS_DIR/"cp* ; do
  V=$(basename $i)
  mkdir $V
  cd $V
  mkdir -p wheel/hext
  cp "$ASSETD/setup.py" "$ASSETD/README.md" "$ASSETD/MANIFEST.in" "$ASSETD/gumbo.license" "$ASSETD/rapidjson.license" wheel/

  PIP="$i/bin/pip"
  $PIP install -U setuptools wheel
  PYTHON_PATH=$(cd "$i/"include/*/ && pwd)
  $CMAKE_APP -DCMAKE_CXX_FLAGS=" -static-libgcc -static-libstdc++ -Wl,-undefined,dynamic_lookup " -DPYTHON_INCLUDE_DIR="$PYTHON_PATH" -DBUILD_SHARED_LIBS=On ..
  make $CMAKE_MAKE_FLAGS
  cp hext.py wheel/hext/__init__.py
  cp _hext.so wheel/hext

  mkdir wheel/bin
  cp /usr/local/bin/htmlext wheel/bin
  strip wheel/bin/htmlext

  cd wheel
  "$i/bin/python" setup.py bdist_wheel

  WHEEL=$(find . -iname "*.whl")
  [[ -f "$WHEEL" ]] || perror_exit "cannot find wheel (*.whl)"
  cp "$WHEEL" "$OUTD"
  cd ../..
done

