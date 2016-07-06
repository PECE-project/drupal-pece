<?php

/**
 * @file
 * ExpireException class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Exception;

/**
 * ExpireException class.
 */
class ExpireException extends \Exception {

  /**
   * Constructs a ExpireException object.
   */
  public function __construct($message, $code = 0, \Exception $previous = NULL) {
    // Make sure everything is assigned properly.
    parent::__construct($message, $code, $previous);
  }

}
