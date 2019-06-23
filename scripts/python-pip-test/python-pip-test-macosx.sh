#!/usr/bin/env bash

set -e
set -x

perror_exit() { echo "$1" >&2 ; exit 1 ; }

USE_PYPI=false
[[ $# -eq 1 && "$1" == "use_pypi" ]] && USE_PYPI=true

[[ "$USE_PYPI" = true ]] || {
  WHEELD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/wheels"
  [[ -d "$WHEELD" ]] || perror_exit "cannot access wheels directory (expected '$WHEELD')"
}

HEXTD=$(mktemp -d)
git clone "https://github.com/html-extract/hext.git" "$HEXTD"

HTMLEXTPY="$HEXTD/libhext/bindings/python/htmlext.py"
[[ -f "$HTMLEXTPY" ]] || perror_exit "cannot access htmlext.py (expected '$HTMLEXTPY')"
BLACKBOXSH="$HEXTD/test/blackbox.sh"
[[ -f "$BLACKBOXSH" ]] || perror_exit "cannot access blackbox.sh (expected '$BLACKBOXSH')"
BLACKBOXCASED="$HEXTD/test/case"
[[ -d "$BLACKBOXCASED" ]] || perror_exit "cannot access blackbox test case directory (expected '$BLACKBOXCASED')"


PYTHON_BUILDS_DIR="$HOME/python-build"
[[ -d "$PYTHON_BUILDS_DIR" ]] || perror_exit "cannot access python build directory (expected '$PYTHON_BUILDS_DIR')"
for i in "$PYTHON_BUILDS_DIR/"cp* ; do
  V=$(basename $i)

  PIP="$i/bin/pip"
  if [[ "$USE_PYPI" = true ]] ; then
    WHEEL="hext"
  else
    WHEEL="$WHEELD"/hext-?.?.?-"$V"-*.whl
  fi
  $PIP install $WHEEL
done


PYTESTD="$HEXTD/libhext/bindings/python/pytest"
for i in "$PYTHON_BUILDS_DIR/"cp* ; do
  V=$(basename $i)

  PIP="$i/bin/pip"
  $PIP install pytest

  PYTHON="$i/bin/python"
  HTMLEXT="$PYTHON $HTMLEXTPY" "$BLACKBOXSH" "$BLACKBOXCASED"/*hext
  STATICHTMLEXT="$i/bin/htmlext"
  HTMLEXT="$STATICHTMLEXT" "$BLACKBOXSH" "$BLACKBOXCASED"/*hext

  PYTEST="$i/bin/pytest"
  $PYTEST "$PYTESTD"
done

