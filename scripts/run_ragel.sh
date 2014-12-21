#!/usr/bin/env bash

ragel="ragel"
error_origin="$0"

assert_dependencies()
{
  # try to execute
  "$ragel" --help > /dev/null 2>&1 \
    || { echo >&2 "$error_origin: cannot execute $ragel"; exit 1; }
 
  # check if input-file exists
  [ -f "$1" ] \
    || { echo >&2 "$error_origin: $1 not found"; exit 1; }
}

print_usage()
{
  echo "Usage: $error_origin [ragel-input-file.rl] [output-file]"
  echo "       Wrapper for ragel"
}

[ $# -eq 2 ] || { print_usage ; exit 0; }

assert_dependencies $1 $2

ragel_input="$1"
ragel_output="$2"

"$ragel" -o  "$ragel_output" "$ragel_input"
ragel_exit=$?

if [ $ragel_exit -eq 0 ] ; then
  echo "Generated '$ragel_output'"
else
  echo >&2 "$error_origin: ragel failed"
fi

exit $ragel_exit

