<?php

/**
 * @file
 * Plugin definition for the Authentication key type.
 */

$plugin = array(
  'label' => t('Authentication'),
  'description' => t('A generic key type to use for a password or API key that does not belong to any other defined key type.'),
  'group' => 'authentication',
  'key value' => array(
    'plugin' => 'text_field',
  ),
);
