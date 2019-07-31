<?php

/**
 * @file
 * Plugin to provide an relationship handler for a profile2 from a user.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Profile2 from user'),
  'keyword' => 'profile2',
  'description' => t('Adds a profile2 from a user context; if multiple profile types are selected, this will get the "first" type only.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'context' => 'ctools_profile2_from_user_context',
  'edit form' => 'ctools_profile2_from_user_settings_form',
  'defaults' => array('type' => ''),
);

/**
 * Return a new context based on an existing context.
 */
function ctools_profile2_from_user_context($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (empty($context->data->uid)) {
    return ctools_context_create_empty('entity:profile2', NULL);
  }

  if (isset($context->data->uid) && isset($conf['type'])) {
    // Load the user that is the author of the node.
    $uid = $context->data->uid;
    $type = $conf['type'];
    $profile = profile2_load_by_user($uid, $type);

    // Send it to ctools.
    return ctools_context_create('entity:profile2', $profile);
  }
}

/**
 * Settings form for the relationship.
 */
function ctools_profile2_from_user_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $options = array();
  foreach (profile2_get_types() as $type => $profile_type) {
    $options[$type] = $type;
  }
  $form['type'] = array(
    '#title' => t('Profile type'),
    '#type' => 'select',
    '#options' => $options,
    '#multiple' => FALSE,
    '#default_value' => $conf['type'],
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );

  return $form;
}
