#!/bin/bash

while ! nc -q 1 pece-db 3306 </dev/null; do sleep 3; done

sudo service php5-fpm restart
sudo nginx -g "daemon on;" > /tmp/access-nginx.log

if [ ! -d /pece/drupal/node_modules ];
then
  npm install && gulp setup && gulp build && gulp site-install
  sudo chgrp -R www-data /pece/drupal/cnf/files
fi

echo ""
echo "---------------------------------"
echo "Virtual machine ready to work."
echo "---------------------------------"

exec "$@"
