<?php
// Plugin definition
$plugin = array(
  'title' => t('Brown (deprecated)'),
  'icon' => 'radix-brown.png',
  'file' => 'radix_brown.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_brown',
  'category' => t('Panopoly'),
  'theme' => 'radix_brown',
  'regions' => array(
    'slider' => t('Slider'),
    'slidergutter' => t('Slider Gutter'),
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'column3' => t('Third Column'),
    'footercolumn1' => t('Footer First Column'),
    'footercolumn2' => t('Footer Second Column'),
    'footercolumn3' => t('Footer Third Column'),
  ),
);
