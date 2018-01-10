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
projects[ctools][version] = 1.12
projects[ctools][subdir] = contrib
; @TODO: Update and reapply the following patch.
; projects[ctools][patch][2671150] = "https://www.drupal.org/files/issues/ctools-2671150-1.patch"

; Overrides panopoly's libraries.
projects[libraries][version] = 2.2
projects[libraries][subdir] = contrib

; Overrides panopoly's token.
projects[token][version] = 1.6
projects[token][subdir] = contrib

; Overrides panopoly's entity.
projects[entity][version] = 1.8
projects[entity][subdir] = contrib
projects[entity][patch][2671150] = "https://www.drupal.org/files/issues/entity_id_token-1957266-36.patch"

; Overrides panopoly's uuid.
projects[uuid][version] = 1.0-beta1
projects[uuid][subdir] = contrib

projects[xautoload][version] = 5.7
projects[xautoload][subdir]  = contrib

projects[jquery_update][version] = 2.7
projects[jquery_update][subdir] = contrib

projects[prevent_js_alerts][version] = 1.0
projects[prevent_js_alerts][subdir] = contrib

projects[pathauto][version] = 1.3
projects[pathauto][subdir] = contrib

projects[pathauto_entity][version] = 1.0
projects[pathauto_entity][subdir] = contrib

projects[subpathauto][version] = 1.3
projects[subpathauto][subdir] = contrib


; =====================
; Views
; =====================

; Overrides panopoly's views.
projects[views][version] = 3.18
projects[views][subdir] = contrib
projects[views][patch][2037469] = http://drupal.org/files/views-exposed-sorts-2037469-1.patch
projects[views][patch][2331209] = https://www.drupal.org/files/issues/2331209-4-views-7.x-3.x-undefined-index.patch

projects[views_infinite_scroll][version] = 2.0
projects[views_infinite_scroll][subdir] = contrib

projects[views_litepager][version] = 3.0
projects[views_litepager][subdir] = contrib

projects[tvi][version] = 1.0-beta5
projects[tvi][subdir] = contrib

projects[better_exposed_filters][version] = 3.5
projects[better_exposed_filters][subdir] = contrib

projects[views_autocomplete_filters][version] = 1.2
projects[views_autocomplete_filters][subdir] = contrib

; =====================
; Administration
; =====================

projects[admin_menu][version] = 3.0-rc5
projects[admin_menu][subdir]  = contrib

projects[adminimal_admin_menu][version] = 1.7
projects[adminimal_admin_menu][subdir]  = contrib

projects[coffee][version] = 2.2
projects[coffee][subdir]  = contrib

projects[fpa][version] = 2.6
projects[fpa][subdir]  = contrib

projects[filter_perms][version] = 1.0
projects[filter_perms][subdir]  = contrib


; =====================
; Configuration Management
; =====================

; Overrides panopoly_core's features_override.
projects[features_override][version] = 2.0-rc3
projects[features_override][subdir] = contrib

projects[features][version] = 2.10
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

; Honeypot
projects[honeypot][subdir] = contrib
projects[honeypot][version] = 1.22

; =====================
; Panels
; =====================

; Overrides panopoly's panelizer.
projects[panelizer][version] = 3.4
projects[panelizer][subdir] = contrib
projects[panelizer][patch][2812807] = https://www.drupal.org/files/issues/panelizer--2812807--provide-entity-on-access-hooks.patch

projects[panels][version] = 3.7
projects[panels][subdir] = contrib

;projects[panels_breadcrumbs][version] = 2.2
;projects[panels_breadcrumbs][subdir] = contrib;

projects[fieldable_panels_panes][version] = 1.10
projects[fieldable_panels_panes][subdir] = contrib
projects[fieldable_panels_panes][patch][2814117] = https://www.drupal.org/files/issues/fieldable_panels_panes--access_hook--2814117-1.patch


; =====================
; Panopoly
; =====================

; The Panopoly Foundation
projects[panopoly_core][version] = 1.49
projects[panopoly_core][subdir] = contrib

projects[panopoly_images][version] = 1.49
projects[panopoly_images][subdir] = contrib

; Panopoly images depending libraries
libraries[jquery.imagesloaded][download][type] = file
libraries[jquery.imagesloaded][download][url] = https://github.com/desandro/imagesloaded/archive/v2.1.2.tar.gz
libraries[jquery.imagesloaded][download][subtree] = imagesloaded-2.1.2

libraries[jquery.imgareaselect][download][type] = file
libraries[jquery.imgareaselect][download][url] = https://github.com/odyniec/imgareaselect/archive/v0.9.11-rc.1.tar.gz
libraries[jquery.imgareaselect][download][subtree] = imgareaselect-0.9.11-rc.1

projects[panopoly_theme][version] = 1.49
projects[panopoly_theme][subdir] = contrib

projects[panopoly_magic][version] = 1.49
projects[panopoly_magic][subdir] = contrib

projects[panopoly_widgets][version] = 1.49
projects[panopoly_widgets][subdir] = contrib
projects[panopoly_widgets][patch][2919401] = https://www.drupal.org/files/issues/panopoly_widgets-update-tablefield-2919401-3.patch

projects[panopoly_admin][version] = 1.49
projects[panopoly_admin][subdir] = contrib

projects[panopoly_users][version] = 1.49
projects[panopoly_users][subdir] = contrib

; The Panopoly Toolset
projects[panopoly_pages][version] = 1.49
projects[panopoly_pages][subdir] = contrib

projects[panopoly_wysiwyg][version] = 1.49
projects[panopoly_wysiwyg][subdir] = contrib

projects[panopoly_search][subdir] = contrib
projects[panopoly_search][version] = 1.49
projects[panopoly_search][patch][] = "./patches/panopoly-remove_panelizer_data_alter_callback.patch"

; For running the automated tests.
projects[panopoly_test][version] = 1.49
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

projects[breakpoints][version] = 1.4
projects[breakpoints][subdir] = contrib

;projects[breakpointsjs][version] = 2.x-dev
;projects[breakpointsjs][subdir] = contrib

; =====================
; Entities
; =====================

projects[eck][version] = 2.0-rc8
projects[eck][subdir]  = contrib

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][subdir] = contrib

projects[entityreference][version] = 1.5
projects[entityreference][subdir] = contrib
projects[entityreference][patch][1836106] = "https://www.drupal.org/files/issues/entityreference_1836106_59.patch"
projects[entityreference][patch][1423778] = "https://www.drupal.org/files/issues/entityreference-1423778-brokenhandler.diff"

projects[entityreference_view_widget][version] = 2.0-rc6
projects[entityreference_view_widget][subdir] = contrib

projects[er_viewmode][version] = 1.0-alpha1
projects[er_viewmode][subdir] = contrib

projects[entityconnect][version] = 2.0-rc1
projects[entityconnect][subdir] = contrib

projects[inline_entity_form][version] = 1.8
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

projects[smart_trim][version] = 1.5
projects[smart_trim][subdir] = contrib

; =====================
; Files
; =====================

projects[file_entity][version] = 2.0-beta2
projects[file_entity][subdir] = contrib

projects[media][version] = 2.14
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

projects[linkit][version] = 3.5
projects[linkit][subdir] = contrib

projects[field_group][version] = 1.5
projects[field_group][subdir] = contrib

; =====================
; Search
; =====================

projects[search_api][version] = 1.18
projects[search_api][subdir]  = contrib

; =====================
; Themes
; =====================

projects[radix][type] = theme
projects[radix][version] = 3.0-rc2
projects[radix][subdir] = contrib

; Adminimal Theme for admin
projects[adminimal_theme][type] = theme
projects[adminimal_theme][version] = 1.24
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

;libraries[annotator][download][type] = file
;libraries[annotator][download][url] = https://github.com/openannotation/annotator/releases/download/v1.2.10/annotator.1.2.10.zip
;libraries[annotator][download][subtree] = annotator.1.2.10

libraries[spyc][download][type] = file
libraries[spyc][download][url] = https://github.com/mustangostang/spyc/archive/0.5.1.zip
libraries[spyc][directory_name] = spyc-master

libraries[imgareaselect][download][type] = file
libraries[imgareaselect][download][url] = http://odyniec.net/projects/imgareaselect/jquery.imgareaselect-0.9.10.zip
libraries[imgareaselect][directory_name] = jquery.imgareaselect

libraries[aws][download][type] = file
libraries[aws][download][url] = https://github.com/aws/aws-sdk-php/releases/download/3.15.5/aws.zip
libraries[aws][directory_name] = aws

libraries[cycle][download][type] = file
libraries[cycle][download][url] = http://malsup.github.io/min/jquery.cycle.all.min.js
libraries[cycle][directory_name] = jquery.cycle

; =====================
; Other
; =====================

; Colorizer
;projects[colorizer][version] = 1.7
;projects[colorizer][subdir]  = contrib

; Rules
projects[rules][subdir] = contrib
projects[rules][version] = 2.9
projects[rules][patch][2189645] = https://www.drupal.org/files/issues/d7_component_caches.patch

; Translation
projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 2.0

; Organic groups
projects[og][subdir] = contrib
projects[og][version] = 2.9

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
projects[legal][version] = 1.10

; Profile 2
projects[profile2][subdir] = contrib
projects[profile2][version] = 1.3
projects[profile2][patch][1273026] = https://www.drupal.org/files/ctools-profile2_from_user-1273026-10.patch
projects[profile2][patch][1307538] = https://www.drupal.org/files/issues/profile2-fix_entity_info_failure_during_install-1307538-10-7.x-1.x-dev.patch

; GMap
projects[gmap][subdir] = contrib
projects[gmap][version] = 2.11

; External link
projects[extlink][subdir] = contrib
projects[extlink][version] = 1.18

; Real Name
projects[realname][subdir] = contrib
projects[realname][version] = 1.2

; TagCloud
projects[tagclouds][version] = 1.11
projects[tagclouds][subdir]  = contrib

; Taxonomy Access Fix
projects[taxonomy_access_fix][subdir] = contrib
projects[taxonomy_access_fix][version] = 2.3

; Annotation
;projects[annotation][subdir] = contrib
;projects[annotation][version] = 1.x-dev

; Annotator
;projects[annotator][subdir] = contrib
;projects[annotator][version] = 1.x-dev

; PDF Reader
projects[pdf_reader][subdir] = contrib
projects[pdf_reader][version] = 1.0-rc6
projects[pdf_reader][patch][] = "./patches/pdf_reader-keydown_event_page_error.patch"

; Amber
projects[amber][subdir] = contrib
projects[amber][version] = 1.0

; Backup and Migrate
projects[backup_migrate][subdir] = contrib
projects[backup_migrate][version] = 3.1

; Node Expiration
projects[node_expire][subdir] = contrib
projects[node_expire][version] = 2.2

; Date (dependency of node_expire)
projects[date][subdir] = contrib
projects[date][version] = 2.9

; =====================
; Development Modules
; =====================

; Backup and Migrate - SFTP support
projects[backup_migrate_sftp][subdir] = contrib
projects[backup_migrate_sftp][version] = 1.0

; SMTP Mail
projects[smtp][subdir] = contrib
projects[smtp][version] = 1.7

; Services
projects[services][subdir] = contrib
projects[services][version] = 3.20

; Services Views
projects[services_views][subdir] = contrib
projects[services_views][version] = 1.3

; =====================
; Integrations
; =====================

; Job scheduler
projects[job_scheduler][subdir] = contrib
projects[job_scheduler][version] = 2.0-alpha3

; Feeds
projects[feeds][subdir] = contrib
projects[feeds][version] = 2.0-beta2

; Bibliography
projects[biblio][subdir] = contrib
projects[biblio][version] = 1.0-rc7

; Bibliography Zotero
projects[biblio_zotero][subdir] = contrib
projects[biblio_zotero][version] = 1.x-dev

; =====================
; Imports
; =====================
; At the end, so that overrides are possible.includes[] = modules/sandbox/taller_entity/taller_entity.make
includes[] = modules/sandbox/panels_packery/panels_packery.make

; =====================
; Disabled.
; Here are the disabled modules to be deleted from make after all environments
; have disabled them. We can not remove these modules right now because the
; build runs before the updates, and it will be impossible to disable a module
; that no longer exists.
; =====================
projects[og_mailinglist][subdir] = contrib
projects[og_mailinglist][version] = 1.1-alpha2
