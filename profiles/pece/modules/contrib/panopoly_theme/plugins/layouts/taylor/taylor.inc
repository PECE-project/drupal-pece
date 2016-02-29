<?php
// Plugin definition
$plugin = array(
  'title' => t('Taylor (deprecated)'),
  'icon' => 'radix-taylor.png',
  'file' => 'radix_taylor.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_taylor',
  'category' => t('Panopoly'),
  'theme' => 'radix_taylor',
  'regions' => array(
    'header' => t('Header'),
    'half' => t('Half Column'),
    'quarter1' => t('Quarter 1 Column'),
    'quarter2' => t('Quarter 2 Column'),
    'footer' => t('Footer'),
  ),
);
