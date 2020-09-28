<?php

/**
 * @file
 * TFA API.
 *
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * @defgroup tfa TFA module integrations.
 *
 * Module integrations with the TFA module.
 */

/**
 * Define TFA plugins.
 *
 * This hook is required to use your own TFA plugin.
 *
 * A plugin must extend the TfaBasePlugin class and may implement one or more
 * TFA plugin interfaces.
 *
 * Note, user-defined plugin classes must be available to the Drupal registry
 * for loading. Either define them in a .info file or via an autoloader.
 *
 * @return array
 *   Keyed array of information about the plugin for TFA integration.
 *
 *   Required key:
 *
 *    - 'example_machine_name'
 *      A unique machine name identifying the plugin.
 *
 *    With required sub-array containing:
 *
 *    - 'name'
 *       Human-readable name of the plugin.
 *    - 'class'
 *       Class name of the plugin.
 *
 *    Optional sub-elements:
 *
 *    - 'callback'
 *      Function name to call to return this plugin's object.
 */
function hook_tfa_api() {
  return array(
    'my_tfa_plugin' => array(
      'name'  => 'My TFA plugin',
      'class' => 'MyTfaPlugin',
    ),
  );
}

/**
 * Example TFA plugin setup.
 *
 * Adapt these Form API methods for your own module. For example, for a plugin
 * that sends a code via SMS you could use this form to allow the user to enter
 * their phone number.
 */

/**
 * Form builder for account configuration of TFA plugin.
 */
function my_tfa_setup_form($form, &$form_state, $account) {

  if (empty($form_state['storage'])) {
    // Include details about existing setup, if applicable.
    // Button to begin setup.
    $form['start'] = array(
      '#type' => 'submit',
      '#value' => t('Setup'),
    );
  }
  else {
    // Return the setup plugin's form.
    $tfa_setup = $form_state['storage']['tfa_setup'];
    $form = $tfa_setup->getForm($form, $form_state);
  }

  // Required account element.
  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );
  return $form;
}

/**
 * Form validation handler.
 */
function my_tfa_setup_form_validate($form, &$form_state) {
  // If there's no storage the form is just beginning, pass over to submit
  // handler.
  if (empty($form_state['storage'])) {
    return;
  }
  // Run setup plugin's form validation.
  $tfa_setup = $form_state['storage']['tfa_setup'];
  if (!$tfa_setup->validateForm($form, $form_state)) {
    foreach ($tfa_setup->getErrorMessages() as $element => $message) {
      form_set_error($element, $message);
    }
  }
}

/**
 * Form submission handler.
 */
function my_tfa_setup_form_submit($form, &$form_state) {
  $account = $form['account']['#value'];

  if (empty($form_state['storage'])) {
    // Start the TfaSetup process.
    $context = array('uid' => $account->uid);
    // Setup plugin class must be defined somehow (e.g. from a variable).
    $class = 'MyTfaPluginSetup';
    $setup_plugin = new $class($context);
    $tfa_setup = new TfaSetup($setup_plugin, $context);

    // Store TfaSetup process for multi-step.
    $form_state['storage']['tfa_setup'] = $tfa_setup;
    $form_state['rebuild'] = TRUE;
  }
  elseif (!empty($form_state['storage']['tfa_setup'])) {
    // Invoke plugin form submission.
    $tfa_setup = $form_state['storage']['tfa_setup'];
    if ($tfa_setup->submitForm($form, $form_state)) {
      drupal_set_message(t('Setup complete'));
      $form_state['redirect'] = 'user';
    }
    else {
      // Setup isn't complete so rebuild.
      $form_state['rebuild'] = TRUE;
    }
  }
}

/**
 * Act during TFA flood hit.
 *
 * This hook is invoked when one of the flood limits is hit.
 *
 * @param array $context
 *   TFA process context.
 */
function hook_tfa_flood_hit(array $context = array()) {
}

/**
 * Whether to halt login because TFA is not setup or ready for the account.
 *
 * Implement this hook to decide if authentication should be denied under the
 * conditions of the account not having TFA set up. TFA module will have already
 * invoked 'ready' methods on enabled plugins.
 *
 * @param object $account
 *   User account.
 *
 * @return bool
 *   FALSE to disallow login or TRUE to allow it without undergoing TFA.
 */
function hook_tfa_ready_require($account) {
  return TRUE;
}
