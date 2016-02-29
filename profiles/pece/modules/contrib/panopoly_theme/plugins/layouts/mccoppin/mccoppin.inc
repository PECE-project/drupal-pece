<?php
// Plugin definition
$plugin = array(
  'title' => t('McCoppin (deprecated)'),
  'icon' => 'radix-mccoppin.png',
  'file' => 'radix_mccoppin.inc',
  'path' => drupal_get_path('module', 'radix_layouts') . '/plugins/layouts/radix_mccoppin',
  'category' => t('Panopoly'),
  'theme' => 'radix_mccoppin',
  'regions' => array(
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
    'column3' => t('Third Column'),
  ),
);
