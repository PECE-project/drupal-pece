<?php
// Plugin definition
$plugin = array(
  'title' => t('Brenham Flipped (deprecated)'),
  'icon' => 'radix-brenham-flipped.png',
  'file' => 'radix_brenham_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_brenham_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_brenham_flipped',
  'regions' => array(
    'header' => t('Header'),
    'sidebar' => t('Content Sidebar'),
    'contentmain' => t('Content'),
  ),
);
