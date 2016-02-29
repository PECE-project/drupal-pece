<?php
// Plugin definition
$plugin = array(
  'title' => t('Taylor Flipped (deprecated)'),
  'icon' => 'radix-taylor-flipped.png',
  'file' => 'radix_taylor_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_taylor_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_taylor_flipped',
  'regions' => array(
    'header' => t('Header'),
    'quarter1' => t('Quarter 1 Column'),
    'quarter2' => t('Quarter 2 Column'),
    'half' => t('Half Column'),
    'footer' => t('Footer'),
  ),
);
