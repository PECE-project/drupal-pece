core = 7.x
api = 2

projects[drupal][version] = 7.91
; Fix Custom logo and favicon stored in private filesystem if it is the default.
projects[drupal][patch][1087250] = https://www.drupal.org/files/issues/1087250.logo-public-filesystem.057-b.patch

projects[pece][type] = "profile"
projects[pece][download][type] = "kraftwagen_directory"
projects[pece][download][url] = "**SRC_DIR**"


