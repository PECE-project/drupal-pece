<?php

/**
 * @file
 *  Generate content, taxonomy, menu, and users via drush framework.
 */

/**
 * Implementation of hook_drush_command().
 */
function pece_demo_drush_command() {
  $items['pece-demo'] = array(
    'callback' => 'pece_demo_generate_demo_content',
    'description' => 'Generates PECE demo contents.',
  );

  return $items;
}
