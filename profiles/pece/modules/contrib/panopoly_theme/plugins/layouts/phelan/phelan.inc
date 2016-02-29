<?php
// Plugin definition
$plugin = array(
  'title' => t('Phelan (deprecated)'),
  'icon' => 'radix-phelan.png',
  'file' => 'radix_phelan.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_phelan',
  'category' => t('Panopoly'),
  'theme' => 'radix_phelan',
  'regions' => array(
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
  ),
);
