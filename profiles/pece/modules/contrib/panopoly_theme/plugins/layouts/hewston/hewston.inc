<?php
// Plugin definition
$plugin = array(
  'title' => t('Hewston (deprecated)'),
  'icon' => 'radix-hewston.png',
  'file' => 'radix_hewston.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_hewston',
  'category' => t('Panopoly'),
  'theme' => 'radix_hewston',
  'regions' => array(
    'slider' => t('Slider'),
    'slidergutter' => t('Slider Gutter'),
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'column3' => t('Third Column'),
  ),
);
