#!/usr/bin/env bash

PASSWORD="${PASSWORD:-impossiblepassword}"

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
