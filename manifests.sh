cd build
drush kw-m

if [ -d "profiles/pece/themes/taller/assets/sass/" ]; then
  (
    cd profiles/pece/themes/taller/assets/sass/
    bundle install
    bundle exec compass compile
  )
fi

if [ -d "profiles/pece/themes/pece/assets/sass/" ]; then
  (
    cd profiles/pece/themes/pece/assets/sass/
    bundle install
    bundle exec compass compile
  )
fi

if [ -d "profiles/pece/themes/ember" ]; then
  (
    cd profiles/pece/themes/ember
    bundle install
    bundle exec compass compile
  )
fi
