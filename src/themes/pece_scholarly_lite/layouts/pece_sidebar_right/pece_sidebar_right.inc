<?php
/**
 * PECE Sidebar Right layout definition.
 * Based on Bootstrap grid system.
 */

module_load_include('inc', 'pece_core', 'pece_core.functions');

$plugin = array(
  'title' => t('PECE Sidebar Right'),
  'icon' => 'pece-sidebar-right.png',
  'category' => t('PECE'),
  'theme' => 'pece_sidebar_right',
  'regions' => array(
    'content' => t('Content'),
    'sidebar' => t('Sidebar'),
  ),
  // 'settings form' => 'pece_sidebar_right_layout_settings_form',
  // 'settings submit' => 'pece_sidebar_right_layout_settings_form_submit',
  // 'settings validate' => 'pece_sidebar_right_layout_validate',
  // 'defaults' => array(
  //   'sidebar' => array(
  //     'size' => 'col-md-3',
  //   ),
  // ),
);
