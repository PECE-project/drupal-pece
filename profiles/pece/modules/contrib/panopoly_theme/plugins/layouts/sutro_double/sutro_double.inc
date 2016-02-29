<?php
// Plugin definition
$plugin = array(
  'title' => t('Sutro Double (deprecated)'),
  'icon' => 'radix-sutro-double.png',
  'file' => 'radix_sutro_double.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_sutro_double',
  'category' => t('Panopoly'),
  'theme' => 'radix_sutro_double',
  'regions' => array(
    'header' => t('Header'),
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'middle' => t('Middle'),
    'secondcolumn1' => t('Bottom First Column'),
    'secondcolumn2' => t('Bottom Second Column'),
    'footer' => t('Footer'),
  ),
);
