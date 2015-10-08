#!/usr/bin/env bash
drush kw-b
cd build

PASSWORD=${PECE_DRUPAL_ADMIN_PASS:-impossiblepassword}
# drush kw-id
drush si pece --site-name="PECE Drupal Distro" --account-pass=${PASSWORD} -y
drush kw-u
## Uncomment for CM left sync.
# drush clsyn

if [ -d "profiles/pece/themes/pece_scholarly_lite/" ]; then
  (
    cd profiles/pece/themes/pece_scholarly_lite/
    bundle install
    bundle exec "compass clean && compass compile"
  )
fi

drush ucrt taller --mail=dev-pece@taller.net.br --password=${PASSWORD}
drush ucrt reva --mail=renato@taller.net.br --password=${PASSWORD}
drush ucrt liz --mail=liz@taller.net.br --password=${PASSWORD}
drush ucrt contributor --mail=example@example.com --password=${PASSWORD}
drush ucrt researcher --mail=researcher@example.com --password=${PASSWORD}
drush urol 'Contributor' --name=reva
drush urol 'Contributor' --name=contributor
drush urol 'Researcher' --name=liz
drush urol 'Researcher' --name=researcher
drush gent pece_tags
drush gent pece_structured_analytics
drush genc 3 0 --types=pece_group
drush genc 6 0 --types=pece_analytic
drush genc 3 0 --types=pece_fieldsite
drush genc 3 0 --types=pece_artifact_text
drush genc 3 0 --types=pece_artifact_image
drush genc 3 0 --types=pece_artifact_audio
drush genc 3 0 --types=pece_artifact_video
drush genc 3 0 --types=pece_artifact_fieldnote
drush genc 3 0 --types=pece_memo
