<?php

/**
 * @file
 * Serves administrative pages for the Respond.js module
 */

/**
 * Implements hook_admin().
 *
 * Respond.js administration settings
 */
function respondjs_admin() {
  $form = array();

  $form['respondjs_scope'] = array(
    '#type'           => 'select',
    '#title'          => t('Where should respond.js be included?'),
    '#description'    => t('A script with a significant visual impact like respond.js belongs in the &lt;head&gt; of a document.<br> However, in some cases it causes problems and you can move it to the footer using this configuration option.'),
    '#options'        => array(
      'header' => t('header'),
      'footer' => t('footer'),
    ),
    '#default_value'  => variable_get('respondjs_scope', RESPONDJS_SCOPE_DEFAULT),
  );

  $form['respondjs_quiet'] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Do not warn me about CSS aggregation.'),
    '#description'    => t('Check this box if you\'d rather not see the warning about CSS aggregation.<br> Disabling the warning will not make the respond.js function properly, but it will suppress the error message.'),
    '#default_value'  => variable_get('respondjs_quiet', RESPONDJS_QUIET_DEFAULT),
  );

  return system_settings_form($form);
}

