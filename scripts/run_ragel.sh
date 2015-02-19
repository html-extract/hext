#!/usr/bin/env bash

ragel="ragel"
script_name="$0"

assert_dependencies()
{
  # try to execute
  "$ragel" --help > /dev/null 2>&1 \
    || { echo >&2 "$script_name: cannot execute $ragel"; exit 1; }
 
  # check if input-file exists
  [ -f "$1" ] \
    || { echo >&2 "$script_name: $1 not found"; exit 1; }
}

print_usage()
{
  echo "Usage: $script_name [ragel-input-file.rl] [output-file]"
  echo "       Wrapper for ragel"
}

[ $# -eq 2 ] || { print_usage ; exit 0; }

assert_dependencies "$@"

ragel_input="$1"
ragel_output="$2"

"$ragel" -o  "$ragel_output" "$ragel_input"
ragel_exit=$?

if [ $ragel_exit -eq 0 ] ; then
  echo "$script_name: Generated '$ragel_output'"
else
  echo >&2 "$script_name: ragel failed"
fi

exit $ragel_exit

