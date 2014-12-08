#!/usr/bin/env bash

ragel="ragel"
ragel_file="lexer.rl"
ragel_output="lexer.h"

assert_dependencies()
{
  # try to execute
  "$ragel" --help > /dev/null 2>&1 \
    || { echo >&2 "cannot execute $ragel"; exit 1; }
 
  # check if a directory was passed
  [ -d "$1" ] \
    || { echo >&2 "project root not found"; exit 1; } 

  # check if src directory exists
  [ -d "$1/src" ] \
    || { echo >&2 "src directory not found"; exit 1; } 
  
  # check if src/hext directory exists
  [ -d "$1/src/hext" ] \
    || { echo >&2 "hext directory not found"; exit 1; } 
  
  # check if ragel_file exists
  [ -f "$1/src/hext/$ragel_file" ] \
    || { echo >&2 "$ragel_file not found"; exit 1; } 
}

print_usage()
{
  echo "Usage:" "$0" "[path to project root]"
  echo "       Wrapper for ragel"
}

[ $# -eq 1 ] || { print_usage ; exit 0; }

assert_dependencies $1

# change directory to have consistent #line directives (they 
# contain the path to the file)
cd "$1/src" || { echo >&2 "failed to cd into src directory"; exit 1; }

path="hext/"
options=" -o $path$ragel_output $path$ragel_file"

"$ragel" $options
exit $?

