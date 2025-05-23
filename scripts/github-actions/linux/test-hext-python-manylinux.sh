#!/usr/bin/env bash

set -e

perror_exit() { echo "$1" >&2 ; exit 1 ; }

[[ $HEXT_MANYLINUX_VERSION == manylinux* ]] || perror_exit "unknown HEXT_MANYLINUX_VERSION '$HEXT_MANYLINUX_VERSION'"
USE_PYPI=false
[[ $# -eq 1 && "$1" == "use_pypi" ]] && USE_PYPI=true

[[ "$USE_PYPI" = true ]] || {
  WHEELD="$( cd "$WHEEL_OUT" >/dev/null && pwd )/"
  [[ -d "$WHEELD" ]] || perror_exit "cannot access wheels directory (expected '$WHEEL_OUT')"
}

HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../../"
[[ -d "$HEXTD/libhext" ]] || {
  HEXTD=$(mktemp -d)
  git clone "https://github.com/html-extract/hext.git" "$HEXTD"
}

HTMLEXTPY="$HEXTD/libhext/bindings/python/htmlext.py"
[[ -f "$HTMLEXTPY" ]] || perror_exit "cannot access htmlext.py (expected '$HTMLEXTPY')"
BLACKBOXSH="$HEXTD/test/blackbox.sh"
[[ -f "$BLACKBOXSH" ]] || perror_exit "cannot access blackbox.sh (expected '$BLACKBOXSH')"
BLACKBOXCASED="$HEXTD/test/case"
[[ -d "$BLACKBOXCASED" ]] || perror_exit "cannot access blackbox test case directory (expected '$BLACKBOXCASED')"

WHEEL_ARCH="$(uname -m)"
for i in /opt/python/cp* ; do
  V=$(basename $i)
  [[ "$V" == *t ]] && continue
  PIP=$(readlink -f /opt/python/$V/bin/pip)
  if [[ "$USE_PYPI" = true ]] ; then
    WHEEL="hext"
  else
    WHEEL=$(readlink -f "$WHEELD"/hext-*.*.*-"$V"-"$HEXT_MANYLINUX_VERSION"_"$WHEEL_ARCH".whl)
  fi
  $PIP install "$WHEEL"
done

PYTESTD="$HEXTD/libhext/bindings/python/pytest"
for i in /opt/python/cp* ; do
  V=$(basename $i)
  [[ "$V" == *t ]] && continue
  PIP=$(readlink -f /opt/python/$V/bin/pip)
  $PIP install pytest

  PYTHON="$(readlink -f /opt/python/$V/bin/python)"
  HTMLEXT="$PYTHON $HTMLEXTPY" "$BLACKBOXSH" "$BLACKBOXCASED"/*hext
  STATICHTMLEXT="$(readlink -f /opt/python/$V/bin/htmlext)"
  HTMLEXT="$STATICHTMLEXT" "$BLACKBOXSH" "$BLACKBOXCASED"/*hext

  PYTEST="$(readlink -f /opt/python/$V/bin/pytest)"
  $PYTEST "$PYTESTD"
done

