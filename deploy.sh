#!/bin/bash

set -ev

ls -lah

#
# rsync -avzhe "ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no" \
#   ./build ubuntu@138.197.1.62:/home/ubuntu/drupal-pece/build

print "Deployed succeeded \o/"
