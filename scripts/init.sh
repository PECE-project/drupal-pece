#!/usr/bin/env bash
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd ../ && pwd )"
PASSWORD=${PECE_DRUPAL_ADMIN_PASS:-impossiblepassword}

drush kw-b
# We're not running 'drush kw-id' becaus we musr set up the account-pass param.
drush si pece --site-name="PECE Drupal Distro" --account-pass=${PASSWORD} -y

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
