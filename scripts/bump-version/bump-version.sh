#!/usr/bin/env bash

set -e
set -o pipefail

perror_exit() { echo "Error: $1" >&2 ; exit 1 ; }

[[ $# -lt 1 ]] && perror_exit "Usage: $0 <new-version>"

new_version="$1"
[[ -z "$new_version" ]] && perror_exit "<new-version> is empty"

hext_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/../../"
cd "$hext_dir"

htmlext_cmake=CMakeLists.txt
sed -Ei "s/^(project[(]htmlext VERSION )[0-9.]+([)])$/\1$new_version\2/" "$htmlext_cmake"
cat "$htmlext_cmake" \
  | grep "VERSION" \
  | grep "$new_version" >/dev/null \
  || perror_exit "failed setting version in $htmlext_cmake"

libhext_cmake=libhext/CMakeLists.txt
sed -Ei "s/^(project[(]Hext VERSION )[0-9.]+([)])$/\1$new_version\2/" "$libhext_cmake"
cat "$libhext_cmake" \
  | grep "VERSION" \
  | grep "$new_version" >/dev/null \
  || perror_exit "failed setting version in $libhext_cmake"

pypi_setup=scripts/github-actions/pypi/assets/setup.py
sed -Ei "s/^(    version=')[0-9.]+(',)$/\1$new_version\2/" "$pypi_setup"
cat "$pypi_setup" \
  | grep "version=" \
  | grep "$new_version" >/dev/null \
  || perror_exit "failed setting version in $pypi_setup"

npm_package=scripts/github-actions/npm/assets/package.json
sed -Ei 's/^(  "version": "1)[0-9.]+(",)$/\1'"$new_version"'\2/' "$npm_package"
cat "$npm_package" \
  | grep '"version":' \
  | grep "$new_version" >/dev/null \
  || perror_exit "failed setting version in $npm_package"

cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=On .. && make -j16
cd ..

HTMLEXT="./build/htmlext" ./scripts/check-version/check-version.sh

git --no-pager diff --unified=0 "$htmlext_cmake" "$libhext_cmake" "$pypi_setup" "$npm_package"

