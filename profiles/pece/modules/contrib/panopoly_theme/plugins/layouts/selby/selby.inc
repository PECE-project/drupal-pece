<?php
// Plugin definition
$plugin = array(
  'title' => t('Selby (deprecated)'),
  'icon' => 'radix-selby.png',
  'file' => 'radix_selby.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_selby',
  'category' => t('Panopoly'),
  'theme' => 'radix_selby',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
    'contentfooter' => t('Content Footer'),
  ),
);
