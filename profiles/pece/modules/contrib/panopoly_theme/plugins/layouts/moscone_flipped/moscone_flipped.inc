<?php
// Plugin definition
$plugin = array(
  'title' => t('Moscone Flipped (deprecated)'),
  'icon' => 'radix-moscone-flipped.png',
  'file' => 'radix_moscone_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_moscone_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_moscone_flipped',
  'regions' => array(
    'header' => t('Header'),
    'sidebar' => t('Content Sidebar'),
    'contentmain' => t('Content'),
    'footer' => t('Footer'),
  ),
);
