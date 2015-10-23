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

/**
 * Layout settings form.
 */
// function pece_sidebar_right_layout_settings_form($display, $layout, $settings) {
//   $settings = pece_array_extend($layout['defaults'], $settings);
//
//   $form['sidebar']['size'] = array(
//     '#type' => 'select',
//     '#title' => t('Sidebar size'),
//     '#description' => t('Sidebar region size equivalent to the layout width.'),
//     '#options' => array(
//       'col-md-1' => t('8,33%'),
//       'col-md-2' => t('16,66%'),
//       'col-md-3' => t('25%'),
//       'col-md-4' => t('33,33%'),
//       'col-md-5' => t('41,66%'),
//       'col-md-6' => t('50%'),
//       'col-md-7' => t('58,33%'),
//       'col-md-8' => t('66,66%'),
//       'col-md-9' => t('75%'),
//       'col-md-10' => t('83,33%'),
//       'col-md-11' => t('91,66%'),
//     ),
//     '#default_value' => $settings['sidebar']['size'],
//   );
//
//   return $form;
// }

/**
 * Preprocess variables for PECE Sidebar Right.
 */
// function template_preprocess_pece_sidebar_right(&$variables, $theme) {
//   dsm(array($variables, $theme));
// }
