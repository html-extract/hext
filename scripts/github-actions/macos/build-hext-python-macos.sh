#!/usr/bin/env bash

set -e

CMAKE_MAKE_FLAGS="-j2"

perror_exit() { echo "$1" >&2 ; exit 1 ; }

[[ $# -lt 1 ]] && perror_exit "Usage: $0 <python-location>"
PYTHON_LOCATION="$1"

WHEEL_OUT="$( cd "$WHEEL_OUT" >/dev/null && pwd )"
[[ -d "$WHEEL_OUT" ]] || perror_exit "cannot access output directory (expected '$WHEEL_OUT')"

rm "$WHEEL_OUT/.gitignore" || true

HEXTD="$( pwd )"
ASSETD="$HEXTD/scripts/github-actions/pypi/assets"
[[ -d "$ASSETD" ]] || perror_exit "cannot access asset directory (expected '$ASSETD')"

LIBHEXTD="$HEXTD/libhext"
PYTHOND="$LIBHEXTD/bindings/python"
cd "$PYTHOND/build"
rm -rf * || true

mkdir -p wheel/hext
cp "$ASSETD/setup.py" "$ASSETD/README.md" "$ASSETD/MANIFEST.in" "$ASSETD/gumbo.license" "$ASSETD/rapidjson.license" wheel/

pip install -U setuptools wheel
PYTHON_INCLUDE_DIR=( "$PYTHON_LOCATION"/include/python* )
cmake \
  -DBUILD_SHARED_LIBS=On \
  -DCMAKE_POLICY_DEFAULT_CMP0074=NEW \
  -DBOOST_ROOT="$HEXT_BOOST_INSTALL_PATH" \
  -DBoost_USE_STATIC_RUNTIME=On \
  -DGumbo_ROOT="$HEXT_GUMBO_INSTALL_PATH" \
  -DPYTHON_INCLUDE_DIR="$PYTHON_INCLUDE_DIR" \
  -DPYTHON_LIBRARY="$PYTHON_LOCATION/lib" \
  -DCMAKE_CXX_FLAGS=" -Wl,-undefined,dynamic_lookup " ..
make $CMAKE_MAKE_FLAGS
cp hext.py wheel/hext/__init__.py
otool -L _hext.so
otool -l _hext.so
otool -l _hext.so | grep -EA7 '(LC_VERSION_MIN_MACOSX|LC_BUILD_VERSION)' || true
cp _hext.so wheel/hext

mkdir wheel/bin
cp /usr/local/bin/htmlext wheel/bin
otool -l /usr/local/bin/htmlext | grep -EA7 '(LC_VERSION_MIN_MACOSX|LC_BUILD_VERSION)' || true

cd wheel
python setup.py bdist_wheel

WHEEL=$(find . -iname "*.whl")
[[ -f "$WHEEL" ]] || perror_exit "cannot find wheel (*.whl)"


# Fix platform name manually
# Wheels will have names like
# hext-0.2.5-cp38-cp38-macosx_10_14_x86_64.whl
# when built on Mac OS 10.14.
# But the wheel is downwards compatible to $MACOSX_DEPLOYMENT_TARGET
WHEEL_COMPAT_NAME=$( \
  echo $WHEEL | \
  sed 's/macosx_[0-9]\{1,\}_[0-9]\{1,\}_/macosx_'${MACOSX_DEPLOYMENT_TARGET//./_}'_/' )
# Fix arch name if wrong platform tag 'universal'
WHEEL_ARCH=$(uname -m)
WHEEL_COMPAT_NAME=$( \
  echo $WHEEL_COMPAT_NAME | \
  sed 's/_universal[0-9]\{0,1\}.whl$/_'$WHEEL_ARCH'.whl/' )
mv "$WHEEL" "$WHEEL_COMPAT_NAME"
WHEEL="$WHEEL_COMPAT_NAME"


shasum -a 256 "$WHEEL"
cp -v "$WHEEL" "$WHEEL_OUT"

