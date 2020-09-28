<?php

/**
 * @file
 * Tests for the TfaValidationPluginInterface.
 */

/**
 * Class TfaTestFallback.
 */
class TfaTestFallback extends TfaBasePlugin implements TfaValidationPluginInterface {

  /**
   * Constructor.
   */
  public function __construct(array $context = array()) {
    parent::__construct($context);
    $this->code = 'FAILSAFE';
  }

  /**
   * {@inheritdoc}
   */
  public function getForm(array $form, array &$form_state) {
    $form['recover'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter recovery code'),
      '#required' => TRUE,
    );
    $form['login'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array $form, array &$form_state) {
    if (!parent::validate($form_state['values']['recover'])) {
      $this->errorMessages['code'] = t('Invalid recovery code');
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

}
