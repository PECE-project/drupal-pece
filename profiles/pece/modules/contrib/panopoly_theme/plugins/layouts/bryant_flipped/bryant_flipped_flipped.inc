<?php
// Plugin definition
$plugin = array(
  'title' => t('Bryant Flipped (deprecated)'),
  'icon' => 'radix-bryant-flipped.png',
  'file' => 'radix_bryant_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_bryant_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_bryant_flipped',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentmain' => t('Content'),
  ),
);
