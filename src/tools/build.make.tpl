core = 7.x
api = 2

projects[drupal][version] = 7.80
; Fix Error in image_styles of image.module on database update.
projects[drupal][patch][1973278] = http://www.drupal.org/files/issues/image-accommodate_missing_definition-1973278-16.patch
; Fix Custom logo and favicon stored in private filesystem if it is the default.
projects[drupal][patch][1087250] = https://www.drupal.org/files/issues/1087250.logo-public-filesystem.057-b.patch

projects[pece][type] = "profile"
projects[pece][download][type] = "kraftwagen_directory"
projects[pece][download][url] = "**SRC_DIR**"


