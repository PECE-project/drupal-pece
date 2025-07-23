#!/usr/bin/env bash
set -euo pipefail
set -x #<- for debugging

public_path=${1:-docker/files}
private_path=${2:-docker/private}
www_id=${3:-82} # (Generally 33:33 for Debian and 82:82 for Alpine, which wodby uses)

# PUBLIC: World readable, owned by PHP process (which for Wodby is www-data)
find "${public_path}" -type f ! -perm ug=rw,o=r -print0 | xargs -r -0 -L20 chmod ug=rw,o=r
find "${public_path}" -type d ! -perm ug=rwx,o=rx -print0 | xargs -r -0 -L20 chmod ug=rwx,o=rx
find "${public_path}" ! -user ${www_id} -print0 | xargs -r -0 -L20 chown ${www_id}
find "${public_path}" ! -group ${www_id} -print0 | xargs -r -0 -L20 chgrp ${www_id}

# PRIVATE: Privately owned and accessible by PHP process
find "${private_path}" -type f ! -perm ug=rw,o= -print0 | xargs -r -0 -L20 chmod ug=rw,o=
find "${private_path}" -type d ! -perm ug=rwx,o= -print0 | xargs -r -0 -L20 chmod ug=rwx,o=
find "${private_path}" ! -user ${www_id} -print0 | xargs -r -0 -L20 chown ${www_id}
find "${private_path}" ! -group ${www_id} -print0 | xargs -r -0 -L20 chgrp ${www_id}

# Ensure public thumbnails are not writable (prevent deletion):
find ${public_path}/styles/pece_thumbnail -type f ! -perm ugo=r -print0 | xargs -r -0 -L20 chmod ugo=r
find ${public_path}/styles/pece_thumbnail -type d ! -perm ugo=rx -print0 | xargs -r -0 -L20 chmod ugo=rx

# If/when e.g. a regex is applied to essay_content, then these might be useful to:
# a) copy styles for any files that were public and moved to private
# b) set specific permissions on all legacy styles folders to ensure they are not deleted
# ...at least until the styles are re-created in D10+
#
#move_styles=('apps_logo' 'panopoly_*' 'pece_[afm]*')
#all_styles=('panopoly_*' 'media_thumbnail' 'pece_artifact_image_large' 'pece_mini_teaser' 'pece_most_recent' 'pece_thumbnail')
#
#for style in "${move_styles[@]}"; do
#	mv "${public_path}/${style}" "${private_path}/${style}"
#done
#for style in "${all_styles[@]}"; do
#	chmod -w "${private_path}/${style}"
#done
