<?php

/**
 * @file
 * Contains integration with Devel generate modules.
 * Provides possibility to generate dummy profiles for users.
 */

/**
 * Form that allows to generate a user profiles with dummy data.
 */
function profile2_generate_form($form, &$form_state) {

  // Generate a list with available profile types.
  $profile_types = profile2_get_types();
  foreach ($profile_types as $id => $type) {
    $profile_types[$id] = $type->label;
  }

  $form['profile2_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Generate profiles of the following types'),
    '#description' => t('Select profile type(s) to create profile. If no types are selected, profiles of all types will be generated.'),
    '#options' => $profile_types,
  );

  $roles_list = user_roles(TRUE);

  // Don't show authorized role.
  unset($roles_list[DRUPAL_AUTHENTICATED_RID]);

  $form['profile2_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Generate profiles for following user roles'),
    '#options' => $roles_list,
  );

  $form['profile2_generate_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of profiles per type'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => 50,
    '#size' => 10,
  );

  $form['profile2_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete existing profiles'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
  );

  return $form;
}

/**
 * Submit callback for profile2_generate_form().
 * Generates profiles for users.
 */
function profile2_generate_form_submit($form, &$form_state) {

  $values = $form_state['values'];

  // Initial database query that allows to fetch all user ids except anonymous.
  $query = db_select('users', 'u');
  $query->fields('u', array('uid'));
  $query->condition('u.uid', 0, '<>');

  // If user selected certain user roles - we need to filter by them.
  $roles_selected = array_filter($values['profile2_roles']);
  if (!empty($roles_selected)) {
    $query->innerJoin('users_roles', 'ur', 'ur.uid = u.uid');
    $query->condition('ur.rid', $roles_selected);
  }

  // Fetch uids for which profiles should be generated.
  $uids = $query->execute()->fetchCol('uid');

  // Delete all profiles before generation.
  if (!empty($values['profile2_delete'])) {

    $profile_ids = db_select('profile')
      ->fields('profile', array('pid'))
      ->execute()
      ->fetchCol('pid');

    profile2_delete_multiple($profile_ids);

    // Set message that indicates how much profiles were deleted.
    $message = format_plural(count($profile_ids), t('1 profile was deleted.'), t('@count profiles were deleted.'));
    drupal_set_message($message);
  }

  $new_pids = array();
  if (!empty($uids)) {

    // Get selected profile types. Load them all if no profile type was chosen.
    $profile_types = array_filter($values['profile2_types']);
    if (empty($profile_types)) {
      $profile_types = profile2_get_types();
    }

    // Generate user-defined amount of certain profile types.
    foreach ($profile_types as $profile_type_name => $profile_type) {
      $counter = 0;
      $uids_to_generate = $uids;
      while ($counter < $values['profile2_generate_limit'] && !empty($uids_to_generate)) {
        $uid = array_shift($uids_to_generate);

        // If user already has profile of certain type - skip the generation for it.
        if (profile2_load_by_user($uid, $profile_type_name)) {
          continue;
        }

        $profile2 = entity_create('profile2', array('type' => $profile_type_name, 'uid' => $uid));

        // Populate all core fields on behalf of field.module.
        module_load_include('fields.inc', 'devel_generate');
        module_load_include('inc', 'devel_generate');
        devel_generate_fields($profile2, 'profile2', $profile2->type);

        // Set profile language.
        $profile2->language = LANGUAGE_NONE;

        // Create new profile of the certain type.
        $new_pids[] = entity_save('profile2', $profile2);

        // Increase counter of generated profiles of certain type.
        $counter++;
      }
    }

  }

  // Show message that indicates how much profiles were created.
  $message = format_plural(count($new_pids), '1 profile were generated', '@count profiles were generated.');
  drupal_set_message($message);
}
