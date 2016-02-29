<?php
// Plugin definition
$plugin = array(
  'title' => t('Boxton (deprecated)'),
  'icon' => 'radix-boxton.png',
  'file' => 'radix_boxton.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_boxton',
  'category' => t('Panopoly'),
  'theme' => 'radix_boxton',
  'regions' => array(
    'contentmain' => t('Content'),
  ),
);
