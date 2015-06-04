cd ~/***DRUPAL_MACHINE_NAME***/build
drush kw-m
if [ -d "profiles/***DRUPAL_MACHINE_NAME***/themes/taller/assets/sass/" ]; then
  cd profiles/***DRUPAL_MACHINE_NAME***/themes/taller/assets/sass/
  bundle install
  bundle exec compass compile
fi
cd ~/***DRUPAL_MACHINE_NAME***/build
if [ -d "profiles/***DRUPAL_MACHINE_NAME***/themes/***DRUPAL_MACHINE_NAME***/assets/sass/" ]; then
  cd profiles/***DRUPAL_MACHINE_NAME***/themes/***DRUPAL_MACHINE_NAME***/assets/sass/
  bundle install
  bundle exec compass compile
fi
cd ~/***DRUPAL_MACHINE_NAME***/build
if [ -d "profiles/***DRUPAL_MACHINE_NAME***/themes/ember" ]; then
  cd profiles/***DRUPAL_MACHINE_NAME***/themes/ember
  bundle install
  bundle exec compass compile
fi
