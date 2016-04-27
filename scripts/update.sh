#!/usr/bin/env bash
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd ../ && pwd )"
# Update and Compile theme stylesheets.
(
  cd $ROOT_DIR
  node_modules/.bin/gulp update
)
