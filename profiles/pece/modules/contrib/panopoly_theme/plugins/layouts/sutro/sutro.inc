<?php
// Plugin definition
$plugin = array(
  'title' => t('Sutro (deprecated)'),
  'icon' => 'radix-sutro.png',
  'file' => 'radix_sutro.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_sutro',
  'category' => t('Panopoly'),
  'theme' => 'radix_sutro',
  'regions' => array(
    'header' => t('Header'),
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'footer' => t('Footer'),
  ),
);
