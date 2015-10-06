cd ./build
drush kw-b
drush kw-u
if [ -d "profiles/pece/themes/pece_scholarly_lite/" ]; then
  cd profiles/pece/themes/pece_scholarly_lite/
  bundle install
  bundle exec compass compile
fi
