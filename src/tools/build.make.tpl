core = 7.x
api = 2

projects[drupal][version] = 7.98
; Fix Custom logo and favicon stored in private filesystem if it is the default.
projects[drupal][patch][1087250] = https://www.drupal.org/files/issues/1087250.logo-public-filesystem.057-b.patch
; Installation profiles do not support project:module format for dependencies (backport to D7).
projects[drupal][patch][2905520] = https://www.drupal.org/files/issues/drupal-namespaced-profile-dependencies-2905520-7.patch

projects[pece][type] = "profile"
projects[pece][download][type] = "kraftwagen_directory"
projects[pece][download][url] = "**SRC_DIR**"


