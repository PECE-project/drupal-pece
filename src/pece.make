core = 7.x
api = 2

projects[kw_manifests][type] = module
projects[kw_manifests][download][type] = git
projects[kw_manifests][download][url] = "git://github.com/kraftwagen/kw-manifests.git"
projects[kw_manifests][subdir] = kraftwagen

projects[kw_itemnames][type] = module
projects[kw_itemnames][download][type] = git
projects[kw_itemnames][download][url] = "git://github.com/kraftwagen/kw-itemnames.git"
projects[kw_itemnames][subdir] = kraftwagen

; The Panopoly Foundation
projects[panopoly_core][version] = 1.26
projects[panopoly_core][subdir] = contrib

projects[panopoly_images][version] = 1.26
projects[panopoly_images][subdir] = contrib

projects[panopoly_theme][version] = 1.26
projects[panopoly_theme][subdir] = contrib

projects[panopoly_magic][version] = 1.26
projects[panopoly_magic][subdir] = contrib

projects[panopoly_widgets][version] = 1.26
projects[panopoly_widgets][subdir] = contrib

projects[panopoly_admin][version] = 1.26
projects[panopoly_admin][subdir] = contrib

projects[panopoly_users][version] = 1.26
projects[panopoly_users][subdir] = contrib

; The Panopoly Toolset
projects[panopoly_pages][version] = 1.26
projects[panopoly_pages][subdir] = contrib

projects[panopoly_wysiwyg][version] = 1.26
projects[panopoly_wysiwyg][subdir] = contrib

projects[panopoly_search][version] = 1.26
projects[panopoly_search][subdir] = contrib

; For running the automated tests.
projects[panopoly_test][version] = 1.26
projects[panopoly_test][subdir] = contrib

; The Panopoly Radix
projects[radix][version] = 3.0-rc2
projects[radix][subdir] = contrib
projects[radix_layouts][version] = 3.3
projects[radix_layouts][subdir] = contrib
projects[radix_views][version] = 1.0
projects[radix_views][subdir] = radix
;projects[radix_admin][version] = 3.x-dev
;projects[radix_admin][subdir] = radix
;projects[radix_colorizer][version] = 1.x-dev
;projects[radix_colorizer][subdir] = radix

; Coffee
projects[coffee][version] = 2.2
projects[coffee][subdir]  = contrib

; ECK
projects[eck][version] = 2.0-rc7
projects[eck][subdir]  = contrib

; Inline Entity Form
projects[inline_entity_form][version] = 1.6
projects[inline_entity_form][subdir]  = contrib

; Rules
projects[rules][subdir] = contrib
projects[rules][version] = 2.9

; Translation
projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 2.0

; XAutoload
projects[xautoload][version] = 5.1
projects[xautoload][subdir]  = contrib
projects[xautoload][patch][] = "https://www.drupal.org/files/issues/xautoload-7.x-5.x-profile-2393205-6.patch"
projects[xautoload][patch][] = "https://www.drupal.org/files/issues/base_table_or_view_not-2393205-2.patch"

; jQuery update recent version
projects[jquery_update][subdir] = contrib
projects[jquery_update][version] = 2.6

; Ember for admin
projects[ember][subdir] = contrib
projects[ember][version] = 2.0-alpha3

; Organic groups
projects[og][subdir] = contrib
projects[og][version] = 2.7
projects[og_mailinglist][subdir] = contrib
projects[og_mailinglist][version] = 1.1-alpha2

; Email
projects[email][subdir] = contrib
projects[email][version] = 1.3

; Location
projects[location][subdir] = contrib
projects[location][version] = 3.7

; Bundle Inherit
projects[bundle_inherit][subdir] = contrib
projects[bundle_inherit][version] = 1.0-alpha2

; Publication date
projects[publication_date][subdir] = contrib
projects[publication_date][version] = 2.2

; Diff
projects[diff][subdir] = contrib
projects[diff][version] = 3.2

; Creative Commons Field
projects[creative_commons][subdir] = contrib
projects[creative_commons][version] = 1.2

; Legal
projects[legal][subdir] = contrib
projects[legal][version] = 1.5

; Profile 2
projects[profile2][subdir] = contrib
projects[profile2][version] = 1.3

; GMap
projects[gmap][subdir] = contrib
projects[gmap][version] = 2.9

; External link
projects[extlink][subdir] = contrib
projects[extlink][version] = 1.18

; External link
projects[extlink][subdir] = contrib
projects[extlink][version] = 1.18

; Fences
projects[fences][subdir] = contrib
projects[fences][version] = 1.0

; Entity View Mode
projects[entity_view_mode][subdir] = contrib
projects[entity_view_mode][version] = 1.0-rc1

; Real Name
projects[realname][subdir] = contrib
projects[realname][version] = 1.2

; Entity Reference View Widget
projects[entityreference_view_widget][subdir] = contrib
projects[entityreference_view_widget][version] = 2.0-rc6

; Entity Connect
projects[entityconnect][subdir] = contrib
projects[entityconnect][version] = 1.0-rc4

; Annotation
;projects[annotation][subdir] = contrib
;projects[annotation][version] = 1.x-dev

; Annotator
;projects[annotator][subdir] = contrib
;projects[annotator][version] = 1.x-dev

; *****************************************
; ************** PECE Themes **************

projects[radix][type] = theme
projects[radix][version] = 3.0-rc2

projects[ember][type] = theme
projects[ember][version] = 2.0-alpha3

; *****************************************
; ************** Libraries ****************

libraries[phpmailer][download][type] = git
libraries[phpmailer][download][url] = https://github.com/Synchro/PHPMailer.git
libraries[phpmailer][download][revision] = d3802c597bff8f6c2ccfa3eab2a511aa01b8d68f
libraries[phpmailer][download][branch] = master

; AnnotatorJS library.
;libraries[annotator][download][type] = file
;libraries[annotator][download][url] = https://github.com/openannotation/annotator/releases/download/v1.2.10/annotator.1.2.10.zip
;libraries[annotator][download][subtree] = annotator.1.2.10
