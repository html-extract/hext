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


[[ $# -gt 1 ]] || {
  echo "Usage: $0 <dir-left> <dir-right>"
  echo
  echo "Recursively compares files from <dir-left> to the files from"
  echo "<dir-right> (similar to 'diff -qr')."
  echo "When comparing the contents all whitespace is removed."
  echo "Basically, this is an unsafe version of 'git diff -w'."
  echo "For example, the following is not considered a change:"
  echo "  'int a, b;'    vs.   'inta,b;'"
  echo "because the only characters removed are whitespace."
  echo
  echo "Will not work with spaces in filenames."
  echo "Exits with 1 if files differ."
  exit
}


left=$1
right=$2


# Rejects unreachable directories
[[ -d "$left" && -r "$left" ]] || {
  echo "Error: $left is not a directory or is not readable" >&2
  exit 1
}

[[ -d "$right" && -r "$right" ]] || {
  echo "Error: $right is not a directory or is not readable" >&2
  exit 1
}


# Rejects paths containing spaces.
for directory in "$left" "$right"
do
  case "$directory" in *\ *) {
    echo "Error: Eew! '${directory}' contains spaces. Bailing out." >&2
    exit 1
  } ;; esac
done


# Collects tuples of files that differ.
# --new-file: Treat absent files as empty
files=$(diff -qr --new-file "$left" "$right" | awk '{ print $2 "," $4 ; }')


exit_code=0
for pair in $files
do
  ORIGINAL_IFS=$IFS;
  IFS=",";
  # move pair.first to $1, pair.second to $2
  set $pair
  IFS=$ORIGINAL_IFS;

  fl="$1"
  fr="$2"

  for file in "$fl" "$fr"
  do
    [[ -r "$file" ]] || {
      echo "File $file does not exist"
      exit_code=1
    }
  done

  if [[ -r "$fl" && -r "$fr" ]]
  then
    # compare contents of files with deleted whitespace
    diff -q <(cat "$fl" | tr --delete '[:space:]')\
            <(cat "$fr" | tr --delete '[:space:]') > /dev/null || {
      echo "Files $fl and $fr differ"
      exit_code=1
    }
  fi
done


exit $exit_code

