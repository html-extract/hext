#!/usr/bin/env bash

set -e


perror_exit() { echo "$1" >&2 ; exit 1 ; }


[[ $# -lt 2 ]] && {
  echo "Usage: $0 <output-package-directory> <binary-modules.node...>"
  exit
}


ASSETD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/assets"
[[ -d "$ASSETD" ]] || perror_exit "cannot access assets directory (expected '$ASSETD')"


get_identifier() {
  # example: hext-v0.2.0-node-v64-linux-x64.node
  #          ^1   ^2     ^3   ^4  ^5    ^6
  echo "${1%%.node}" | cut -d- -f"$2"
}
get_platform() { get_identifier "$1" 5; }
get_arch() { get_identifier "$1" 6; }
get_abi_version() { get_identifier "$1" 4; }
get_runtime() { get_identifier "$1" 3; }


add_module_to_package() {
  [[ -f "$1" && -r "$1" ]] || perror_exit "<$1> does not exist or is not readable"

  fname=$(basename "$1")
  [[ "${fname##*.}" == "node" ]] || perror_exit "<$1> has unknown file extension, expected 'node'"

  local platform=$(get_platform "$fname")
  [[ ! -z "$platform" ]] || perror_exit "cannot extract platform from <$1>"

  local arch=$(get_arch "$fname")
  [[ ! -z "$arch" ]] || perror_exit "cannot extract architecture from <$1>"

  local abi_version=$(get_abi_version "$fname")
  [[ ! -z "$abi_version" ]] || perror_exit "cannot extract abi version from <$1>"

  local runtime=$(get_runtime "$fname")
  [[ ! -z "$runtime" ]] || perror_exit "cannot extract runtime from <$1>"

  local target_dir="$OUTD/lib/${platform}-${arch}/${runtime}/${abi_version}"
  [[ -d "$target_dir" ]] || mkdir -p "$target_dir"

  cp "$1" "$target_dir/hext.node"
}


OUTD="$1"
[[ -d "$OUTD" ]] || mkdir "$OUTD"
shift


cp "$ASSETD"/* "$OUTD/"
while [[ $# -gt 0 ]] ; do
  add_module_to_package "$1"
  shift
done

find "$OUTD"

