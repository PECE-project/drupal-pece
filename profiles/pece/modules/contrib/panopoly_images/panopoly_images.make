; Panopoly Images Makefile

api = 2
core = 7.x

; Cropping images

projects[manualcrop][version] = 1.7
projects[manualcrop][subdir] = contrib
projects[manualcrop][patch][3177209] = https://www.drupal.org/files/issues/2020-10-23/manualcrop-csp-3177209-5.patch
projects[manualcrop][patch][3264865] = https://www.drupal.org/files/issues/2022-02-17/manualcrop-d788-3264865-2_0.patch

; jquery.imagesLoaded library for manualcrop
libraries[jquery.imagesloaded][download][type] = file
libraries[jquery.imagesloaded][download][url] = https://github.com/desandro/imagesloaded/archive/v2.1.2.tar.gz
libraries[jquery.imagesloaded][download][subtree] = imagesloaded-2.1.2

; jquery.imgAreaSelect library for manualcrop
libraries[jquery.imgareaselect][download][type] = file
libraries[jquery.imgareaselect][download][url] = https://github.com/odyniec/imgareaselect/archive/v0.9.11-rc.1.tar.gz
libraries[jquery.imgareaselect][download][subtree] = imgareaselect-0.9.11-rc.1
