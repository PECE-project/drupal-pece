<?php
// Plugin definition
$plugin = array(
  'title' => t('Burr (deprecated)'),
  'icon' => 'radix-burr.png',
  'file' => 'radix_burr.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_burr',
  'category' => t('Panopoly'),
  'theme' => 'radix_burr',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentmain' => t('Content'),
  ),
);
