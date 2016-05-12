#!/bin/bash

while ! nc -q 1 pece-db 3306 </dev/null; do sleep 3; done

sudo chown -R www-data:www-data /pece/drupal/cnf/files
sudo service php5-fpm restart
sudo nginx -g "daemon on;"

if [ ! -d /pece/drupal/node_modules ];
then
  npm install && gulp setup
fi

echo ""
echo "---------------------------------"
echo "Virtual machine ready to work."
echo "---------------------------------"

exec "$@"
