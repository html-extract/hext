#!/usr/bin/env bats

# Copyright 2016 Thomas Trapp
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


# Only use htmlext from PATH if HTMLEXT wasn't set by caller
if [[ -z "${HTMLEXT}" ]] ; then
  if hash htmlext 2>/dev/null
  then
    HTMLEXT="htmlext"
  else
    echo "Error: htmlext is not in PATH. Either install htmlext or set the"\
         "environment variable HTMLEXT to the path of the htmlext binary." >&2
    exit 1
  fi
fi


@test "--version" {
  run "${HTMLEXT}" -V
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" --version
  [ "$status" -eq 0 ]
}

@test "--help" {
  run "${HTMLEXT}" -h
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" --help
  [ "$status" -eq 0 ]
}

@test "--lint" {
  run "${HTMLEXT}" -l
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" --lint
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" -l -s "<a />"
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" -l -s "<a @err />"
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" --lint -s "<a />"
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" -l -x <(echo "<a />")
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" -l -x <(echo "<a />") -s "<b />"
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" -l -x <(echo "<a />") -s "<b @err />"
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" -l -s "<b @err />" -x <(echo "<a />")
  [ "$status" -eq 1 ]
}

@test "--filter" {
  run "${HTMLEXT}" -f
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" --filter
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" -s "<b @text:x />" -i <(echo "<b>bla</b>") -f
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" -s "<b @text:x />" -i <(echo "<b>bla</b>") -f x
  [ "$status" -eq 0 ]
  [ "$output" = "bla" ]
  run "${HTMLEXT}" -s "<b @text:x />" -i <(echo "<b>bla</b>") --filter x
  [ "$status" -eq 0 ]
  [ "$output" = "bla" ]
}

@test "--pretty" {
  run "${HTMLEXT}" -p
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" --pretty
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" -p -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "3" ]
  run "${HTMLEXT}" -p -c -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "3" ]
  run "${HTMLEXT}" -c -p -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "3" ]
  run "${HTMLEXT}" -a -p -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "5" ]
}

@test "--compact" {
  run "${HTMLEXT}" -c
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" --compact
  [ "$status" -eq 1 ]

  # the number of lines will always be 1, because htmlext detects that the
  # output is not a tty and will enable --compact automatically.
  run "${HTMLEXT}" -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "1" ]
  orig_outp="$output"
  run "${HTMLEXT}" -c -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "$output" = "$orig_outp" ]
  [ "${#lines[@]}" = "1" ]
  run "${HTMLEXT}" -a -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "1" ]
  run "${HTMLEXT}" -a -c -s "<b @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  [ "${#lines[@]}" = "1" ]
}

@test "--array (requires jq)" {
  run "${HTMLEXT}" -a
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" --array
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" -a -s "<b @text:x @text:y />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  array_length=$(echo "$output" | jq '. | length')
  [ "$array_length" = "1" ]
}

@test "no arguments" {
  run "${HTMLEXT}"
  [ "$status" -eq 1 ]
}

@test "positional arguments" {
  run "${HTMLEXT}" <(echo "<a />")
  [ "$status" -eq 1 ]
  run "${HTMLEXT}" <(echo "<a />") <(echo "<a></a>")
  [ "$status" -eq 0 ]
  run "${HTMLEXT}" -f x <(echo "<b @text:x />") <(echo "<b>aaa</b>")
  [ "$status" -eq 0 ]
  [ "$output" = "aaa" ]
  run "${HTMLEXT}" -f x <(echo "<b @text:x />") \
                        <(echo "<b>aaa</b>") \
                        <(echo "<b>bbb</b>")
  [ "$status" -eq 0 ]
  [ "${lines[0]}" = "aaa" ]
  [ "${lines[1]}" = "bbb" ]
  run "${HTMLEXT}" -f x <(echo "<b @text:x />") \
                        <(echo "<b>aaa</b>") \
                        <(echo "<b>bbb</b>") \
                        <(echo "<b>ccc</b>")
  [ "$status" -eq 0 ]
  [ "${lines[0]}" = "aaa" ]
  [ "${lines[1]}" = "bbb" ]
  [ "${lines[2]}" = "ccc" ]
}

@test "duplicate capture becomes array (requires jq)" {
  run "${HTMLEXT}" -s "<b @text:x @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  array_length=$(echo "$output" | jq '.x | length')
  [ "$array_length" = "2" ]
  run "${HTMLEXT}" -s "<b @text:x @text:x @text:x />" -i <(echo "<b>bla</b>")
  [ "$status" -eq 0 ]
  array_length=$(echo "$output" | jq '.x | length')
  [ "$array_length" = "3" ]
}

