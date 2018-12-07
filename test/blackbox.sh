#!/usr/bin/env bash

# Copyright 2015,2016 Thomas Trapp
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


[[ $# -lt 1 ]] && {
  echo "Usage: $0 <hext-file...>"
  echo
  cat <<HelpMessage | fold -s -w 78 | sed 's/^/  /'
$0 applies Hext snippets to HTML documents and compares the result to a third \
file that contains the expected output. For example, there is a test case \
icase-quoted-regex that consists of three files:
  icase-quoted-regex.hext
  icase-quoted-regex.html
  icase-quoted-regex.expected
To run this test case you would do the following:
  $ $0 case/icase-quoted-regex.hext

$0 will then look for the corresponding .html and .expected files of the same \
name in the directory of icase-quoted-regex.hext. Then it will invoke htmlext \
with the given Hext snippet and HTML document and compare the result to \
icase-quoted-regex.expected.

To run all blackbox tests in succession:
  $ $0 case/*.hext

By default $0 will look for the htmlext binary in \$PATH. Failing that, it \
looks for the binary in the default build directory. You can tell $0 which \
command to use by setting HTMLEXT.
For example, to run all tests through valgrind you'd run the following:
  $ HTMLEXT="valgrind -q htmlext" $0 case/*.hext
HelpMessage
  exit
}


# Assume this file's location in the project is /test
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

# The build directory for htmlext is expected in to be /build
BUILD_DIR=$((hash realpath 2> /dev/null) && realpath "${SCRIPT_DIR}/../build")

C_RED=$(tput setaf 1)
C_GRN=$(tput setaf 2)
C_BLD=$(tput bold)
C_RST=$(tput sgr0)

# Use colordiff, if available
DIFF="diff"
hash colordiff >/dev/null 2>&1 && DIFF="colordiff"


# Prints error message to stdout.
perror() {
  echo -e "${C_RED}${C_BLD}Error:${C_RST}" "$@"
}


# Prints a failed test case to stdout.
perror_case() {
  local case_name=${1:-"unknown"}
  echo "${C_RED}${C_BLD}✘ Test case <${case_name}>: Failure${C_RST}"
}


# Indents each line from stdin with two spaces and prints to stdout.
# The amount of spaces can be overridden by providing an argument
# greater than 0.
pindent() {
  local width=${1:-"2"}

  # hax: generate a string filled with $width amount of spaces
  local spaces=$(printf "%0.s " $(seq 1 "$width"))

  # insert spaces at the beginning of each line
  sed "s/^/${spaces}/" < /dev/stdin
}


# Prints a string that can be used to successfully invoke htmlext.
# If given an argument, it will be used as a directory in which to look
# for htmlext.
# Returns 0 if successful.
whereis_htmlext() {
  local htmlext="htmlext"

  # if a path was provided, use it
  [[ $# -gt 0 ]] && htmlext="${1}/${htmlext}"

  ${htmlext} --help >/dev/null 2>&1 && {
    echo "${htmlext}"
    return 0
  }

  return 1
}


# Only search for htmlext if HTMLEXT wasn't set by caller
if [[ -z "${HTMLEXT}" ]] ; then
  # Try to find htmlext, it may be located either in PATH, or in the build
  # directory.
  HTMLEXT=$(whereis_htmlext) || {
    if [[ -d "${BUILD_DIR}" ]]
    then
      HTMLEXT=$(whereis_htmlext "${BUILD_DIR}") || {
        perror "htmlext is neither in PATH" \
          "nor in the build directory (${BUILD_DIR})\n"\
          "Build htmlext and run $0 again"
        exit 1
      }
    else
      perror "htmlext is not in PATH" \
        "and the build directory was not found" \
        "(tried to access: ${BUILD_DIR})"
      exit 1
    fi
  } >&2
fi


# Run a hext test case.
# Expects a path to a file ending in hext, whose directory contains a
# file with the same name but ending in ".html", which will be passed
# to htmlext alongside the given hext file, and a file ending in
# ".expected", whose contents will be compared to the output of
# htmlext.
#
# Prints whether or not the test was successfull.
# Returns 0 on success.
#
# Example:
# $ ls case/nth-child.*
#   nth-child.expected
#   nth-child.hext
#   nth-child.html
# $ test_hext case/nth-child.hext
test_hext() {
  [[ $# -eq 1 ]] || {
    perror "missing parameter <hext-file>" >&2
    return 1
  }

  [[ "${1##*.}" == "hext" ]] || {
    perror_case "$1"
    perror "invalid format, expected <${1}.hext>" | pindent
    return 1
  } >&2

  local t_case="${1%.*}"
  local f_hext="$1"
  local f_html="${t_case}.html"
  local f_expe="${t_case}.expected"

  for f in "$f_hext" "$f_html" "$f_expe" ; do
    [[ -f "$f" && -r "$f" ]] || {
      perror_case "$t_case"
      perror "<$f> does not exist or is not readable" | pindent
      return 1
    } >&2
  done

  local actual
  actual=$($HTMLEXT "$f_hext" "$f_html") || {
    perror_case "$t_case"
    perror "$HTMLEXT failed for <$f_hext>" | pindent
    return 1
  } >&2
  actual=$(echo "$actual" | sort)

  local expect
  expect=$(sort "$f_expe")

  [[ "$actual" == "$expect" ]] || {
    perror_case "$t_case"

    echo "$DIFF <expected> <actual>:" | pindent
    $DIFF <(echo "$expect") <(echo "$actual") | pindent 4

    echo "See <$f_hext>, <$f_html> and <$f_expe>" | pindent

    return 1
  } >&2

  echo "${C_GRN}${C_BLD}✔ <${t_case}>${C_RST}"
  return 0
}


# Run a test for each parameter
failure=0
total=0
while [[ $# -gt 0 ]] ; do
  test_hext "$1" || {
    failure=$(expr $failure + 1)
    echo >&2
  }
  total=$(expr $total + 1)
  shift
done

echo
echo "$total tested, $failure failed"

exit $failure

