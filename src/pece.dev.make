---
core: 7.x
api: 2

; =====================
; Debuging
; =====================

projects:
   subdir: dev

; =====================
; Other
; =====================

projects[devel][subdir] = dev
projects[drush_clone][subdir] = dev
projects[drush_entity][subdir] = dev
projects[module_builder][subdir] = dev
projects[stage_file_proxy][subdir] = dev
projects[environment_indicator][subdir] = dev
projects[search_krumo][subdir] = dev

; =====================
; Tests
; =====================

projects[seeds][type] = module
projects[seeds][download][type] = git
projects[seeds][download][url] = https://github.com/lucasconstantino/drupal-seeds.git
projects[seeds][subdir] = dev
