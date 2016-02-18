core = 7.x
api = 2


; =====================
; kraftwagen
; =====================

projects[kw_manifests][type] = module
projects[kw_manifests][download][type] = git
projects[kw_manifests][download][url] = "git://github.com/kraftwagen/kw-manifests.git"
projects[kw_manifests][subdir] = kraftwagen

projects[kw_itemnames][type] = module
projects[kw_itemnames][download][type] = git
projects[kw_itemnames][download][url] = "git://github.com/kraftwagen/kw-itemnames.git"
projects[kw_itemnames][subdir] = kraftwagen


; =====================
; Utilities and APIs
; =====================

; Overrides panopoly's ctools.
projects[ctools][version] = 1.9
projects[ctools][subdir] = contrib
projects[ctools][patch][] = "./patches/ctools-save_continue_button.patch"
projects[ctools][patch][] = "https://www.drupal.org/files/issues/ctools-2671150-1.patch"

; Overrides panopoly's libraries.
projects[libraries][version] = 2.2
projects[libraries][subdir] = contrib

; Overrides panopoly's token.
projects[token][version] = 1.6
projects[token][subdir] = contrib

; Overrides panopoly's entity.
projects[entity][version] = 1.6
projects[entity][subdir] = contrib

projects[xautoload][version] = 5.5
projects[xautoload][subdir]  = contrib

projects[jquery_update][version] = 2.7
projects[jquery_update][subdir] = contrib

projects[prevent_js_alerts][version] = 1.0
projects[prevent_js_alerts][subdir] = contrib

projects[pathauto][version] = 1.3
projects[pathauto][subdir] = contrib

projects[pathauto_entity][version] = 1.0
projects[pathauto_entity][subdir] = contrib


; =====================
; Views
; =====================

projects[views_infinite_scroll][version] = 1.1
projects[views_infinite_scroll][subdir] = contrib

projects[views_litepager][version] = 3.0
projects[views_litepager][subdir] = contrib

projects[tvi][version] = 1.0-beta5
projects[tvi][subdir] = contrib

; =====================
; Administration
; =====================

projects[admin_menu][version] = 3.0-rc5
projects[admin_menu][subdir]  = contrib

projects[adminimal_admin_menu][version] = 1.6
projects[adminimal_admin_menu][subdir]  = contrib

projects[coffee][version] = 2.2
projects[coffee][subdir]  = contrib

; =====================
; Configuration Management
; =====================

; Overrides panopoly_core's features_override.
projects[features_override][version] = 2.0-rc3
projects[features_override][subdir] = contrib

projects[features][version] = 2.7
projects[features][subdir] = contrib

projects[diff][version] = 3.2
projects[diff][subdir] = contrib

projects[strongarm][version] = 2.0
projects[strongarm][subdir] = contrib

projects[defaultconfig][version] = 1.0-alpha11
projects[defaultconfig][subdir] = contrib

; =====================
; Security
; =====================

; projects[seckit][subdir] = contrib
; projects[username_enumeration_prevention][subdir] = contrib
; projects[password_policy][subdir] = contrib

; Login Security
projects[login_security][subdir] = contrib
projects[login_security][version] = 1.9

; AES (with php5-mcrypt support)
projects[aes][subdir] = contrib
projects[aes][version] = 1.10


; =====================
; Panels
; =====================

; Overrides panopoly's panelizer.
projects[panelizer][version] = 3.1
projects[panelizer][subdir] = contrib
projects[panelizer][patch][1623536] = http://drupal.org/files/issues/array-to-object-on-update-1623536-26.patch
projects[panelizer][patch][2416505] = http://www.drupal.org/files/issues/panelizer-search_api-2416505-3.patch
projects[panelizer][patch][2328615] = https://www.drupal.org/files/issues/panelizerentitydefault-2328615-1.patch

projects[panels][version] = 3.5
projects[panels][subdir] = contrib
projects[panels][patch][2448825] = https://www.drupal.org/files/issues/panels-export-indentation-2448825-1.patch
projects[panels][patch][2390803] = https://www.drupal.org/files/issues/panels-focus-add-content-tab-2390803-13.patch

;projects[panels_breadcrumbs][version] = 2.2
;projects[panels_breadcrumbs][subdir] = contrib;

; =====================
; Panopoly
; =====================

; The Panopoly Foundation
projects[panopoly_core][version] = 1.28
projects[panopoly_core][subdir] = contrib

projects[panopoly_images][version] = 1.28
projects[panopoly_images][subdir] = contrib

projects[panopoly_theme][version] = 1.28
projects[panopoly_theme][subdir] = contrib

projects[panopoly_magic][version] = 1.28
projects[panopoly_magic][subdir] = contrib

projects[panopoly_widgets][version] = 1.28
projects[panopoly_widgets][subdir] = contrib

projects[panopoly_admin][version] = 1.28
projects[panopoly_admin][subdir] = contrib

; projects[panopoly_users][version] = 1.28
; projects[panopoly_users][subdir] = contrib

; The Panopoly Toolset
projects[panopoly_pages][version] = 1.28
projects[panopoly_pages][subdir] = contrib

projects[panopoly_wysiwyg][version] = 1.28
projects[panopoly_wysiwyg][subdir] = contrib

projects[panopoly_search][subdir] = contrib
projects[panopoly_search][version] = 1.28

; For running the automated tests.
projects[panopoly_test][version] = 1.27
projects[panopoly_test][subdir] = contrib

; The Panopoly Radix
projects[radix_layouts][version] = 3.4
projects[radix_layouts][subdir] = contrib
projects[radix_views][version] = 1.0
projects[radix_views][subdir] = contrib

;projects[radix_colorizer][version] = 1.x-dev
;projects[radix_colorizer][subdir] = contrib
;projects[radix_admin][version] = 3.x-dev
;projects[radix_admin][subdir] = contrib

; =====================
; Interface
; =====================

projects[breakpoints][version] = 1.3
projects[breakpoints][subdir] = contrib

;projects[breakpointsjs][version] = 2.x-dev
;projects[breakpointsjs][subdir] = contrib

; =====================
; Entities
; =====================

projects[eck][version] = 2.0-rc7
projects[eck][subdir]  = contrib

projects[entity_view_mode][subdir] = contrib
projects[entity_view_mode][version] = 1.0-rc1

projects[entityreference_view_widget][subdir] = contrib
projects[entityreference_view_widget][version] = 2.0-rc6

projects[entityconnect][subdir] = contrib
projects[entityconnect][version] = 1.0-rc5

projects[inline_entity_form][version] = 1.6
projects[inline_entity_form][subdir]  = contrib

; =====================
; Form & Form Elements
; =====================

projects[elements][version] = 1.4
projects[elements][subdir] = contrib

projects[panels_tabs][version] = 1.x-dev
projects[panels_tabs][subdir] = contrib

projects[fences][version] = 1.2
projects[fences][subdir] = contrib

projects[better_formats][version] = 1.0-beta1
projects[better_formats][subdir] = contrib

; =====================
; Files
; =====================

projects[file_entity][version] = 2.0-beta2
projects[file_entity][subdir] = contrib

projects[media][version] = 2.0-beta1
projects[media][subdir] = contrib

projects[ckeditor][version] = 1.16
projects[ckeditor][subdir] = contrib

projects[manualcrop][version] = 1.5
projects[manualcrop][subdir] = contrib

; =====================
; Fields
; =====================

projects[image_resize_filter][version] = 1.16
projects[image_resize_filter][subdir] = contrib

projects[linkit][version] = 3.4
projects[linkit][subdir] = contrib

projects[field_group][version] = 1.5
projects[field_group][subdir] = contrib

; =====================
; Search
; =====================

projects[search_api][version] = 1.16
projects[search_api][subdir]  = contrib

; =====================
; Themes
; =====================

projects[radix][type] = theme
projects[radix][version] = 3.0-rc2
projects[radix][subdir] = contrib

; Adminimal Theme for admin
projects[adminimal_theme][type] = theme
projects[adminimal_theme][version] = 1.23
projects[adminimal_theme][subdir] = contrib

; PECE Base Theme
; projects[scholarly_lite][type] = theme
; projects[scholarly_lite][version] = 1.0
; projects[scholarly_lite][subdir] = contrib

; =====================
; Libraries
; =====================

libraries[phpmailer][download][type] = git
libraries[phpmailer][download][url] = https://github.com/Synchro/PHPMailer.git
libraries[phpmailer][download][revision] = d3802c597bff8f6c2ccfa3eab2a511aa01b8d68f
libraries[phpmailer][download][branch] = master

libraries[autopager][download][type] = file
libraries[autopager][download][url] = http://jquery-autopager.googlecode.com/files/jquery.autopager-1.0.0.js

;libraries[annotator][download][type] = file
;libraries[annotator][download][url] = https://github.com/openannotation/annotator/releases/download/v1.2.10/annotator.1.2.10.zip
;libraries[annotator][download][subtree] = annotator.1.2.10

libraries[spyc][download][type] = file
libraries[spyc][download][url] = https://github.com/mustangostang/spyc/archive/0.5.1.zip
libraries[spyc][directory_name] = spyc-master

; =====================
; Other
; =====================

; Colorizer
;projects[colorizer][version] = 1.7
;projects[colorizer][subdir]  = contrib

; Rules
projects[rules][subdir] = contrib
projects[rules][version] = 2.9

; Translation
projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 2.0

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

; Creative Commons Field
projects[creative_commons][subdir] = contrib
projects[creative_commons][version] = 1.2

; Legal
projects[legal][subdir] = contrib
projects[legal][version] = 1.5

; Profile 2
projects[profile2][subdir] = contrib
projects[profile2][version] = 1.3
projects[profile2][patch][] = https://www.drupal.org/files/ctools-profile2_from_user-1273026-10.patch

; GMap
projects[gmap][subdir] = contrib
projects[gmap][version] = 2.10

; External link
projects[extlink][subdir] = contrib
projects[extlink][version] = 1.18

; Real Name
projects[realname][subdir] = contrib
projects[realname][version] = 1.2

; TagCloud
projects[tagclouds][version] = 1.10
projects[tagclouds][subdir]  = contrib

; Taxonomy Access Fix
projects[taxonomy_access_fix][subdir] = contrib
projects[taxonomy_access_fix][version] = 2.2

; Annotation
;projects[annotation][subdir] = contrib
;projects[annotation][version] = 1.x-dev

; Annotator
;projects[annotator][subdir] = contrib
;projects[annotator][version] = 1.x-dev

; PDF Reader
projects[pdf_reader][subdir] = contrib
projects[pdf_reader][version] = 1.0-rc6

; =====================
; Development Modules
; =====================

projects[devel][subdir] = dev
projects[search_krumo][subdir] = dev
projects[module_builder][subdir] = dev
projects[drupal_ipsum][subdir] = dev
projects[environment_indicator][subdir] = dev

projects[seeds][type] = module
projects[seeds][download][type] = git
projects[seeds][download][url] = https://github.com/lucasconstantino/drupal-seeds.git
projects[seeds][subdir] = dev

projects[search_krumo][subdir] = dev

; =====================
; Imports
; =====================
; At the end, so that overrides are possible.includes[] = modules/sandbox/taller_entity/taller_entity.make
; includes[] = path/to/file.make
