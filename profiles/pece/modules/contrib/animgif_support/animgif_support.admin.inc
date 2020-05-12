<?php

/**
 * @file
 * Admin page callbacks for the animgif_support module.
 *
 * Developed by Dénes Szabó.
 * denes.szabo@internode.hu
 * http://internode.hu
 * .
 */

/**
 * Form builder; Configure site animated GIF image toolkit usage.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function animgif_support_settings_form() {

  $has_imagick = extension_loaded('imagick');
  $has_gifresizer = libraries_load('gifresizer');

  $options = [];

  $active = variable_get('animgif_support_gif_handler', 'gifresizer');
  if ($has_gifresizer) {
    $options['gifresizer'] = 'GIFResizer';
  }

  if ($has_imagick) {
    $options['imagick'] = 'Imagick';
  }

  if (empty($options[$active])) {
    $active = '';
    if (count($options)) {
      reset($options);
      $active = key($options);
    }
  }

  $form['animgif_support_gif_handler'] = array(
    '#type' => 'radios',
    '#title' => t('Available GIF handler library'),
    '#default_value' => $active,
    '#options' => $options,
    '#description' => t('Choose GIF re-sizer library from available list.'),
  );

  return system_settings_form($form);
}
