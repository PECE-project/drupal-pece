<?php
// Plugin definition
$plugin = array(
  'title' => t('Burr Flipped (deprecated)'),
  'icon' => 'radix-burr-flipped.png',
  'file' => 'radix_burr_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_burr_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_burr_flipped',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentmain' => t('Content'),
  ),
);
