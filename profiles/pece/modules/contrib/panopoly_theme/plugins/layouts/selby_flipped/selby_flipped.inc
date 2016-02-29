<?php
// Plugin definition
$plugin = array(
  'title' => t('Selby Flipped (deprecated)'),
  'icon' => 'radix-selby-flipped.png',
  'file' => 'radix_selby_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_selby_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_selby_flipped',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
    'contentfooter' => t('Content Footer'),
  ),
);
