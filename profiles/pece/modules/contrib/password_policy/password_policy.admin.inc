<?php

/**
 * @file
 * Admin page callback file for the Password Policy module.
 */

/****************************************************************************/
/* Password policy admin settings                                           */
/****************************************************************************/

/**
 * Settings form display.
 */
function password_policy_admin_settings() {
  $form['force_change'] = array(
    '#type' => 'fieldset',
    '#title' => t('Force password change settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['force_change']['password_policy_force_change_reset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force password change on reset'),
    '#default_value' => variable_get('password_policy_force_change_reset', 0),
    '#description' => t('When a user requests a one-time login link, this option will require the user to change their password before continuing to browse the site.'),
  );
  $form['force_change']['password_policy_force_change_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Password change form path'),
    '#description' => t('If the module does not determine the path for the password change form, use this field to specify the correct path. For example: "user/[user:uid]/edit". Supported replacement patterns are [user:uid] and [user:name].'),
    '#default_value' => variable_get('password_policy_force_change_path', NULL),
  );
  $form['force_change']['password_policy_force_change_extra_allowed_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Extra allowed paths'),
    '#default_value' => variable_get('password_policy_force_change_extra_allowed_paths', _password_policy_default_force_change_extra_allowed_paths()),
    '#description' => t("Extra paths, one per line, that the user can access as normal when being forced to change their password. The '*' character is a wildcard. These paths are in addition to the minimally allowed paths for password changes, which are always allowed by Password Policy. This setting can be used, for example, to allow paths requested by custom AJAX on the password change page."),
  );

  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['expiration']['password_policy_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Admin (UID=1) password expires.'),
    '#default_value' => variable_get('password_policy_admin', 1),
    '#description' => t('Admin account password will obey expiration policy.'),
  );
  $form['expiration']['password_policy_begin'] = array(
    '#type' => 'radios',
    '#title' => t('Beginning of password expirations'),
    '#default_value' => variable_get('password_policy_begin', 0),
    '#options' => array('0' => t('After expiration time from setting a default policy (all passwords are valid during the expiration time from setting the default policy, and after that older than expiration time passwords expire).'), '1' => t('Setting a default policy (passwords older than expiration time expire after setting the default policy, retroactive behaviour).')),
  );
  $form['expiration']['password_policy_block'] = array(
    '#type' => 'radios',
    '#title' => t('Blocking expired accounts'),
    '#default_value' => variable_get('password_policy_block', 0),
    '#options' => array('0' => t('Expired accounts are blocked. Only administrators can unblock them. Once unblocked, users can log in and will be forced to change their password. If they do not log in and change their password within one day, they will be blocked again.'), '1' => t('Expired accounts are not blocked. Users whose accounts have expired will be forced to change their passwords at next login.')),
  );
  $form['expiration']['password_policy_expired_account_entries'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Entries per page on expired accounts page'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => variable_get('password_policy_expired_account_entries', 10),
    '#description' => t('The <a href="@expired-accounts-page">expired accounts page</a> lists all expired accounts to administrators.', array('@expired-accounts-page' => url('admin/people/expired'))),
  );

  // Visibility.
  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['visibility']['password_policy_show_restrictions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show all restrictions on password change page.'),
    '#default_value' => variable_get('password_policy_show_restrictions', 0),
    '#description' => t('List all password restrictions on the password change page. The list is displayed in addition to the default dynamic, JavaScript-generated list of only the restrictions the typed password does not meet. Enabling this setting allows a user who is not using JavaScript to see the password restrictions prior to submitting their password.'),
  );

  // E-mail notification settings.
  $form['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail notification settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['email']['password_policy_warning_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject of warning e-mail'),
    '#default_value' => variable_get('password_policy_warning_subject', PASSWORD_POLICY_DEFAULT_WARNING_SUBJECT),
    '#maxlength' => 180,
    '#description' => t('Customize the subject of the warning e-mail message, which is sent to remind of password expiration.') . _password_policy_warning_email_tokens_help(),
  );
  $form['email']['password_policy_warning_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body of warning e-mail'),
    '#default_value' => variable_get('password_policy_warning_body', PASSWORD_POLICY_DEFAULT_WARNING_BODY),
    '#rows' => 15,
    '#description' => t('Customize the body of the warning e-mail message, which is sent to remind of password expiration.') . _password_policy_warning_email_tokens_help(),
  );

  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#submit' => array('password_policy_admin_settings_reset_submit'),
  );

  return system_settings_form($form);
}

/**
 * Gets help for warning email tokens.
 */
function _password_policy_warning_email_tokens_help() {
  return ' ' . t('Available variables are: [user:name], [site:name], [site:url], [site:url-brief], [user:mail], [date:medium], [site:login-url], [user:edit-url], [password-policy:days-left], [password-policy:password-edit-url].');
}

/**
 * Submit hook for the reset button on the settings form.
 */
function password_policy_admin_settings_reset_submit($form, &$form_state) {
  variable_del('password_policy_admin');
  variable_del('password_policy_begin');
  variable_del('password_policy_block');
  variable_del('password_policy_show_restrictions');
  variable_del('password_policy_warning_subject');
  variable_del('password_policy_warning_body');
  variable_del('password_policy_force_change_reset');
  variable_del('password_policy_force_change_extra_allowed_paths');
  if (function_exists('variable_delete')) {
    variable_delete('password_policy_warning_subject');
    variable_delete('password_policy_warning_body');
  }
  drupal_set_message(t('The configuration options have been reset to their default values.'));
}

/**
 * Lists roles to which a policy applies.
 *
 * @param int $pid
 *   Policy id.
 *
 * @return string[]
 *   Array of role names.
 */
function _password_policy_admin_list_roles($pid) {
  $roles = array();
  $query = db_select('role', 'r', array('target' => 'slave'));
  $query->innerJoin('password_policy_role', 'p', 'p.rid = r.rid');
  $result = $query->fields('r', array('name'))
    ->condition('p.pid', $pid)
    ->execute();
  foreach ($result as $row) {
    $roles[] = check_plain($row->name);
  }
  return $roles;
}

/**
 * The list of the password policies.
 */
function password_policy_admin_list($form) {
  $result = db_select('password_policy', 'p',
    array(
      'fetch' => PDO::FETCH_ASSOC,
      'target' => 'slave',
    ))
    ->fields('p',
        array(
          'pid',
          'name',
          'enabled',
          'description',
          'created',
          'weight',
        ))
    ->orderBy('weight')
    ->execute();

  $form['#tree'] = TRUE;
  foreach ($result as $row) {
    $pid = $row['pid'];

    $form['policies'][$pid]['name'] = array(
      '#markup' => check_plain($row['name']),
    );
    $form['policies'][$pid]['roles'] = array(
      '#markup' => theme('item_list', array('items' => _password_policy_admin_list_roles($pid))),
    );
    $form['policies'][$pid]['enabled'] = array(
      '#type' => 'checkbox',
      '#default_value' => $row['enabled'],
    );
    $form['policies'][$pid]['view'] = array(
      '#type' => 'link',
      '#title' => 'view',
      '#href' => 'admin/config/people/password_policy/' . $pid,
    );
    $form['policies'][$pid]['edit'] = array(
      '#type' => 'link',
      '#title' => 'edit',
      '#href' => 'admin/config/people/password_policy/' . $pid . '/edit',
    );
    $form['policies'][$pid]['delete'] = array(
      '#type' => 'link',
      '#title' => 'delete',
      '#href' => 'admin/config/people/password_policy/' . $pid . '/delete',
    );
    $form['policies'][$pid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight for @title', array('@title' => $row['name'])),
      '#title_display' => 'invisible',
      '#default_value' => $row['weight'],
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );
  return $form;
}

/**
 * Submit hook for the form on the default list view.
 */
function password_policy_admin_list_submit($form, &$form_state) {
  foreach ($form_state['values']['policies'] as $pid => $policy) {
    db_update('password_policy')
      ->fields(array(
        'weight' => $policy['weight'],
      ))
      ->condition('pid', $pid)
      ->execute();
    // Ensure we don't reset the timestamp on policies that are already enabled.
    if ($policy['enabled']) {
      db_update('password_policy')
        ->fields(array(
          'enabled' => 1,
          'created' => _password_policy_get_request_time(),
        ))
        ->condition('pid', $pid)
        ->condition('enabled', 0)
        ->execute();
    }
    else {
      db_update('password_policy')
        ->fields(array('enabled' => 0))
        ->condition('pid', $pid)
        ->execute();
    }
  }

  drupal_set_message(t('The changes have been saved.'));
}

/**
 * Returns HTML for the password policy administration list.
 *
 * @param array $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 *
 * @see theme_filter_admin_overview()
 */
function theme_password_policy_admin_list(array $variables) {
  $form = $variables['form'];

  $rows = array();
  if (isset($form['policies']) && count($form['policies'])) {
    foreach (element_children($form['policies']) as $id) {
      $form['policies'][$id]['weight']['#attributes']['class'] = array('password-policy-order-weight');
      $rows[] = array(
        'data' => array(
          drupal_render($form['policies'][$id]['name']),
          drupal_render($form['policies'][$id]['roles']),
          drupal_render($form['policies'][$id]['enabled']),
          drupal_render($form['policies'][$id]['weight']),
          drupal_render($form['policies'][$id]['view']),
          drupal_render($form['policies'][$id]['edit']),
          drupal_render($form['policies'][$id]['delete']),
        ),
        'class' => array('draggable'),
      );
    }
  }
  if (empty($rows)) {
    unset($form['actions']['submit']);
  }
  $header = array(
    t('Name'),
    t('Roles'),
    t('Enabled'),
    t('Weight'),
    array(
      'data' => t('Operations'),
      'colspan' => 3,
    ),
  );
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'password-policy-order'),
    'empty' => t('There are currently no policies. <a href="!url">Add a new one</a>.',
      array('!url' => url('admin/config/people/password_policy/add'))),
  ));
  $output .= drupal_render_children($form);

  drupal_add_tabledrag('password-policy-order', 'order', 'sibling', 'password-policy-order-weight');

  return $output;
}

/**
 * The default view for the password policy.
 */
function password_policy_admin_view($policy) {
  $output = check_plain($policy['description']);
  $header = array(t('Name'), t('Constraint'));
  $rows = array();

  $roles = _password_policy_admin_list_roles($policy['pid']);
  if (!empty($roles)) {
    $rows[] = array(t('Roles'), theme('item_list', array('items' => $roles)));
  }
  if (!empty($policy['expiration'])) {
    $rows[] = array(t('Expiration'), $policy['expiration']);
  }
  if (!empty($policy['warning'])) {
    $rows[] = array(t('Warning'), check_plain($policy['warning']));
  }

  foreach ($policy['constraints'] as $key => $val) {
    $desc = _password_policy_constraint_description($key);
    $rows[] = array($desc['name'], $val);
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No policies defined.'), 'colspan' => 2));
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows));

  return $output;
}

/**
 * Form display for new or to be edited password policies.
 */
function password_policy_admin_form($form, &$form_state, $policy = NULL) {
  $form['policy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Policy'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['policy']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($policy['name']) ? $policy['name'] : '',
    '#maxlength' => 64,
    '#required' => TRUE,
  );
  $form['policy']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#default_value' => isset($policy['description']) ? $policy['description'] : '',
    '#size' => 128,
    '#maxlength' => 255,
  );

  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['roles']['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#options' => user_roles(TRUE),
    '#default_value' => isset($policy['roles']) ? $policy['roles'] : array(),
    '#description' => t('Select the roles that this policy will apply to.'),
  );

  $authentication_modules = _password_policy_get_authentication_modules();
  if (count($authentication_modules)) {
    $form['excluded_authentication_modules'] = array(
      '#type' => 'fieldset',
      '#title' => t('Excluded Authentication Modules'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['excluded_authentication_modules']['excluded_authentication_modules'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Excluded Authentication Modules'),
      '#options' => drupal_map_assoc($authentication_modules),
      '#default_value' => isset($policy['excluded_authentication_modules']) ? $policy['excluded_authentication_modules'] : array(),
      '#description' => t('Select the authentication modules that this policy will not apply to.'),
    );
  }

  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['expiration']['expiration'] = array(
    '#type' => 'textfield',
    '#title' => t('Password Expiration'),
    '#default_value' => isset($policy['expiration']) ? $policy['expiration'] : '0',
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t('The passwords will expire after this number of days. The users with expired passwords will be blocked. Setting this field to 0 will not put any password expiration constraints.'),
  );
  $form['expiration']['warning'] = array(
    '#type' => 'textfield',
    '#title' => t('Password Expiration Warning'),
    '#default_value' => isset($policy['warning']) ? $policy['warning'] : '',
    '#size' => 10,
    '#field_suffix' => t('days before password expiration'),
    '#description' => t("<p>When to send a password expiration warning e-mail.  To send warning e-mails on multiple days, enter numbers separated by commas.  For example, '30,7' will cause an expiration warning e-mail to be sent both 30 and 7 days before expiration. Leave blank to not send or display any warnings.</p><p><strong>Important:</strong> Drupal cron must be run once per day. Otherwise, warning e-mails might not be sent. The default Drupal cron configuration relies on site visitors to invoke cron. If your site might not receive visitors on a day, you should run cron from outside the site daily. See <a href='https://www.drupal.org/cron'>Setting Up Cron</a>.</p>"),
  );

  $form['constraints'] = array(
    '#type' => 'fieldset',
    '#title' => t('Constraints'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  foreach (_password_policy_constraints() as $constraint) {
    $desc = _password_policy_constraint_description($constraint);
    $form['constraints']['constraint_' . $constraint] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#default_value' => isset($policy['constraints'][$constraint]) ? $policy['constraints'][$constraint] : NULL,
      '#maxlength' => 3,
      '#title' => filter_xss($desc['name']),
      '#description' => filter_xss($desc['description']),
    );
  }

  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => is_array($policy) ? t('Save') : t('Create'),
  );

  if ($policy) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['actions']['pid'] = array(
      '#type' => 'hidden',
      '#value' => isset($policy['pid']) ? $policy['pid'] : '',
    );
  }

  return $form;
}

/**
 * Form validation hook for new or edited password policies.
 */
function password_policy_admin_form_validate($form, &$form_state) {
  $roles = array_filter($form_state['values']['roles']);
  if (empty($roles)) {
    form_set_error('roles', t('You must select at least one role for a policy to apply to.'));
  }
  _password_policy_validate_expiration_warning($form_state);
  if (_password_policy_validating_new_policy($form_state)) {
    _password_policy_validate_unique_policy_name($form_state);
  }
}

/**
 * Validates expiration warning.
 */
function _password_policy_validate_expiration_warning($form_state) {
  if (!empty($form_state['values']['warning']) && !preg_match('/^[0-9]+(,[0-9]+)*+$/', $form_state['values']['warning'])) {
    form_set_error('warning', t('Warning must be a number of days or comma-separated numbers of days. For example, "30" or "30,7".'));
  }
}

/**
 * Determines whether a new policy is being validated.
 *
 * The policy being validated could be either new or edited.
 */
function _password_policy_validating_new_policy($form_state) {
  return !isset($form_state['values']['pid']);
}

/**
 * Validates that the policy name is unique.
 */
function _password_policy_validate_unique_policy_name($form_state) {
  $query = db_select('password_policy', 'p')
    ->condition('p.name', $form_state['values']['name'])
    ->fields('p', array('pid'));
  $row_count = $query->execute()->rowCount();
  if ($row_count > 0) {
    form_set_error('name', t('A policy with the same name already exists. Please enter a different name.'));
  }
}

/**
 * Form submission hook for new or edited password policies.
 */
function password_policy_admin_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];

  if ($op == t('Delete')) {
    drupal_goto('admin/config/people/password_policy/' . $form_state['values']['pid'] . '/delete');
  }

  _password_policy_admin_form_save_policy($form_state);

  $form_state['redirect'] = 'admin/config/people/password_policy/list';
}

/**
 * Saves policy from submitted policy form.
 */
function _password_policy_admin_form_save_policy($form_state) {
  $policy = _password_policy_admin_form_get_policy($form_state);
  password_policy_save_policy($policy);
  _password_policy_admin_form_set_saved_message($policy);
}

/**
 * Gets policy from submitted policy form.
 *
 * @param array $form_state
 *   Form state.
 *
 * @return array
 *   Policy array.
 */
function _password_policy_admin_form_get_policy(array $form_state) {
  $form_values = $form_state['values'];
  $policy = array(
    'name' => $form_values['name'],
    'description' => $form_values['description'],
    'constraints' => _password_policy_admin_form_get_constraints($form_state),
    'expiration' => $form_values['expiration'],
    'warning' => $form_values['warning'],
    'roles' => $form_values['roles'],
    'excluded_authentication_modules' => isset($form_values['excluded_authentication_modules']) ? $form_values['excluded_authentication_modules'] : array(),
  );
  if (isset($form_values['pid'])) {
    // Editing an existing policy. Get pid.
    $policy['pid'] = $form_values['pid'];
  }
  else {
    // Adding a new policy. Disable by default.
    $policy['enabled'] = 0;
  }

  return $policy;
}

/**
 * Sets message indicating policy has been saved.
 *
 * @param array $policy
 *   Policy array.
 */
function _password_policy_admin_form_set_saved_message(array $policy) {
  if (isset($policy['pid'])) {
    drupal_set_message(t('Policy %name has been updated.', array('%name' => $policy['name'])));
  }
  else {
    drupal_set_message(t('Policy %name has been created.', array('%name' => $policy['name'])));
  }
}

/**
 * Gets constraints from submitted policy form.
 *
 * @param array $form_state
 *   Form state.
 *
 * @return array
 *   Constraints array.
 */
function _password_policy_admin_form_get_constraints(array $form_state) {
  $constraints = array();
  foreach ($form_state['values'] as $key => $value) {
    // If we have no form value, then we have no constraint to set.
    if (!is_array($value)) {
      // Dodge issues with roles array.
      $value = trim($value);
      if ($value != '' && preg_match('/^constraint_/', $key)) {
        $constraints[substr($key, 11)] = $value;
      }
    }
  }
  return $constraints;
}

/**
 * Confirmation form for the deletion of a password policy.
 *
 * Deletion takes place in password_policy_admin_delete_submit().
 */
function password_policy_admin_delete($form, $form_state, $policy) {
  $form['pid'] = array('#type' => 'hidden', '#value' => $policy['pid']);

  return confirm_form($form, t('Are you sure you want to delete the policy %name?', array('%name' => $policy['name'])), 'admin/config/people/password_policy/list', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Submit hook for the delete policy operation.
 */
function password_policy_admin_delete_submit($form, &$form_state) {
  $pid = $form_state['values']['pid'];
  $policy = _password_policy_load_policy_by_pid($pid);

  db_delete('password_policy')
    ->condition('pid', $pid)
    ->execute();
  db_delete('password_policy_role')
    ->condition('pid', $pid)
    ->execute();
  drupal_set_message(t('Password policy %policy was deleted.', array('%policy' => $policy['name'])));
  watchdog('password_policy', 'Policy %name was deleted.', array('%name' => $policy['name']), WATCHDOG_NOTICE);
  drupal_goto('admin/config/people/password_policy/list');
}

/**
 * Forced password change form.
 */
function password_policy_password_change_settings() {
  $form = array();

  $form['password_policy_new_login_change'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force password change on first-time login'),
    '#default_value' => variable_get('password_policy_new_login_change', 0),
  );
  $roles = user_roles(TRUE);
  $form['password_policy_force_change_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#title' => t('Force users in the following roles to change their password'),
    '#description' => t('Users who are not logged in will be required to change their password immediately upon login. Users who are currently logged in will be required to change their password upon their next page request, but after changing their password will be redirected back to the page they were attempting to access.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * Submit hook for forced password change form.
 */
function password_policy_password_change_settings_submit($form, &$form_state) {
  global $user;
  $selected_roles = array();
  variable_set('password_policy_new_login_change', $form_state['values']['password_policy_new_login_change']);
  if ($form_state['values']['password_policy_new_login_change'] == 1) {
    watchdog('password_policy', 'New user accounts must change password on new login enabled by !admin.', array('!admin' => $user->name), WATCHDOG_NOTICE);
  }
  ($form_state['values']['password_policy_new_login_change']) ? drupal_set_message(t('New users will be required to change their password on first-time login.')) : drupal_set_message(t('New users will not be required to change their password on first-time login.'));

  foreach ($form_state['values']['password_policy_force_change_roles'] as $role) {
    // Skip over null values returned by unselected roles.
    if ($role == 0) {
      continue;
    }
    $uids = array();
    // Special handling for authenticated users role, since this role makes no
    // entries in the users_roles table.
    if ($role == 2) {
      // No point in flagging anonymous since they can't log in anyway.
      $db_uids = db_query('SELECT uid FROM {users} WHERE uid <> 0')->fetchCol();
    }
    else {
      $db_uids = db_query('SELECT uid FROM {users_roles} WHERE rid = :rid', array('rid' => $role))->fetchCol();
    }
    foreach ($db_uids as $uid) {
      if (($uid == 1 && variable_get('password_policy_admin', 1)) || $uid > 1) {
        $uids[] = $uid;
      }
    }
    if (!empty($uids)) {
      // If there are a large number of users to process, PHP memory limit may
      // be reached, so process the users in batches.
      $chunks = array_chunk($uids, 50000);
      foreach ($chunks as $chunk) {
        db_update('password_policy_force_change')
          ->fields(array(
            'force_change' => 1,
          ))
          ->condition('uid', $chunk, 'IN')
          ->execute();
      }
    }
    $selected_roles[] = $role;
  }
  if (count($selected_roles)) {
    $roles = user_roles(TRUE);
    $list = array();
    foreach ($selected_roles as $sr) {
      $list[] = $roles[$sr];
    }
    $list = implode(', ', $list);
    drupal_set_message(t('Users in the following roles will be required to immediately change their password: %list', array('%list' => $list)), 'status');
    watchdog('password_policy', '!admin has flagged users in the following roles to immediately change their password: %list', array('%list' => $list, '!admin' => $user->name), WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('No roles were selected.'));
  }
}
