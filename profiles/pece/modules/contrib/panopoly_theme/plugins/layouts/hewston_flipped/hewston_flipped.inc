<?php
// Plugin definition
$plugin = array(
  'title' => t('Hewston Flipped (deprecated)'),
  'icon' => 'radix-hewston-flipped.png',
  'file' => 'radix_hewston_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_hewston_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_hewston_flipped',
  'regions' => array(
    'slider' => t('Slider'),
    'slidergutter' => t('Slider Gutter'),
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'column3' => t('Third Column'),
  ),
);
