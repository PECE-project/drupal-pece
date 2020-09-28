<?php

/**
 * @file
 * Form-related functions.
 */

/**
 * Start of TFA process form.
 *
 * @param object $account
 *   User account object.
 */
function tfa_begin_form($account) {
  return drupal_get_form('tfa_form', $account);
}

/**
 * Main TFA process form builder.
 *
 * Invokes plugin getForm() and handles multi-step fallback.
 */
function tfa_form($form, $form_state, $account) {
  $tfa = tfa_get_process($account);

  // Check flood tables.
  if (_tfa_hit_flood($tfa)) {
    module_invoke_all('tfa_flood_hit', $tfa->getContext());
    return drupal_access_denied();
  }
  // Get TFA plugins form.
  $form = $tfa->getForm($form, $form_state);
  if ($tfa->hasFallback()) {
    $form['actions']['fallback'] = array(
      '#type' => 'submit',
      '#value' => t("Can't access your account?"),
      '#submit' => array('tfa_form_submit'),
      '#limit_validation_errors' => array(),
      '#weight' => 20,
    );
  }
  // Set account element.
  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );

  return $form;
}

/**
 * TFA form validation handler.
 *
 * Invokes plugin validateForm() and getErrorMessages().
 */
function tfa_form_validate($form, &$form_state) {
  // No validation when issuing fallback.
  if (isset($form_state['values']['fallback']) && $form_state['values']['op'] === $form_state['values']['fallback']) {
    return;
  }
  $account = $form['account']['#value'];
  $tfa = tfa_get_process($account);

  if (!$tfa->validateForm($form, $form_state)) {
    foreach ($tfa->getErrorMessages() as $element => $message) {
      form_set_error($element, $message);
    }
    $identifier = variable_get('user_failed_login_identifier_uid_only', FALSE) ? $account->uid : $account->uid . '-' . ip_address();
    flood_register_event('tfa_user', variable_get('tfa_user_window', 900), $identifier);

    if (_tfa_hit_flood($tfa)) {
      module_invoke_all('tfa_flood_hit', $tfa->getContext());
      return drupal_access_denied();
    }
  }
}

/**
 * TFA form submission handler.
 *
 * Invokes plugin submitForm() and processComplete() and handles starting
 * multi-step if appropriate.
 */
function tfa_form_submit($form, &$form_state) {
  $account = $form['account']['#value'];
  $tfa = tfa_get_process($account);

  if (!$tfa->submitForm($form, $form_state)) {
    // If fallback was triggered TFA process has been reset to new validate
    // plugin so run begin and store new context.
    if (isset($form_state['values']['fallback']) && $form_state['values']['op'] === $form_state['values']['fallback']) {
      $tfa->begin();
    }
    $context = $tfa->getContext();
    tfa_set_context($account, $context);
    $form_state['rebuild'] = TRUE;
  }
  else {
    // TFA process is complete so finalize and authenticate user.
    $context = tfa_get_context($account);
    $tfa->finalize();
    tfa_login($account);
    // Set redirect based on query parameters, existing $form_state or context.
    $form_state['redirect'] = _tfa_form_get_destination($context, $form_state, $account);
  }
}

/**
 * Get destination and options for $form_state['redirect'].
 *
 * @param array $context
 *   TFA account context.
 * @param array $form_state
 *   Form API state array from tfa_form_submit().
 * @param object $account
 *   User account.
 *
 * @return array
 *   Array with the redirect destination, and options.
 */
function _tfa_form_get_destination(array $context, array $form_state, $account) {
  $options = array();
  $destination = 'user';
  if (!empty($_GET['pass-reset-token'])) {
    // If pass-reset-token was set then complete final process interrupted
    // from user_pass_reset().
    watchdog('tfa', 'User %name used one-time login link', array('%name' => $account->name));
    drupal_set_message(t('You have just used your one-time login link. It is no longer necessary to use this link to log in. Please change your password.'));
    // Let the user's password be changed without the current password check.
    $token = drupal_hash_base64(drupal_random_bytes(32));
    $_SESSION['pass_reset_' . $account->uid] = $token;
    $options['query']['pass-reset-token'] = $token;
  }
  if (!empty($form_state['redirect'])) {
    if (is_array($form_state['redirect'])) {
      $destination = $form_state['redirect'][0];
      $options = $form_state['redirect'][1];
    }
    else {
      $destination = $form_state['redirect'];
    }
  }
  if (!empty($_GET['destination']) && !url_is_external($_GET['destination'])) {
    $query_destination = drupal_parse_url($_GET['destination']);
    $destination = $query_destination['path'];
    $options['query'] = !empty($options['query']) ?
      array_merge($options['query'], $query_destination['query']) : $query_destination['query'];
    $options['fragment'] = $query_destination['fragment'];
    unset($_GET['destination']);
  }
  // Context redirect takes final precedence.
  if (!empty($context['redirect'])) {
    if (is_array($context['redirect'])) {
      $destination = $context['redirect'][0];
      $options = $context['redirect'][1];
    }
    else {
      $destination = $context['redirect'];
    }
  }
  // Allow other modules to alter final destination. This is better than form
  // altering TFA forms because callers would need to check the TFA process
  // status to figure out when to act.
  drupal_alter('tfa_complete_redirect', $destination, $options);
  return array($destination, $options);
}

/**
 * Check if flood has been hit.
 *
 * @param Tfa $tfa
 *   Tfa object.
 *
 * @return bool
 *   TRUE if the flood has been hit.
 *
 * phpcs:disable Drupal.Commenting.FunctionComment.TypeHintMissing
 */
function _tfa_hit_flood($tfa) {
  if (variable_get('tfa_test_mode', 0)) {
    return FALSE;
  }
  $window = variable_get('tfa_flood_window', 3600);
  $user_window = variable_get('tfa_user_window', 900);
  $context = $tfa->getContext();
  $identifier = variable_get('user_failed_login_identifier_uid_only', FALSE) ? $context['uid'] : $context['uid'] . '-' . ip_address();

  // Check user specific flood.
  if (!flood_is_allowed('tfa_user', variable_get('tfa_user_threshold', 6), $user_window, $identifier)) {
    drupal_set_message(t('You have reached the threshold for incorrect code entry attempts. Please try again in !time minutes.', array('!time' => round($user_window / 60))), 'error');
    return TRUE;
  }
  // Check entire process flood.
  elseif (!flood_is_allowed('tfa_begin', variable_get('tfa_begin_threshold', 6), $window)) {
    drupal_set_message(t('You have reached the threshold for TFA attempts. Please try again in !time minutes.', array('!time' => round($window / 60))), 'error');
    return TRUE;
  }
  // Check TFA plugin flood.
  elseif (!$tfa->floodIsAllowed($window)) {
    foreach ($tfa->getErrorMessages() as $message) {
      drupal_set_message($message, 'error');
    }
    return TRUE;
  }
  return FALSE;
}
