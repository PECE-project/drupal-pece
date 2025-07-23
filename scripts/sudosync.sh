#!/usr/bin/env bash
set -euo pipefail
# PULL
#rsync -av --rsync-path="sudo rsync" --exclude /private/amber --exclude /php --exclude /js --exclude /css --exclude /twig pece-asthma-live:/data/www/files/ web/sites/default/files
# PUSH:
rsync -rlptvzc --delete --rsync-path="sudo rsync" --exclude /php --exclude /js --exclude /css --exclude /twig --exclude /private web/sites/default/files/ target-server:/data/public
rsync -rlptvzc --delete --rsync-path="sudo rsync" --exclude /php --exclude /js --exclude /css --exclude /twig ./private-files/ target-server:/data/private
