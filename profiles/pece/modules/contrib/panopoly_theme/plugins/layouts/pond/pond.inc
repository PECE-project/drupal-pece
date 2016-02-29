<?php
// Plugin definition
$plugin = array(
  'title' => t('Pond (deprecated)'),
  'icon' => 'radix-pond.png',
  'file' => 'radix_pond.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_pond',
  'category' => t('Panopoly'),
  'theme' => 'radix_pond',
  'regions' => array(
    'header' => t('Header'),
    'column1' => t('Row 1: First Column'),
    'column2' => t('Row 1: Second Column'),
    'column3' => t('Row 1: Third Column'),
    'secondarycolumn1' => t('Row 2: First Column'),
    'secondarycolumn2' => t('Row 2: Second Column'),
    'secondarycolumn3' => t('Row 2: Third Column'),
    'footer' => t('Footer'),
  ),
);
