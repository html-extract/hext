#!/usr/bin/env bash

set -e

perror_exit() { echo "$0: $1" >&2 ; exit 1 ; }

: ${HTMLEXT:="htmlext"}
HEXTD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/../../"
cd "$HEXTD"

ACTUAL_VERSION="v$(
  ( grep 'project(htmlext VERSION ' CMakeLists.txt | grep -oP '\d+.\d+.\d+' ) \
  || perror_exit "failed to extract version from top-level CMakeLists.txt")"

$HTMLEXT --version \
  | head -n1 \
  | awk -F, '{ print $1 }' \
  | grep "htmlext $ACTUAL_VERSION" >/dev/null \
  || perror_exit "htmlext --version != $ACTUAL_VERSION"

$HTMLEXT --version \
  | grep -i 'linked with libhext' \
  | grep "libhext $ACTUAL_VERSION" >/dev/null \
  || perror_exit "libhext version != $ACTUAL_VERSION"

grep 'version=' scripts/github-actions/pypi/assets/setup.py \
  | grep "version='${ACTUAL_VERSION:1}'," >/dev/null \
  || perror_exit "pypi version != $ACTUAL_VERSION"

grep '"version":' scripts/github-actions/npm/assets/package.json \
  | awk -F\" '{ print $4 }' \
  | grep "1${ACTUAL_VERSION:1}" >/dev/null \
  || perror_exit "npm version != $ACTUAL_VERSION"

NPM_README_NODE_VERSIONS=$(grep 'Node v' scripts/github-actions/npm/assets/README.md)
NPM_PJSON_NODE_VERSIONS=$(grep 'engines' scripts/github-actions/npm/assets/package.json)
WORKFLOW_NODE_RELEASES=$(grep \
  "^  HEXT_NODE_VERSION" .github/workflows/hext-releases.yml \
    | awk -F\" '{ print $2 }')
[[ "$WORKFLOW_NODE_RELEASES" == "" ]] \
  && perror_exit "failed to extract node releases from workflow"
for i in $WORKFLOW_NODE_RELEASES ; do
  [[ "$i" == "" ]] && perror_exit "unexpected format '$WORKFLOW_NODE_RELEASES'"
  echo "$NPM_README_NODE_VERSIONS" | grep "v$i" >/dev/null \
    || perror_exit "npm readme does not include node version '$i'"
  echo "$NPM_PJSON_NODE_VERSIONS" | grep "\^$i" >/dev/null \
    || perror_exit "npm package.json does not include node version '$i'"
done

