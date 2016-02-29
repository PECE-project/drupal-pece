<?php
// Plugin definition
$plugin = array(
  'title' => t('Harris (deprecated)'),
  'icon' => 'radix-harris.png',
  'file' => 'radix_harris.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_harris',
  'category' => t('Panopoly'),
  'theme' => 'radix_harris',
  'regions' => array(
    'header' => t('Header'),
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'contentmain' => t('Content'),
  ),
);
