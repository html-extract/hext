#!/usr/bin/env bash

set -e

perror_exit() { echo "$1" >&2 ; exit 1 ; }

: ${HTMLEXT:="htmlext"}
HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../"
cd "$HEXTD"

[[ "$GIT_TAG" != "" ]] || GIT_TAG=$(git describe --abbrev=0 --tags)
$HTMLEXT --version \
  | head -n1 \
  | awk -F, '{ print $1 }' \
  | grep "htmlext $GIT_TAG" >/dev/null \
  || perror_exit "htmlext --version != $GIT_TAG"

$HTMLEXT --version \
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
done

