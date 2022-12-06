<?php

namespace Drupal\pece_core\Controller;

use Drupal\Core\Controller\ControllerBase;

/**
 * Controller for the PECE Core module.
 *
 * @codeCoverageIgnore
 */
class PeceConfigController extends ControllerBase {

  /**
   * PECE Core constructor.
   */
  public function __construct() {

  }

  /**
   * Generate default config page for PECE distro.
   */
  public function overview() {
    return [
      '#type' => 'markup',
      '#markup' => 'PECE Configuration',
    ];
  }
}
