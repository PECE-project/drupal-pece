#!/usr/bin/env bash
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd ../ && pwd )"

drush kw-b

(
  cd ./build
)
drush kw-u
## Uncomment for CM left sync.
# drush clsyn

# Compile theme stylesheets.
(
  cd $ROOT_DIR
)
node_modules/.bin/gulp styles

sh ../../scripts/sample_content.sh
