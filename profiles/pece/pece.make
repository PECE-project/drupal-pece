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
; Libraries
; =====================

; Panopoly images depending libraries
libraries[jquery.imagesloaded][download][type] = file
libraries[jquery.imagesloaded][download][url] = https://github.com/desandro/imagesloaded/archive/v2.1.2.tar.gz
libraries[jquery.imagesloaded][download][subtree] = imagesloaded-2.1.2


; Misc Libraries

libraries[imagesloaded][download][type] = file
libraries[imagesloaded][download][url] = https://github.com/desandro/imagesloaded/archive/v2.1.2.tar.gz
libraries[imagesloaded][download][subtree] = imagesloaded-2.1.2

libraries[imgareaselect][download][type] = file
libraries[imgareaselect][download][url] = https://github.com/odyniec/imgareaselect/archive/v0.9.11-rc.1.tar.gz
libraries[imgareaselect][directory_name] = jquery.imgareaselect

libraries[phpmailer][download][type] = git
libraries[phpmailer][download][url] = https://github.com/Synchro/PHPMailer.git
libraries[phpmailer][download][revision] = d3802c597bff8f6c2ccfa3eab2a511aa01b8d68f
libraries[phpmailer][download][branch] = master

;libraries[annotator][download][type] = file
;libraries[annotator][download][url] = https://github.com/openannotation/annotator/releases/download/v1.2.10/annotator.1.2.10.zip
;libraries[annotator][download][subtree] = annotator.1.2.10

libraries[spyc][download][type] = file
libraries[spyc][download][url] = https://github.com/mustangostang/spyc/archive/0.6.2.zip
libraries[spyc][directory_name] = spyc

libraries[aws][download][type] = file
libraries[aws][download][url] = https://github.com/aws/aws-sdk-php/releases/download/3.15.5/aws.zip
libraries[aws][directory_name] = aws

libraries[cycle][download][type] = file
libraries[cycle][download][url] = http://malsup.github.io/min/jquery.cycle.all.min.js
libraries[cycle][directory_name] = jquery.cycle

libraries[masonry][download][type] = file
libraries[masonry][download][url] = https://npmcdn.com/masonry-layout@3.3.2/dist/masonry.pkgd.min.js
libraries[masonry][directory_name] = masonry

libraries[autopager][download][type] = file
libraries[autopager][download][url] = https://bitbucket.org/luksak/jquery-autopager/raw/2100c39767f97f6da18882aadca7b908c703e450/jquery.autopager-1.0.0.js
libraries[autopager][download][subtree] = autopager

libraries[timelinejs][download][type] = file
libraries[timelinejs][download][url] = https://github.com/NUKnightLab/TimelineJS3/archive/3.6.5.tar.gz

; PHP encryption libraries (REAL AES module dependency)
libraries[php-encryption][download][type] = file
libraries[php-encryption][download][url] = https://github.com/defuse/php-encryption/archive/522859f0b3f35fe83be5803ede83af3f517bfd5b.zip

; Spectrum Colorpicker
libraries[bgrins-spectrum][download][type] = file
libraries[bgrins-spectrum][download][url] =  https://github.com/bgrins/spectrum/archive/master.zip

; =====================
; Utilities and APIs
; =====================

; Overrides Panopoly's Ctools to apply custom patches.
projects[ctools][version] = 1.15
projects[ctools][subdir] = contrib
; Panopoly's patch.
projects[ctools][patch][1907256] = "https://www.drupal.org/files/issues/2018-03-26/views_panes-more_link_text-1000146-28.patch"
; Fix PECE Annotation Save&Continue issue.
projects[ctools][patch][1907256] = "https://www.drupal.org/files/issues/2018-05-23/ctools-modal-1907256-9.patch"
; @TODO: Update and reapply the following patch if needed. @see https://www.drupal.org/project/ctools/issues/2671150
; projects[ctools][patch][2671150] = "https://www.drupal.org/files/issues/ctools-2671150-1.patch"

; Overrides panopoly's Libraries.
projects[libraries][version] = 2.5
projects[libraries][subdir] = contrib

; Overrides panopoly's features.
projects[features][version] = 2.11
projects[features][subdir] = contrib

projects[xautoload][version] = 5.7
projects[xautoload][subdir]  = contrib

projects[prevent_js_alerts][version] = 1.0
projects[prevent_js_alerts][subdir] = contrib

projects[pathauto_entity][version] = 1.0
projects[pathauto_entity][subdir] = contrib

projects[subpathauto][version] = 1.3
projects[subpathauto][subdir] = contrib

projects[site_notice][version] = 1.4
projects[site_notice][subdir] = contrib

; =====================
; Views
; =====================

; Overrides panopoly's views to apply custom patches.
projects[views][version] = 3.23
projects[views][subdir] = contrib
; Applies Panopoly's specific patches.
projects[views][patch][2037469] = https://www.drupal.org/files/issues/views-exposed-sorts-2037469-26.patch
projects[views][patch][2977851] = https://www.drupal.org/files/issues/2019-03-13/2977851-views-php72-count-8.patch

projects[views_infinite_scroll][version] = 2.1
projects[views_infinite_scroll][subdir] = contrib

projects[views_litepager][version] = 3.0
projects[views_litepager][subdir] = contrib

projects[draggableviews][version] = 2.1
projects[draggableviews][subdir] = contrib

projects[tvi][version] = 1.0
projects[tvi][subdir] = contrib

projects[better_exposed_filters][version] = 3.6
projects[better_exposed_filters][subdir] = contrib

projects[masonry][version] = 3.0-beta1
projects[masonry][subdir] = contrib

projects[masonry_views][version] = 3.0
projects[masonry_views][subdir] = contrib

; =====================
; Administration
; =====================

projects[admin_menu][version] = 3.0-rc6
projects[admin_menu][subdir]  = contrib

projects[adminimal_admin_menu][version] = 1.9
projects[adminimal_admin_menu][subdir]  = contrib

; Overrides panopoly's module_filter.
projects[module_filter][version] = 2.2
projects[module_filter][subdir]  = contrib

projects[coffee][version] = 2.3
projects[coffee][subdir]  = contrib

projects[fpa][version] = 2.6
projects[fpa][subdir]  = contrib

projects[filter_perms][version] = 1.0
projects[filter_perms][subdir]  = contrib

projects[total_control][version] = 2.4
projects[total_control][subdir] = contrib

; =====================
; Configuration Management
; =====================

projects[diff][version] = 3.4
projects[diff][subdir] = contrib

; =====================
; Security
; =====================

; projects[seckit][subdir] = contrib
; projects[username_enumeration_prevention][subdir] = contrib
; projects[password_policy][subdir] = contrib

; Login Security
projects[login_security][subdir] = contrib
projects[login_security][version] = 1.9

; Key
projects[key][subdir] = contrib
projects[key][version] = 3.4

; Encrypt
projects[encrypt][subdir] = contrib
projects[encrypt][version] = 2.3

; Real AES PHP encryption
projects[real_aes][subdir] = contrib
projects[real_aes][version] = 1.2

; Honeypot
projects[honeypot][subdir] = contrib
projects[honeypot][version] = 1.25

; Role Delegation
projects[role_delegation][subdir] = contrib
projects[role_delegation][version] = 1.1

; User Protect
projects[userprotect][subdir] = contrib
projects[userprotect][version] = 1.2

; =====================
; Panels
; =====================

; Overrides Panopoly's panelizer.
projects[panelizer][version] = 3.4
projects[panelizer][subdir] = contrib
projects[panelizer][patch][2812807] = https://www.drupal.org/files/issues/panelizer--2812807--provide-entity-on-access-hooks.patch
; Panopoly's v1.57 patches.
projects[panelizer][patch][1549608] = https://www.drupal.org/files/issues/panelizer-n1549608-26.patch
projects[panelizer][patch][2788851] = https://www.drupal.org/files/issues/panelizer-administer-panelizer-2788851-2.patch

; Overrides panopoly's panels.
projects[panels][version] = 3.9
projects[panels][subdir] = contrib
; Panopoly's v1.57 patches.
projects[panels][patch][1570120] = https://www.drupal.org/files/issues/move-image-1570120-31.patch
projects[panels][patch][2897658] = https://www.drupal.org/files/issues/panels-menu-block-ipe-2897658-3.patch

projects[fieldable_panels_panes][version] = 1.13
projects[fieldable_panels_panes][subdir] = contrib
projects[fieldable_panels_panes][patch][2814117] = https://www.drupal.org/files/issues/fieldable_panels_panes--access_hook--2814117-1.patch

; =====================
; Panopoly
; =====================

; The Panopoly Foundation
projects[panopoly_admin][version] = 1.70
projects[panopoly_admin][subdir] = contrib

projects[panopoly_core][version] = 1.70
projects[panopoly_core][subdir] = contrib

projects[panopoly_images][version] = 1.70
projects[panopoly_images][subdir] = contrib

projects[panopoly_magic][version] = 1.70
projects[panopoly_magic][subdir] = contrib

projects[panopoly_theme][version] = 1.70
projects[panopoly_theme][subdir] = contrib

projects[panopoly_widgets][version] = 1.70
projects[panopoly_widgets][subdir] = contrib

projects[panopoly_users][version] = 1.70
projects[panopoly_users][subdir] = contrib

; The Panopoly Toolset
projects[panopoly_pages][version] = 1.70
projects[panopoly_pages][subdir] = contrib

projects[panopoly_search][version] = 1.70
projects[panopoly_search][subdir] = contrib
projects[panopoly_search][patch][] = "./patches/panopoly-remove_panelizer_data_alter_callback.patch"

projects[panopoly_wysiwyg][version] = 1.70
projects[panopoly_wysiwyg][subdir] = contrib

; For running the automated tests.
projects[panopoly_test][version] = 1.70
projects[panopoly_test][subdir] = contrib

; The Panopoly Radix

projects[radix_views][version] = 1.0
projects[radix_views][subdir] = contrib

;projects[radix_colorizer][version] = 1.x-dev
;projects[radix_colorizer][subdir] = contrib
;projects[radix_admin][version] = 3.x-dev
;projects[radix_admin][subdir] = contrib

; =====================
; Interface
; =====================

;projects[breakpointsjs][version] = 2.x-dev
;projects[breakpointsjs][subdir] = contrib

; =====================
; Entities
; =====================

projects[eck][version] = 2.0-rc10
projects[eck][subdir]  = contrib

projects[entity_view_mode][version] = 1.0-rc1
projects[entity_view_mode][subdir] = contrib

; Overrides panopoly's entityreference.
projects[entityreference][version] = 1.5
projects[entityreference][subdir] = contrib
projects[entityreference][patch][1423778] = "https://www.drupal.org/files/issues/entityreference-1423778-brokenhandler.diff"

projects[entityreference_view_widget][version] = 2.1
projects[entityreference_view_widget][subdir] = contrib

projects[er_viewmode][version] = 1.0-alpha1
projects[er_viewmode][subdir] = contrib

projects[entityconnect][version] = 2.0-rc2
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

projects[ckeditor][version] = 1.16
projects[ckeditor][subdir] = contrib

projects[manualcrop][version] = 1.7
projects[manualcrop][subdir] = contrib

projects[mimedetect][version] = 1.1
projects[mimedetect][subdir] = contrib

; =====================
; Fields
; =====================
; Overrides Panopoly's link.
projects[link][version] = 1.6
projects[link][subdir] = contrib

; Overrides Panopoly's linkit.
projects[linkit][version] = 3.5
projects[linkit][subdir] = contrib
projects[linkit][patch][2651404] = https://www.drupal.org/files/issues/linkit-add-to-any-element-2651404-3.patch

projects[languagefield][version] = 1.7
projects[languagefield][subdir] = contrib

; Node Access User Reference
projects[nodeaccess_userreference][subdir] = contrib
projects[nodeaccess_userreference][version] = 3.10
projects[nodeaccess_userreference][patch][] = ./patches/nodeaccess_userreference-fix_install_phase_requirement_error.patch


; Color field
projects[color_field][subdir] = contrib
projects[color_field][version] = 1.8

; =====================
; Search
; =====================

; Search API
; Overrides panopoly's search_api settings.
projects[search_api][subdir] = contrib
projects[search_api][version] = 1.26
projects[search_api][patch][] = ./patches/search_api_fix-composer-friendly-dependecies-issue.patch

; =====================
; Themes
; =====================

projects[radix][type] = theme
projects[radix][version] = 3.0-rc2
projects[radix][subdir] = contrib

; Adminimal Theme for admin
projects[adminimal_theme][type] = theme
projects[adminimal_theme][version] = 1.26
projects[adminimal_theme][subdir] = contrib

; PECE Base Theme
projects[scholarly_lite][type] = theme
projects[scholarly_lite][version] = 1.1
projects[scholarly_lite][subdir] = contrib

; =====================
; Other
; =====================

; Colorizer
;projects[colorizer][version] = 1.7
;projects[colorizer][subdir]  = contrib

; Rules
projects[rules][subdir] = contrib
projects[rules][version] = 2.12
projects[rules][patch][2189645] = https://www.drupal.org/files/issues/d7_component_caches.patch

; Translation
projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 2.2

; Organic groups
projects[og][subdir] = contrib
projects[og][version] = 2.10

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
projects[profile2][version] = 1.6
;projects[profile2][patch][1273026] = https://www.drupal.org/files/ctools-profile2_from_user-1273026-10.patch
projects[profile2][patch][1307538] = https://www.drupal.org/files/issues/profile2-fix_entity_info_failure_during_install-1307538-10-7.x-1.x-dev.patch

; GMap
projects[gmap][subdir] = contrib
projects[gmap][version] = 2.11

; External link
projects[extlink][subdir] = contrib
projects[extlink][version] = 1.20

; Real Name
projects[realname][subdir] = contrib
projects[realname][version] = 1.4

; TagCloud
projects[tagclouds][version] = 1.12
projects[tagclouds][subdir]  = contrib
projects[tagclouds][patch][]  = ./patches/tagclouds_fix-composer-friendly-dependecies-issue.patch

; Taxonomy Access Fix
projects[taxonomy_access_fix][subdir] = contrib
projects[taxonomy_access_fix][version] = 2.4

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
projects[amber][version] = 1.x-dev
projects[amber][patch][2945946] = "https://www.drupal.org/files/issues/amber-mysql5.7_compatibility-2945946-4.patch"

; Backup and Migrate
projects[backup_migrate][subdir] = contrib
projects[backup_migrate][version] = 3.6

; Node Expiration
projects[node_expire][subdir] = contrib
projects[node_expire][version] = 2.2

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
projects[services][version] = 3.25

; Services Views
projects[services_views][subdir] = contrib
projects[services_views][version] = 1.3

; =====================
; Integrations
; =====================

; Job scheduler
projects[job_scheduler][subdir] = contrib
projects[job_scheduler][version] = 2.0

; Feeds
projects[feeds][subdir] = contrib
projects[feeds][version] = 2.0-beta4

; Bibliography
projects[biblio][subdir] = contrib
projects[biblio][version] = 1.0

; Bibliography Zotero
projects[biblio_zotero][subdir] = contrib
projects[biblio_zotero][version] = 1.0-alpha3

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
