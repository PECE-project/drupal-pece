<?php
// Plugin definition
$plugin = array(
  'title' => t('Bartlett (deprecated)'),
  'icon' => 'radix-bartlett.png',
  'file' => 'radix_bartlett.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_bartlett',
  'category' => t('Panopoly'),
  'theme' => 'radix_bartlett',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
  ),
);
