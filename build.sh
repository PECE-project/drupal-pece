#!/usr/bin/env bash
drush kw-b
cd build

PASSWORD=${PECE_DRUPAL_ADMIN_PASS:-impossiblepassword}
# We're not running 'drush kw-id' becaus we musr set up the account-pass param.
drush si pece --site-name="PECE Drupal Distro" --account-pass=${PASSWORD} -y

drush kw-u
## Uncomment for CM left sync.
# drush clsyn

if [ -d "profiles/pece/themes/pece_scholarly_lite/" ]; then
  (
    cd profiles/pece/themes/pece_scholarly_lite/
    bundle install
    bundle exec "compass clean && compass compile"
  )
fi

sh ../../scripts/sample_content.sh
