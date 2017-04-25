#!/bin/bash

set -ev

ls -lah

nvm use default
gulp update

rsync -avzhe "ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no" \
  ./build ubuntu@138.197.1.62:/home/ubuntu/drupal-pece/build

print "Deploy to DEV environment succeeded \o/"
