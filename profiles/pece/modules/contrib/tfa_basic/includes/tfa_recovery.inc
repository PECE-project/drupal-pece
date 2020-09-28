<?php

/**
 * @file class for TFA Basic
 */

/**
 * Class TfaBasicRecoveryCode
 */
class TfaBasicRecoveryCode extends TfaBasePlugin implements TfaValidationPluginInterface {

  /**
   * @var string
   */
  protected $usedCode;

  public function __construct(array $context) {
    parent::__construct($context);
    // Set in settings.php.
    $this->encryptionKey = variable_get('tfa_basic_secret_key', drupal_get_private_key());
  }

  /**
   * @copydoc TfaBasePlugin::ready()
   */
  public function ready() {
    $codes = $this->getCodes();
    return !empty($codes);
  }

  /**
   * @copydoc TfaBasePlugin::getForm()
   */
  public function getForm(array $form, array &$form_state) {
    $form['recover'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter one of your recovery codes'),
      '#required' => TRUE,
      '#description' => t('Recovery codes were generated when you first set up TFA. Format: XXX XX XXX'),
      '#attributes' => array('autocomplete' => 'off'),
    );
    if (module_exists('elements')) {
      $form['recover']['#type'] = 'numberfield';
    }
    $form['actions']['#type'] = 'actions';
    $form['actions']['login'] = array(
      '#type' => 'submit',
      '#value' => t('Verify'),
    );
    return $form;
  }

  /**
   * @copydoc TfaBasePlugin::validateForm()
   */
  public function validateForm(array $form, array &$form_state) {
    return $this->validate($form_state['values']['recover']);
  }

  /**
   * @copydoc TfaBasePlugin::finalize()
   */
  public function finalize() {
    // Mark code as used.
    if ($this->usedCode) {
      $num = db_update('tfa_recovery_code')
        ->fields(array('used' => REQUEST_TIME))
        ->condition('id', $this->usedCode)
        ->condition('uid', $this->context['uid'])
        ->execute();
      if ($num) {
        watchdog('tfa_basic', 'Used TFA recovery code !id by user !uid', array('!id' => $this->usedCode, '!uid' => $this->context['uid']), WATCHDOG_NOTICE);
      }
    }
  }

  /**
   * Get unused recovery codes.
   *
   * @todo consider returning used codes so validate() can error with
   * appropriate message
   *
   * @return array
   *   Array of codes indexed by ID.
   */
  public function getCodes() {
    // Lookup codes for account and decrypt.
    $codes = array();
    $result = db_query("SELECT id, code FROM {tfa_recovery_code} WHERE uid = :uid AND used = 0", array(':uid' => $this->context['uid']));
    if (!empty($result)) {
      foreach ($result as $data) {
        $encrypted = base64_decode($data->code);
        // trim() prevents extraneous escape characters.
        $code = trim($this->decrypt($encrypted));
        if (!empty($code)) {
          $codes[$data->id] = $code;
        }
      }
    }
    return $codes;
  }

  /**
   * @copydoc TfaBasePlugin::validate()
   */
  protected function validate($code) {
    $this->isValid = FALSE;
    // Get codes and compare.
    $codes = $this->getCodes();
    if (empty($codes)) {
      $this->errorMessages['code'] = t('You have no unused codes available.');
      return FALSE;
    }
    // Remove empty spaces.
    $code = str_replace(' ', '', $code);
    foreach ($codes as $id => $stored) {
      // Remove spaces from stored code.
      if (str_replace(' ', '', $stored) === $code) {
        $this->isValid = TRUE;
        $this->usedCode = $id;
        return $this->isValid;
      }
    }
    $this->errorMessages['code'] = t('Invalid recovery code.');
    return $this->isValid;
  }

}

/**
 * Class TfaBasicRecoveryCode
 */
class TfaBasicRecoveryCodeSetup extends TfaBasicRecoveryCode implements TfaSetupPluginInterface {

  /**
   * @var int
   */
  protected $codeLimit;

  /**
   * @var array
   */
  protected $codes;

  public function __construct(array $context) {
    parent::__construct($context);
    $this->codeLimit = variable_get('tfa_recovery_codes_amount', 10);
  }

  /**
   * @copydoc TfaSetupPluginInterface::getSetupForm()
   */
  public function getSetupForm(array $form, array &$form_state) {

    $this->codes = $this->generateCodes();

    $form['codes'] = array(
      '#type' => 'item',
      '#title' => t('Your recovery codes'),
      '#description' => t('Print, save, or write down these codes for use in case you are without your application and need to log in.'),
      '#markup' => theme('item_list', array('items' => $this->codes)),
      '#attributes' => array('class' => array('recovery-codes')),
    );
    $form['actions']['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    return $form;
  }

  /**
   * @copydoc TfaSetupPluginInterface::validateSetupForm()
   */
  public function validateSetupForm(array $form, array &$form_state) {
    // Do nothing, TfaBasicRecoveryCodeSetup has no form inputs.
    return TRUE;
  }

  /**
   * @copydoc TfaSetupPluginInterface::submitSetupForm()
   */
  public function submitSetupForm(array $form, array &$form_state) {
    $this->storeCodes($this->codes);
    return TRUE;
  }

  /**
   * Delete existing codes.
   *
   * @return int
   */
  public function deleteCodes() {
    // Delete any existing codes.
    $num_deleted = db_delete('tfa_recovery_code')
      ->condition('uid', $this->context['uid'])
      ->execute();
    return $num_deleted;
  }

  /**
   * Overide TfaBasePlugin::generate().
   *
   * @return string
   */
  protected function generate() {
    $code = $this->generateBlock(3) . ' ' . $this->generateBlock(2) . ' ' . $this->generateBlock(3);
    return $code;
  }

  /**
   * Generate block of random digits.
   *
   * @param int $length
   * @return string
   */
  protected function generateBlock($length) {
    $block = '';
    do {
      $block .= ord(drupal_random_bytes(1));
    } while (strlen($block) <= $length);

    return substr($block, 0, $length);
  }

  /**
   * Generate recovery codes.
   *
   * Note, these are un-encrypted codes. For any long-term storage be sure to
   * encrypt.
   *
   * @return array
   */
  protected function generateCodes() {
    $codes = array();
    for ($i = 0; $i < $this->codeLimit; $i++) {
      $codes[] = $this->generate();
    }
    return $codes;
  }

  /**
   * Save codes for account.
   *
   * @param array $codes
   */
  protected function storeCodes($codes) {
    $num_deleted = $this->deleteCodes();
    // Encrypt code for storage.
    foreach ($codes as $code) {
      $encrypted = $this->encrypt($code);
      // Data is binary so store base64 encoded.
      $record = array(
        'uid' => $this->context['uid'],
        'code' => base64_encode($encrypted),
        'created' => REQUEST_TIME
      );
      drupal_write_record('tfa_recovery_code', $record);
    }

    $message = 'Saved recovery codes for user !uid';
    if ($num_deleted) {
      $message .= ' and deleted !del old codes';
    }
    watchdog('tfa_basic', $message, array('!uid' => $this->context['uid'], '!del' => $num_deleted), WATCHDOG_INFO);
  }
}
