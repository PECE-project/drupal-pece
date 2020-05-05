#!/bin/bash

set -ev

ls -lah

rsync -avzhe "ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no" \
  ./build ubuntu@159.89.183.62:/home/ubuntu/pece/build

print "Deploy to DEV environment succeeded \o/"
