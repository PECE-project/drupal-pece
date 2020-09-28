<?php

/**
 * @file class for TFA Basic
 */

/**
 * Class TfaBasicHelp
 */
class TfaBasicHelp extends TfaBasePlugin implements TfaValidationPluginInterface {

  /**
   * @copydoc TfaBasePlugin::getForm()
   */
  public function getForm(array $form, array &$form_state) {
    $default = t('Contact support to reset your access');
    $content = variable_get('tfa_basic_help_text', $default);
    $form['help'] = array(
      '#type' => 'markup',
      '#markup' => check_plain($content),
    );
    // Disallow login plugins from applying to this step.
    $form['#tfa_no_login'] = TRUE;
    return $form;
  }

  /**
   * @copydoc TfaValidationPluginInterface::validateForm()
   */
  public function validateForm(array $form, array &$form_state) {
    // Unused.
  }

}
