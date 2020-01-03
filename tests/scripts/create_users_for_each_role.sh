drush ucrt cy_owner --mail=owner@email.com --password=123456789
drush ucrt cy_researcher --mail=researcher@email.com --password=123456789
drush ucrt cy_contributor --mail=contributor@email.com --password=123456789
drush ucrt cy_user --mail=user@email.com --password=123456789
drush urol Researcher cy_researcher
drush urol Researcher cy_owner
drush urol Contributor cy_contributor
