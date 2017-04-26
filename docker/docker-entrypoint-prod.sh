#!/bin/bash

sudo chown $UID:$UID -R .
sudo chmod +w -R .
while ! nc -q 1 pece-db 3306 </dev/null; do sleep 3; done

sudo service php5-fpm restart
sudo nginx -g "daemon on;" > /tmp/access-nginx.log

echo ""
echo "--------------------------------"
echo "------ Database connected ------"
echo "--------------------------------"
echo ""

echo ""
echo "-------------------------------"
echo "-- Started the build process --"
echo "-------------------------------"
echo ""

if [[ -d ./build ]]; then
  rm -r ./build
fi
/usr/local/bin/drush kw-b

echo "PECE's Build proccess succeeded."

echo ""
echo "------------------------------"
echo "Virtual machine ready to work."
echo "------------------------------"
echo ""

exec "$@"
