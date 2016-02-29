<?php
// Plugin definition
$plugin = array(
  'title' => t('Moscone (deprecated)'),
  'icon' => 'radix-moscone.png',
  'file' => 'radix_moscone.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_moscone',
  'category' => t('Panopoly'),
  'theme' => 'radix_moscone',
  'regions' => array(
    'header' => t('Header'),
    'sidebar' => t('Content Sidebar'),
    'contentmain' => t('Content'),
    'footer' => t('Footer'),
  ),
);
