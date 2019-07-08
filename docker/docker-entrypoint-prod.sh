#!/bin/bash

sudo chown $UID:$UID -R .
sudo chmod +w -R .
while ! nc -q 1 pece-db 3306 </dev/null; do sleep 3; done

sudo service php7.2-fpm stop
sudo service php7.2-fpm start

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

if [ ! -d /pece/drupal/node_modules ];
then
  npm install && gulp setup && gulp build && gulp site-install
  sudo chmod 775 -Rf /pece/drupal/cnf
fi

echo "PECE's Build proccess succeeded."

echo ""
echo "------------------------------"
echo "PECE project ready to work."
echo "------------------------------"
echo ""

exec "$@"
