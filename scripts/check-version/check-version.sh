#!/usr/bin/env bash

set -e

perror_exit() { echo "$1" >&2 ; exit 1 ; }

HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../"
cd "$HEXTD"

GIT_TAG=$(git describe --abbrev=0 --tags)
htmlext --version \
  | head -n1 \
  | awk -F, '{ print $1 }' \
  | grep "htmlext $GIT_TAG" >/dev/null \
  || perror_exit "htmlext --version != $GIT_TAG"

htmlext --version \
  | grep -i 'linked with libhext' \
  | grep "libhext $GIT_TAG" >/dev/null \
  || perror_exit "libhext version != $GIT_TAG"

grep 'version=' scripts/github-actions/pypi/assets/setup.py \
  | grep "version='${GIT_TAG:1}'," >/dev/null \
  || perror_exit "pypi version != $GIT_TAG"

grep '"version":' scripts/github-actions/npm/assets/package.json \
  | awk -F\" '{ print $4 }' \
  | grep "1${GIT_TAG:1}" >/dev/null \
  || perror_exit "npm version != $GIT_TAG"

README_NODE_VERSIONS=$(grep 'Node v' README.md)
NPM_README_NODE_VERSIONS=$(grep 'Node v' scripts/github-actions/npm/assets/README.md)
WORKFLOW_NODE_RELEASES=$(grep \
  "^  HEXT_NODE_VERSION" .github/workflows/hext-releases.yml \
    | awk -F\" '{ print $2 }')
[[ "$WORKFLOW_NODE_RELEASES" == "" ]] \
  && perror_exit "cannot extract node releases from workflow"
for i in $WORKFLOW_NODE_RELEASES ; do
  [[ "$i" == "" ]] && perror_exit "unexpected format '$WORKFLOW_NODE_RELEASES'"
  echo "$NPM_README_NODE_VERSIONS" | grep "v$i" >/dev/null \
    || perror_exit "npm readme does not include node version '$i'"
  echo "$README_NODE_VERSIONS" | grep "v$i" >/dev/null \
    || perror_exit "toplevel readme does not include node version '$i'"
done

grep 'https://github.com/html-extract/hext/archive/v' README.md \
  | grep "$GIT_TAG" >/dev/null \
  || perror_exit "toplevel readme links to old archive"

