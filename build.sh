#!/usr/bin/env bash

source $HOME/.nvm/nvm.sh

ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

(
  npm install
  node_modules/.bin/gulp build

  cd ./build
  drush kw-u
  cd $ROOT_DIR
)

sh ../../scripts/sample_content.sh
