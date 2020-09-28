<?php

/**
 * @file
 * Tests for the TfaLoginPluginInterface.
 */

/**
 * Class TfaTestLogin.
 */
class TfaTestLogin extends TfaBasePlugin implements TfaLoginPluginInterface {

  /**
   * User ID.
   *
   * @var int
   */
  protected $loginUid;

  /**
   * Constructor.
   */
  public function __construct($uid, array $context = array()) {
    parent::__construct($context);
    $this->loginUid = $uid;
  }

  /**
   * {@inheritdoc}
   */
  public function loginAllowed() {
    if ($this->context['uid'] === $this->loginUid) {
      return TRUE;
    }
    return FALSE;
  }

}
