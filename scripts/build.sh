#!/usr/bin/env bash
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd ../ && pwd )"

# Build and Compile theme stylesheets.
(
  cd $ROOT_DIR
  node_modules/.bin/gulp build
)

sh ../../scripts/sample_content.sh
