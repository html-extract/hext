#!/usr/bin/env bash

set -e

perror_exit() { echo "$1" >&2 ; exit 1 ; }

[[ $# -eq 1 ]] || perror_exit "Usage: $0 <input.ronn>"
hash ronn >/dev/null 2>&1 || perror_exit "missing dependency 'ronn'"

ronn --organization="Thomas Trapp" --date "$(date '+%Y-%m-%d')" --manual=htmlext --pipe -w -r "$1"

