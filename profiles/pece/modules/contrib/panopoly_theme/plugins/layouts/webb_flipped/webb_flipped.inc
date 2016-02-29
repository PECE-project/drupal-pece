<?php
// Plugin definition
$plugin = array(
  'title' => t('Webb Flipped (deprecated)'),
  'icon' => 'radix-webb-flipped.png',
  'file' => 'radix_webb_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_webb_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_webb_flipped',
  'regions' => array(
    'header' => t('Header'),
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
  ),
);
