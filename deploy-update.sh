#!/bin/bash

set -ev

ls -lah

nvm use default
gulp update

print "Deploy succeeded \o/"
