<?php
// Plugin definition
$plugin = array(
  'title' => t('Webb (deprecated)'),
  'icon' => 'radix-webb.png',
  'file' => 'radix_webb.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_webb',
  'category' => t('Panopoly'),
  'theme' => 'radix_webb',
  'regions' => array(
    'header' => t('Header'),
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
  ),
);
