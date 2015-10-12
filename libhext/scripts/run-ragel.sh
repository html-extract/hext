#!/usr/bin/env bash

# Copyright 2015 Thomas Trapp
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


script_name=$(basename "$0")

assert_dependencies()
{
  # try to execute ragel
  ragel --help > /dev/null 2>&1 \
    || { echo >&2 "$script_name: cannot execute ragel"; exit 1; }

  # check if input-file exists
  [ -f "$1" ] \
    || { echo >&2 "$script_name: $1 not found"; exit 1; }

  # try to execute md5sum
  md5sum --help > /dev/null 2>&1 \
    || { echo >&2 "$script_name: cannot execute md5sum"; exit 1; }
}

print_usage()
{
  echo "Usage: $script_name [ragel-input-file.rl] [output-file]"
  echo "       Wrapper for ragel"
}

# For each filename given, compute md5sum. Return true if all files have same
# md5sum.
# Example: files_are_equal "/tmp/test1" "/tmp/test2" "/tmp/test3"
files_are_equal()
{
  # return false if not at least 2 filenames given
  [ "$#" -gt 1 ] || { return 1; }
  sum=""
  # for all arguments
  while (( "$#" )); do
    # abuse array access to get first column of md5sum's output
    this_sum=($(md5sum "$1"))
    # return false if md5sum fails
    [ $? ] || { return 1; }
    # return false if this_sum is not exactly 32 characters in length
    [ "${#this_sum}" -eq 32 ] || { return 1; }
    if [ "$sum" = "" ] ; then
      sum="$this_sum"
    elif [ "$sum" != "$this_sum" ] ; then
      return 1;
    fi
    shift
  done

  return 0
}

[ $# -eq 2 ] || { print_usage ; exit 0; }

assert_dependencies "$@"

ragel_input="$1"
ragel_output="$2"
basename_ragel_input=$(basename "$ragel_input")
basename_ragel_output=$(basename "$ragel_output")
dirname_ragel_input=$(dirname "$ragel_input")

# Ragel prints the full passed path into the generated files. We only want the
# filename.
cd "$dirname_ragel_input" || {
  echo >&2 "$script_name: failed changing directory to $dirname_ragel_input"
  exit 1
}

# We only want to write to $ragel_output if the file will actually change.
# Else cmake will recompile it everytime. Therefore we first write to a
# temporary, and then use md5sum to detect changes.
# We cannot use mktemp here, because ragel includes the filename in its
# output. mktemp will produce a new filename on every invocation, thus
# resulting in different outputs everytime we run ragel.
# (ragel 6.9 actually has a switch -L to "Inhibit writing of #line directives"
# but it is useless in this context, because the filename still gets written)
ragel_tmp="$basename_ragel_output.tmp"
[ ! -f "$ragel_tmp" ] || {
  echo >&2 "$script_name: cannot create temporary, file already exists. Please delete $ragel_tmp"
  exit 1
}

# run ragel
ragel -o "$ragel_tmp" "$basename_ragel_input"
ragel_exit=$?

if [ $ragel_exit -ne 0 ] ; then
  echo >&2 "$script_name: ragel failed"
  exit $ragel_exit
fi

trap 'rm "$ragel_tmp"' EXIT

# Prepend notice.
sed -i "1i // This file was generated from $basename_ragel_input." "$ragel_tmp"

if [ ! -f "$ragel_output" ] ; then
  cp "$ragel_tmp" "$ragel_output" || {
    echo >&2 "$script_name: failed creating $ragel_output";
    exit 1;
  }
  echo "$script_name: Created '$basename_ragel_output'"
elif files_are_equal "$ragel_tmp" "$ragel_output" ; then
  echo "$script_name: $basename_ragel_output still current"
else
  cp "$ragel_tmp" "$ragel_output" || {
    echo >&2 "$script_name: failed replacing $ragel_output";
    exit 1;
  }
  echo "$script_name: Replaced $basename_ragel_output with new version"
fi

