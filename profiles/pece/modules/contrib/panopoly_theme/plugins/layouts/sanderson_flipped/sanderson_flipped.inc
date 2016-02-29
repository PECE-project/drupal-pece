<?php
// Plugin definition
$plugin = array(
  'title' => t('Sanderson Flipped (deprecated)'),
  'icon' => 'radix-sanderson-flipped.png',
  'file' => 'radix_sanderson_flipped.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_sanderson_flipped',
  'category' => t('Panopoly'),
  'theme' => 'radix_sanderson_flipped',
  'regions' => array(
    'column1' => t('Row 1: First Column'),
    'column2' => t('Row 1: Second Column'),
    'column3' => t('Row 1: Third Column'),
    'secondarycolumn1' => t('Row 2: First Column'),
    'secondarycolumn2' => t('Row 2: Second Column'),
  ),
);
