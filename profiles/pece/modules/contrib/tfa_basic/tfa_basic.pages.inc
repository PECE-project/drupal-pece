<?php

/**
 * TFA Basic account setup overview page.
 */
function tfa_basic_overview($form, &$form_state, $account) {

  $output['info'] = array(
    '#type' => 'markup',
    '#markup' => '<p>' . t('Two-factor authentication (TFA) provides additional security for your account. With TFA enabled, you log in to the site with a verification code in addition to your username and password.') . '</p>',
  );
  $form_state['storage']['account'] = $account;
  $user_tfa = tfa_basic_get_tfa_data($account);
  $enabled = isset($user_tfa['status']) && $user_tfa['status'] ? TRUE : FALSE;

  if (!empty($user_tfa)) {
    if ($enabled) {
      $status_text = t('Status: <strong>TFA enabled</strong>, set !time. <a href="!url">Disable TFA</a>', array('!time' => format_date($user_tfa['saved']), '!url' => url('user/' . $account->uid . '/security/tfa/disable')));
    }
    else {
      $status_text = t('Status: <strong>TFA disabled</strong>, set !time.', array('!time' => format_date($user_tfa['saved'])));
    }
    $output['status'] = array(
      '#type' => 'markup',
      '#markup' => '<p>' . $status_text . '</p>',
    );
  }

  // Start with validate plugin setup.
  if (!$enabled) {
    $validate_plugin = variable_get('tfa_validate_plugin', '');
    $output['setup'] = _tfa_basic_plugin_setup_form_overview($validate_plugin, $account, $user_tfa);
  }
  else {
    // TOTP setup.
    $output['app'] = _tfa_basic_plugin_setup_form_overview('tfa_basic_totp', $account, $user_tfa);
    // SMS setup.
    $output['sms'] = _tfa_basic_plugin_setup_form_overview('tfa_basic_sms', $account, $user_tfa);
    // Trusted browsers.
    $output['trust'] = _tfa_basic_plugin_setup_form_overview('tfa_basic_trusted_browser', $account, $user_tfa);
    // Recovery codes.
    $output['recovery'] = _tfa_basic_plugin_setup_form_overview('tfa_basic_recovery_code', $account, $user_tfa);
  }

  return $output;
}

/**
 * Get TFA basic setup action links for use on overview page.
 *
 * @param string $plugin
 * @param object $account
 * @param array $user_tfa
 *
 * @return array
 *   Render array
 */
function _tfa_basic_plugin_setup_form_overview($plugin, $account, array $user_tfa) {
  // No output if the plugin isn't enabled.
  if ($plugin !== variable_get('tfa_validate_plugin', '') &&
    !in_array($plugin, variable_get('tfa_fallback_plugins', array())) &&
    !in_array($plugin, variable_get('tfa_login_plugins', array()))) {
    return array();
  }
  $enabled = isset($user_tfa['status']) && $user_tfa['status'] ? TRUE : FALSE;
  $output = array();
  switch ($plugin) {
    case 'tfa_basic_totp';
      $output = array(
        'heading' => array(
          '#theme' => 'html_tag',
          '#tag' => 'h3',
          '#value' => t('TFA application'),
        ),
        'description' => array(
          '#theme' => 'html_tag',
          '#tag' => 'p',
          '#value' => t('Generate verification codes from a mobile or desktop application.'),
        ),
        'link' => array(
          '#prefix' => '<p>',
          '#theme' => 'link',
          '#path' => 'user/' . $account->uid . '/security/tfa/app-setup',
          '#text' => !$enabled ? t('Set up application') : t('Reset application'),
          '#options' => array('attributes' => array(), 'html' => FALSE),
          '#suffix' => '</p>',
        ),
      );
      break;

    case 'tfa_basic_sms':
      $output = array(
        'heading' => array(
          '#theme' => 'html_tag',
          '#tag' => 'h3',
          '#value' => t('SMS'),
        ),
        'description' => array(
          '#theme' => 'html_tag',
          '#tag' => 'p',
          '#value' => t('Receive verification code via SMS.'),
        ),
      );
      if (tfa_basic_get_twilio_client() !== FALSE) {
        $mobile_number = tfa_basic_get_mobile_number($account);
        if (!empty($user_tfa['data']['sms']) && $mobile_number !== FALSE) {
          $output['number'] = array(
            '#type' => 'markup',
            '#markup' => '<p>' . t('Deliver to @number', array('@number' => tfa_basic_format_number($mobile_number))) . '</p>',
          );
        }
        if (empty($user_tfa['data']['sms'])) {
          $sms_text = t('Set up SMS delivery');
        }
        else {
          $sms_text = t('Reset SMS delivery');
        }
        $output['link'] = array(
          '#type' => 'markup',
          '#markup' => l($sms_text, 'user/' . $account->uid . '/security/tfa/sms-setup'),
        );
      }
      else {
        $output['number'] = array(
          '#type' => 'markup',
          '#markup' => '<p><em>' . t('Not available for use') . '</em></p>',
        );
      }
      break;

    case 'tfa_basic_trusted_browser':
      $trusted_browser = new TfaTrustedBrowserSetup(array('uid' => $account->uid));
      $trusted_browsers = array();
      foreach ($trusted_browser->getTrustedBrowsers() as $device) {
        $vars = array(
          '!expiration' => format_date($device['created'] + variable_get('tfa_basic_trust_cookie_expiration', 3600 * 24 * 30)),
          '@browser' => $device['name'],
          '!time' => format_date($device['last_used']),
        );
        if (empty($device['last_used'])) {
          $message = t('@browser, expires !expiration', $vars);
        }
        else {
          $message = t('@browser, expires !expiration, last used !time', $vars);
        }
        $trusted_browsers[] = $message;
      }
      $output = array(
        'heading' => array(
          '#theme' => 'html_tag',
          '#tag' => 'h3',
          '#value' => t('Trusted browsers'),
        ),
        'description' => array(
          '#theme' => 'html_tag',
          '#tag' => 'p',
          '#value' => t('Browsers that will not require a verification code during login.'),
        ),
      );
      if (!empty($trusted_browsers)) {
        $output['list'] = array(
          '#type' => 'markup',
          '#markup' => theme('item_list', array('items' => $trusted_browsers)),
        );
      }
      $output['link'] = array(
        '#prefix' => '<p>',
        '#theme' => 'link',
        '#path' => 'user/' . $account->uid . '/security/tfa/trusted-browsers',
        '#text' => t('Set trusted browsers'),
        '#options' => array('attributes' => array(), 'html' => FALSE),
        '#suffix' => '</p>',
      );
      break;

    case 'tfa_basic_recovery_code':
      $recovery = new TfaBasicRecoveryCodeSetup(array('uid' => $account->uid));
      $output = array(
        'heading' => array(
          '#theme' => 'html_tag',
          '#tag' => 'h3',
          '#value' => t('Recovery codes'),
        ),
        'description' => array(
          '#theme' => 'html_tag',
          '#tag' => 'p',
          '#value' => t('Pre-generated, one-time-use codes intended as a fallback should other methods be unavailable.'),
        ),
      );
      $recovery_codes = $recovery->getCodes();
      if (empty($recovery_codes)) {
        $codes_text = t('Get recovery codes');
      }
      else {
        $output['list'] = array(
          '#prefix' => '<p>',
          '#theme' => 'link',
          '#path' => 'user/' . $account->uid . '/security/tfa/recovery-codes-list',
          '#text' => t('View unused recovery codes'),
          '#options' => array('attributes' => array(), 'html' => FALSE),
          '#suffix' => '</p>',
        );
        $codes_text = t('Get new recovery codes');
      }
      $output['link'] = array(
        '#prefix' => '<p>',
        '#theme' => 'link',
        '#path' => 'user/' . $account->uid . '/security/tfa/recovery-codes',
        '#text' => $codes_text,
        '#options' => array('attributes' => array(), 'html' => FALSE),
        '#suffix' => '</p>',
      );
      break;

  }
  return $output;
}

function tfa_basic_disable_form($form, &$form_state, $account) {
  global $user;

  $form_state['storage']['account'] = $account;

  if ($account->uid != $user->uid && user_access('administer users')) {
    $preamble_desc = t('Are you sure you want to disable TFA on account %name?', array('%name' => $account->name));
    $notice_desc = t('TFA settings and data will be lost. %name can re-enable TFA again from their profile.', array('%name' => $account->name));
    if (tfa_basic_tfa_required($account)) {
      drupal_set_message(t("This account is required to have TFA enabled per the 'require TFA' permission on one of their roles. Disabling TFA will remove their ability to log back into the site. If you continue, consider also removing the role so they can authenticate and setup TFA again."), 'warning');
    }
  }
  else {
    $preamble_desc = t('Are you sure you want to disable your two-factor authentication setup?');
    $notice_desc = t("Your settings and data will be lost. You can re-enable two-factor authentication again from your profile.");
    if (tfa_basic_tfa_required($account)) {
      drupal_set_message(t('Your account must have at least one two-factor authentication method enabled. Continuing will disable your ability to log back into this site.'), 'warning');
      $notice_desc = t('Your settings and data will be lost and you will be unable to log back into the site. To regain access contact a site administrator.');
    }
  }
  $form['preamble'] = array(
    '#prefix' => '<p class="preamble">',
    '#suffix' => '</p>',
    '#markup' => $preamble_desc,
  );
  $form['notice'] = array(
    '#prefix' => '<p class="preamble">',
    '#suffix' => '</p>',
    '#markup' => $notice_desc,
  );

  $form['account']['current_pass'] = array(
    '#type' => 'password',
    '#title' => t('Confirm your current password'),
    '#description_display' => 'before',
    '#size' => 25,
    '#weight' => -5,
    '#attributes' => array('autocomplete' => 'off'),
    '#required' => TRUE,
  );
  $form['account']['mail'] = array(
    '#type' => 'value',
    '#value' => $account->mail,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Disable'),
  );
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#limit_validation_errors' => array(),
    '#submit' => array('tfa_basic_disable_form_submit'),
  );

  return $form;
}

/**
 * Disable form validate.
 */
function tfa_basic_disable_form_validate($form, &$form_state) {
  global $user;
  $account = $form_state['storage']['account'];
  // Allow administrators to disable TFA for another account.
  if ($account->uid != $user->uid && user_access('administer users')) {
    $account = $user;
  }
  // Check password. (from user.module user_validate_current_pass()).
  require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
  $current_pass = user_check_password($form_state['values']['current_pass'], $account);
  if (!$current_pass) {
    form_set_error('current_pass', t("Incorrect password."));
  }
}

/**
 * Disable form submit.
 */
function tfa_basic_disable_form_submit($form, &$form_state) {
  $account = $form_state['storage']['account'];
  if ($form_state['values']['op'] === $form_state['values']['cancel']) {
    drupal_set_message(t('TFA disable canceled.'));
    $form_state['redirect'] = 'user/' . $account->uid . '/security/tfa';
    return;
  }
  $params = array('account' => $account);
  tfa_basic_setup_save_data($account, array('status' => FALSE));
  // Delete TOTP code.
  $totp = new TfaTotp(array('uid' => $account->uid));
  $totp->deleteSeed();
  // Delete recovery codes.
  $recovery = new TfaBasicRecoveryCodeSetup(array('uid' => $account->uid));
  $recovery->deleteCodes();
  // Delete trusted browsers.
  $trusted = new TfaTrustedBrowserSetup(array('uid' => $account->uid));
  $trusted->deleteTrustedBrowsers();

  watchdog('tfa_basic', 'TFA disabled for user @name UID !uid', array(
    '@name' => $account->name,
    '!uid' => $account->uid,
  ), WATCHDOG_NOTICE);

  // E-mail account to inform user that it has been disabled.
  drupal_mail('tfa_basic', 'tfa_basic_disabled_configuration', $account->mail, user_preferred_language($account), $params);

  drupal_set_message(t('TFA has been disabled.'));
  $form_state['redirect'] = 'user/' . $account->uid . '/security/tfa';
}

/**
 * TFA setup form router.
 */
function tfa_basic_setup_form($form, &$form_state, $account, $method = 'tfa_basic_totp') {
  global $user;

  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );
  $tfa_data = tfa_basic_get_tfa_data($account);
  $enabled = isset($tfa_data['status']) && $tfa_data['status'] ? TRUE : FALSE;

  // Always require a password on the first time through.
  if (empty($form_state['storage'])) {
    // Allow administrators to change TFA settings for another account.
    if ($account->uid != $user->uid && user_access('administer users')) {
      $current_pass_description = t('Enter your current password to alter TFA settings for account %name.', array('%name' => $account->name));
    }
    else {
      $current_pass_description = t('Enter your current password to continue.');
    }
    $form['current_pass'] = array(
      '#type' => 'password',
      '#title' => t('Current password'),
      '#size' => 25,
      '#required' => TRUE,
      '#description' => $current_pass_description,
      '#attributes' => array('autocomplete' => 'off'),
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Confirm'),
    );
    $form['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#limit_validation_errors' => array(),
      '#submit' => array('tfa_basic_setup_form_submit'),
    );
  }
  else {
    // If TFA is not enabled setup each plugin by using enabled plugins as form
    // steps.
    if (!$enabled && empty($form_state['storage']['steps'])) {
      $form_state['storage']['full_setup'] = TRUE;
      $steps = _tfa_basic_full_setup_steps($method);
      $form_state['storage']['steps_left'] = $steps;
      $form_state['storage']['steps_skipped'] = array();
    }

    // Override provided method if operating under multi-step.
    if (isset($form_state['storage']['step_method'])) {
      $method = $form_state['storage']['step_method'];
    }
    // Record methods progressed.
    $form_state['storage']['steps'][] = $method;
    $context = array('uid' => $account->uid);
    switch ($method) {
      case 'tfa_basic_totp':
        drupal_set_title(t('TFA setup - Application'));
        $setup_plugin = new TfaTotpSetup($context);
        $tfa_setup = new TfaSetup($setup_plugin, $context);

        if (!empty($tfa_data)) {
          $form['disclaimer'] = array(
            '#type' => 'markup',
            '#markup' => '<p>' . t('Note: You should delete the old account in your mobile or desktop app before adding this new one.') . '</p>',
          );
        }
        $form = $tfa_setup->getForm($form, $form_state);
        $form_state['storage'][$method] = $tfa_setup;
        break;

      case 'tfa_basic_trusted_browser':
        drupal_set_title(t('TFA setup - Trusted browsers'));
        $setup_plugin = new TfaTrustedBrowserSetup($context);
        $tfa_setup = new TfaSetup($setup_plugin, $context);
        $form = $tfa_setup->getForm($form, $form_state);
        $form_state['storage'][$method] = $tfa_setup;
        break;

      case 'tfa_basic_recovery_code':
        drupal_set_title(t('TFA setup - Recovery codes'));
        $setup_plugin = new TfaBasicRecoveryCodeSetup($context);
        $tfa_setup = new TfaSetup($setup_plugin, $context);
        $form = $tfa_setup->getForm($form, $form_state);
        $form_state['storage'][$method] = $tfa_setup;
        break;

      case 'tfa_basic_sms':
        drupal_set_title(t('TFA setup - SMS'));
        // SMS itself has multiple steps. Begin with phone number entry.
        if (empty($form_state['storage'][$method])) {
          $default_number = tfa_basic_get_mobile_number($account);
          $form['sms_number'] = array(
            '#type' => 'textfield',
            '#title' => t('Mobile phone number'),
            '#required' => TRUE,
            '#description' => t('Enter your mobile phone number that can receive SMS codes. A code will be sent to this number for validation.'),
            '#default_value' => $default_number ?: '',
          );
          $phone_field = variable_get('tfa_basic_phone_field', '');
          if (!empty($phone_field)) {
            // Report that this is an account field.
            $field = field_info_instance('user', $phone_field, 'user');
            $form['sms_number']['#description'] .= ' ' . t('This number is stored on your account under field %label.', array('%label' => $field['label']));
          }
          $form['send'] = array(
            '#type' => 'submit',
            '#value' => t('Send SMS'),
          );
          if (!empty($tfa_data['data']['sms'])) {
            // Provide disable SMS option.
            $form['actions']['sms_disable'] = array(
              '#type' => 'submit',
              '#value' => t('Disable SMS delivery'),
              '#limit_validation_errors' => array(),
              '#submit' => array('tfa_basic_setup_form_submit'),
            );
          }
        }
        // Then validate by sending an SMS.
        else {
          $number = tfa_basic_format_number($form_state['storage']['sms_number']);
          drupal_set_message(t("A code was sent to @number. It may take up to a minute for its arrival.", array('@number' => $number)));
          $tfa_setup = $form_state['storage'][$method];
          $form = $tfa_setup->getForm($form, $form_state);
          if (isset($form_state['storage']['full_setup'])) {
            drupal_set_message(t("If the code does not arrive or you entered the wrong number skip this step to continue without SMS delivery. You can enable it after completing the rest of TFA setup."));
          }
          else {
            $form['sms_code']['#description'] .= ' ' . l(t('If the code does not arrive or you entered the wrong number click here to start over.'), 'user/' . $account->uid . '/security/tfa/sms-setup');
          }

          $form_state['storage'][$method] = $tfa_setup;
        }
        break;

      // List previously saved recovery codes. Note, this is not a plugin.
      case 'recovery_codes_list':
        $recovery = new TfaBasicRecoveryCodeSetup(array('uid' => $account->uid));
        $codes = $recovery->getCodes();

        $output = theme('item_list', array('items' => $codes));
        $output .= l(t('Return to account TFA overview'), 'user/' . $account->uid . '/security/tfa');
        $form['output'] = array(
          '#type' => 'markup',
          '#markup' => $output,
        );
        // Return early.
        return $form;

      default:
        break;
    }
    // Provide skip button under full setup.
    if (isset($form_state['storage']['full_setup']) && count($form_state['storage']['steps']) > 1) {
      $count = count($form_state['storage']['steps_left']);
      $form['actions']['skip'] = array(
        '#type' => 'submit',
        '#value' => $count > 0 ? t('Skip') : t('Skip and finish'),
        '#limit_validation_errors' => array(),
        '#submit' => array('tfa_basic_setup_form_submit'),
      );
    }
    // Provide cancel button on first step or single steps.
    else {
      $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
        '#limit_validation_errors' => array(),
        '#submit' => array('tfa_basic_setup_form_submit'),
      );
    }
    // Record the method in progress regardless of whether in full setup.
    $form_state['storage']['step_method'] = $method;
  }

  return $form;

}

/**
 * Setup form validate.
 */
function tfa_basic_setup_form_validate($form, &$form_state) {
  global $user;
  $account = $form['account']['#value'];
  if (isset($form_state['values']['current_pass'])) {
    // Allow administrators to change TFA settings for another account.
    if ($account->uid != $user->uid && user_access('administer users')) {
      $account = $user;
    }
    // Check password. (from user.module user_validate_current_pass()).
    require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
    $current_pass = user_check_password($form_state['values']['current_pass'], $account);
    if (!$current_pass) {
      form_set_error('current_pass', t("Incorrect password."));
    }
    return;
  }
  elseif (isset($form_state['values']['cancel']) && $form_state['values']['op'] === $form_state['values']['cancel']) {
    return;
  }
  // Handle first step of SMS setup.
  elseif (isset($form_state['values']['sms_number'])) {
    // Validate number.
    $number = $form_state['values']['sms_number'];
    $number_errors = tfa_basic_valid_number($number);
    if (!empty($number_errors)) {
      foreach ($number_errors as $error) {
        form_set_error('number', $error);
      }
    }
    return;
  }
  // Validate plugin form.
  elseif (!empty($form_state['storage']['step_method'])) {
    $method = $form_state['storage']['step_method'];
    $tfa_setup = $form_state['storage'][$method];
    if (!$tfa_setup->validateForm($form, $form_state)) {
      foreach ($tfa_setup->getErrorMessages() as $element => $message) {
        form_set_error($element, $message);
      }
    }
  }
}

/**
 * Setup form submit.
 */
function tfa_basic_setup_form_submit($form, &$form_state) {
  $account = $form['account']['#value'];

  // Cancel button.
  if (isset($form_state['values']['cancel']) && $form_state['values']['op'] === $form_state['values']['cancel']) {
    drupal_set_message('TFA setup canceled.');
    $form_state['redirect'] = 'user/' . $account->uid . '/security/tfa';
    return;
  }
  // Password validation.
  if (isset($form_state['values']['current_pass'])) {
    $form_state['storage']['pass_confirmed'] = TRUE;
    $form_state['rebuild'] = TRUE;
    return;
  }
  // Submitting mobile number step.
  elseif (!empty($form_state['values']['sms_number'])) {
    // Send code to number.
    $form_state['storage']['sms_number'] = $form_state['values']['sms_number'];
    $context = array('uid' => $account->uid, 'mobile_number' => $form_state['storage']['sms_number']);
    $client = tfa_basic_get_twilio_client();
    $setup_plugin = new TfaBasicSmsSetup($context, $form_state['storage']['sms_number'], $client);
    $tfa_setup = new TfaSetup($setup_plugin, $context);
    $tfa_setup->begin();
    $errors = $tfa_setup->getErrorMessages();
    if (!empty($errors)) {
      foreach ($errors as $error) {
        form_set_error('number', $error);
      }
    }
    else {
      // No errors so store setup.
      $form_state['storage']['tfa_basic_sms'] = $tfa_setup;
    }
    $form_state['rebuild'] = TRUE;
    return;
  }
  // Disabling SMS delivery.
  if (isset($form_state['values']['sms_disable']) && $form_state['values']['op'] === $form_state['values']['sms_disable']) {
    tfa_basic_setup_save_data($account, array('sms' => FALSE));
    drupal_set_message(t('TFA SMS delivery disabled.'));
    $form_state['redirect'] = 'user/' . $account->uid . '/security/tfa';
    watchdog('tfa_basic', 'TFA SMS disabled for user @name UID !uid', array(
      '@name' => $account->name,
      '!uid' => $account->uid,
    ), WATCHDOG_INFO);
    return;
  }
  // Submitting a plugin form.
  elseif (!empty($form_state['storage']['step_method'])) {
    $method = $form_state['storage']['step_method'];
    $skipped_method = FALSE;

    // Support skipping optional steps when in full setup.
    if (isset($form_state['values']['skip']) && $form_state['values']['op'] === $form_state['values']['skip']) {
      $skipped_method = $method;
      $form_state['storage']['steps_skipped'][] = $method;
      unset($form_state['storage'][$method]);
    }

    // Trigger multi-step if in full setup.
    if (!empty($form_state['storage']['full_setup'])) {
      _tfa_basic_set_next_step($form_state, $method, $skipped_method);
    }

    // Plugin form submit.
    if (!empty($form_state['storage'][$method])) {
      $setup_class = $form_state['storage'][$method];
      if (!$setup_class->submitForm($form, $form_state)) {
        drupal_set_message(t('There was an error during TFA setup. Your settings have not been saved.'), 'error');
        $form_state['redirect'] = 'user/' . $account->uid . '/security/tfa';
        return;
      }
    }

    // Save user TFA settings for relevant plugins that weren't skipped.
    if (empty($skipped_method) && $method == 'tfa_basic_sms' &&
      isset($form_state['storage']['sms_number']) &&
      in_array('tfa_basic_sms', $form_state['storage']['steps'])) {

      // Update mobile number if different than stored.
      if ($form_state['storage']['sms_number'] !== tfa_basic_get_mobile_number($account)) {
        tfa_basic_set_mobile_number($account, $form_state['storage']['sms_number']);
      }
      tfa_basic_setup_save_data($account, array('sms' => TRUE));
    }

    // Return if multi-step.
    if (isset($form_state['rebuild']) && $form_state['rebuild']) {
      return;
    }
    // Else, setup complete and return to overview page.
    drupal_set_message(t('TFA setup complete.'));
    $form_state['redirect'] = 'user/' . $account->uid . '/security/tfa';

    // Log and notify if this was full setup.
    if (!empty($form_state['storage']['full_setup'])) {
      $data = array(
        'plugins' => array_diff($form_state['storage']['steps'], $form_state['storage']['steps_skipped']),
      );
      tfa_basic_setup_save_data($account, $data);
      $params = array('account' => $account);
      drupal_mail('tfa_basic', 'tfa_basic_tfa_enabled', $account->mail, user_preferred_language($account), $params);
      watchdog('tfa_basic', 'TFA enabled for user @name UID !uid', array(
        '@name' => $account->name,
        '!uid' => $account->uid,
      ), WATCHDOG_INFO);
    }
  }
}

/**
 * Steps eligble for TFA Basic setup.
 */
function _tfa_basic_full_setup_steps() {
  $steps = array();
  $plugins = array(
    'tfa_basic_totp',
    'tfa_basic_sms',
    'tfa_basic_trusted_browser',
    'tfa_basic_recovery_code',
  );
  foreach ($plugins as $plugin) {
    if ($plugin === variable_get('tfa_validate_plugin', '') ||
      in_array($plugin, variable_get('tfa_fallback_plugins', array())) ||
      in_array($plugin, variable_get('tfa_login_plugins', array()))) {
      $steps[] = $plugin;
    }
  }
  return $steps;
}

/**
 * Set form rebuild, next step, and message if any plugin steps left.
 */
function _tfa_basic_set_next_step(&$form_state, $this_step, $skipped_step = FALSE) {
  // Remove this step from steps left.
  $form_state['storage']['steps_left'] = array_diff($form_state['storage']['steps_left'], array($this_step));
  if (!empty($form_state['storage']['steps_left'])) {
    // Contextual reporting.
    $output = FALSE;
    switch ($this_step) {
      case 'tfa_basic_totp':
        $output = $skipped_step ? t('Application codes not enabled.') : t('Application code verified.');
        break;

      case 'tfa_basic_sms':
        $output = $skipped_step ? t('SMS code delivery not enabled.') : t('SMS code verified.');
        break;

      case 'tfa_basic_trusted_browser':
        // Handle whether the checkbox was unchecked.
        if ($skipped_step || empty($form_state['values']['trust'])) {
          $output = t('Browser not saved.');
        }
        else {
          $output = t('Browser saved.');
        }
        break;

      case 'tfa_basic_recovery_code':
        $output = $skipped_step ? t('Recovery codes not saved.') : t('Saved recovery codes.');
        break;
    }
    $count = count($form_state['storage']['steps_left']);
    $output .= ' ' . format_plural($count, 'One setup step remaining.', '@count TFA setup steps remain.', array('@count' => $count));
    if ($output) {
      drupal_set_message($output);
    }

    // Set next step and mark form for rebuild.
    $next_step = array_shift($form_state['storage']['steps_left']);
    $form_state['storage']['step_method'] = $next_step;
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Output unused recovery codes.
 *
 * @param stdClass $account
 * @return string
 */
function tfa_basic_recovery_codes_list($account) {
  $recovery = new TfaBasicRecoveryCodeSetup(array('uid' => $account->uid));
  $codes = $recovery->getCodes();

  $output = theme('item_list', array('items' => $codes));
  $output .= l(t('Return to account TFA overview'), 'user/' . $account->uid . '/security/tfa');
  return $output;
}
