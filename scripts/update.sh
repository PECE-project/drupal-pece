#!/usr/bin/env bash
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd ../ && pwd )"

(
  cd ./build
)
drush kw-u

# Compile theme stylesheets.
(
  cd $ROOT_DIR
)
node_modules/.bin/gulp styles
