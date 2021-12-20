#!/usr/bin/env bash

set -e
set -o pipefail

: ${REPOSITORY:="html-extract/hext"}
: ${WORKFLOW_NAME:="Hext Releases"}

perror_exit() { echo "Error: $1" >&2 ; exit 1 ; }
j() { echo "$1" | jq -r "$2" ; }

run=$(curl -s https://api.github.com/repos/html-extract/hext/actions/runs \
  | jq -c '.workflow_runs
             | sort_by(.created_at)
             | .[]
             | select(.name=="'"$WORKFLOW_NAME"'")
             | select(.status=="completed")' \
  | tail -n 1)

head_local=$(git rev-parse HEAD)
head_run=$(j "$run" .head_commit.id)
[[ "$head_local" == "$head_run" ]] \
  || perror_exit "local head != run head ($head_local != $head_run)"

tag_local=$(git describe --abbrev=0 --tags)
tag_remote=$(curl -s https://api.github.com/repos/html-extract/hext/tags \
  | jq -r '.[0].name')
[[ "$tag_local" == "$tag_remote" ]] \
  || perror_exit "local tag != remote tag ($tag_local != $tag_remote)"

../check-version/check-version.sh

run_id=$(j "$run" .id)
artifacts_url="https://api.github.com/repos/html-extract/hext/actions/runs/$run_id/artifacts"
artifacts=$(curl -s "$artifacts_url" \
  | jq -c '.artifacts[]
            | select(.expired == false)
            | [.name,.archive_download_url]')

[[ -z "$artifacts_dir" ]] && artifacts_dir=$(mktemp -d -p . artifacts.XXXXXXXXXX)
for artifact in $artifacts ; do
  artifact_name="$(j "$artifact" '.[0]')"
  path="$artifacts_dir/$artifact_name.zip"
  output_path="$artifacts_dir/$artifact_name"
  url="$(j "$artifact" '.[1]')"
  [[ -f "$path" ]] || {
    [[ -z "$auth" ]] \
      && read -p "credentials for api.github.com: " auth
    curl -L -u "$auth" -o "$path" "$url"
  }
  [[ -d "$output_path" ]] || unzip -d "$output_path" "$path"
done

pypi_dir=$(mktemp -d -p . pypi.XXXXXXXXXX)
cp "$artifacts_dir/"*/*.whl "$pypi_dir"

npm_dir=$(mktemp -d -p . npm.XXXXXXXXXX)
cp -r "$artifacts_dir/"hext-npm-package-*/* "$npm_dir"

echo "$(j "$run" .head_commit.timestamp)"\
  "$(j "$run" .head_commit.message)"\
  "($(j "$run" .head_commit.id))"

echo "artifacts: $artifacts_dir"
echo "PyPI: $pypi_dir"
echo "NPM: $npm_dir"

