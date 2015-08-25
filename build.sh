#!/usr/bin/env bash
drush kw-b
cd build

PASSWORD=${PECE_DRUPAL_ADMIN_PASS:-impossiblepassword}
# drush kw-id
drush si pece --site-name="PECE Drupal Distro" --account-pass=${PASSWORD} -y
drush kw-u
## Uncomment for CM left sync.
# drush clsyn

if [ -d "profiles/pece/themes/pece_radix/" ]; then
  (
    cd profiles/pece/themes/pece_radix/
    bundle install
    bundle exec compass compile
  )
fi
