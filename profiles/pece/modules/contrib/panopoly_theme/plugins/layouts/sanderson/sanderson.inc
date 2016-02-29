<?php
// Plugin definition
$plugin = array(
  'title' => t('Sanderson (deprecated)'),
  'icon' => 'radix-sanderson.png',
  'file' => 'radix_sanderson.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_sanderson',
  'category' => t('Panopoly'),
  'theme' => 'radix_sanderson',
  'regions' => array(
    'column1' => t('Row 1: First Column'),
    'column2' => t('Row 1: Second Column'),
    'secondarycolumn1' => t('Row 2: First Column'),
    'secondarycolumn2' => t('Row 2: Second Column'),
    'secondarycolumn3' => t('Row 2: Third Column'),
  ),
);
