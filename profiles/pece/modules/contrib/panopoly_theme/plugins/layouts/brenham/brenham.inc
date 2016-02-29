<?php
// Plugin definition
$plugin = array(
  'title' => t('Brenham (deprecated)'),
  'icon' => 'radix-brenham.png',
  'file' => 'radix_brenham.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_brenham',
  'category' => t('Panopoly'),
  'theme' => 'radix_brenham',
  'regions' => array(
    'header' => t('Header'),
    'sidebar' => t('Content Sidebar'),
    'contentmain' => t('Content'),
  ),
);
