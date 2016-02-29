<?php
// Plugin definition
$plugin = array(
  'title' => t('Bryant (deprecated)'),
  'icon' => 'radix-bryant.png',
  'file' => 'radix_bryant.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_bryant',
  'category' => t('Panopoly'),
  'theme' => 'radix_bryant',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentmain' => t('Content'),
  ),
);
