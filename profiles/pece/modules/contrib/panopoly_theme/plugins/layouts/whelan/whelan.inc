<?php
// Plugin definition
$plugin = array(
  'title' => t('Whelan (deprecated)'),
  'icon' => 'radix-whelan.png',
  'file' => 'radix_whelan.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_whelan',
  'category' => t('Panopoly'),
  'theme' => 'radix_whelan',
  'regions' => array(
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'contentmain' => t('Content'),
  ),
);
