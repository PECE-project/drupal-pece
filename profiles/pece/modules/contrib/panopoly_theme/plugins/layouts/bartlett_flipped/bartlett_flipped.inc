<?php
// Plugin definition
$plugin = array(
  'title' => t('Bartlett Flipped (deprecated)'),
  'icon' => 'radix-bartlett-flipped.png',
  'file' => 'radix_bartlett_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_bartlett_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_bartlett_flipped',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
  ),
);
