<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the AboutPece block.
 *
 * @Block(
 *   id = "pece_about_about_pece",
 *   admin_label = @Translation("About PECE")
 * )
 */
class AboutPece extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    return _theme('about_pece');
  }

}
