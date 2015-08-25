cd ./build
drush kw-u
if [ -d "profiles/pece/themes/pece_radix/" ]; then
  cd profiles/pece/themes/pece_radix/
  bundle install
  bundle exec compass compile
fi
