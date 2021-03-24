#!/usr/bin/env bash

set -euf -o pipefail

download_and_verify() {
  curl -vL -o "$1" "$2"
  echo "$3  $1" | sha256sum -c || {
    echo "Error: invalid checksum for $1, expected $3"
    exit 1
  } > /dev/stderr
}

download_and_verify \
  "boost_1_75_0.tar.gz" \
  "https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz" \
  "aeb26f80e80945e82ee93e5939baebdca47b9dee80a07d3144be1e1a6a66dd6a"

download_and_verify \
  "gumbo-parser-v0.10.1.tar.gz" \
  "https://github.com/google/gumbo-parser/archive/refs/tags/v0.10.1.tar.gz" \
  "28463053d44a5dfbc4b77bcf49c8cee119338ffa636cc17fc3378421d714efad"
