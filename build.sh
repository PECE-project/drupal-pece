cd ~/***DRUPAL_MACHINE_NAME***
drush kw-b
cd build
drush kw-m
drush cc all
drush updb -y
drush fra -y
drush clsyn
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
cd ~/***DRUPAL_MACHINE_NAME***
