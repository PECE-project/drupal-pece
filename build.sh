#!/usr/bin/env bash
drush kw-b
cd build

PASSWORD=${PECE_DRUPAL_ADMIN_PASS:-impossiblepassword}
# drush kw-id
drush si pece --account-pass=${PASSWORD} -y
drush kw-m
drush cc all
## Uncomment for CM left sync.
# drush clsyn

if [ -d "profiles/pece/themes/taller/assets/sass/" ]; then
  (
    cd profiles/pece/themes/taller/assets/sass/
    bundle install
    bundle exec compass compile
  )
fi

if [ -d "profiles/pece/themes/pece_radix/assets/sass/" ]; then
  (
    cd profiles/pece/themes/pece/assets/sass/
    bundle install
    bundle exec compass compile
  )
fi

if [ -d "profiles/pece/themes/contrib/ember" ]; then
  (
    cd profiles/pece/themes/contrib/ember
    bundle install
    bundle exec compass compile
  )
fi
