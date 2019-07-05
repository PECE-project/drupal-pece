<?php

/**
 * @file
 * Plugin to provide an relationship handler for profile2 from user.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Profile2 from user'),
  'keyword' => 'profile2',
  'description' => t('Adds a profile2 type from a user context.'),
  'required context' => new ctools_context_required(t('User'), 'entity:user'),
  'context' => 'profile2_from_user_context',
  'edit form' => 'profile2_from_user_settings_form',
  'defaults' => array('type' => 'main'),
);

/**
 * Return a new context based on an existing context.
 */
function profile2_from_user_context($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data) || !isset($context->data->uid)) {
    return ctools_context_create_empty('entity:profile2', NULL);
  }

  // Load user's profile and return a ctools context from it.
  if ($profile = profile2_load_by_user($context->data, $conf['type'])) {
    return ctools_context_create('entity:profile2', $profile);
  }

  // In case when we can't load a profile, just return an empty context.
  return ctools_context_create_empty('entity:profile2', NULL);
}

/**
 * Settings form for the relationship.
 */
function profile2_from_user_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $options = array();
  foreach (profile2_get_types() as $type => $info) {
    $options[$type] = $info->label;
  }

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Select Profile2 Type'),
    '#options' => $options,
    '#default_value' => $conf['type'],
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );

  return $form;
}
