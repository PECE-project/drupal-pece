<?php
// Plugin definition
$plugin = array(
  'title' => t('Rolph (deprecated)'),
  'icon' => 'radix-rolph.png',
  'file' => 'radix_rolph.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_rolph',
  'category' => t('Panopoly'),
  'theme' => 'radix_rolph',
  'regions' => array(
    'header' => t('Header'),
    'quarter1' => t('Quarter 1 Column'),
    'quarter2' => t('Quarter 2 Column'),
    'quarter3' => t('Quarter 1 Column'),
    'quarter4' => t('Quarter 2 Column'),
    'footer' => t('Footer'),
  ),
);
