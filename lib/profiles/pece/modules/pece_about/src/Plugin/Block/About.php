<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the About block.
 *
 * @Block(
 *   id = "pece_about_about",
 *   admin_label = @Translation("About")
 * )
 */
class About extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {

    return [
      '#type' => 'container',
      '#markup' => 'PECE About block',
    ];
  }

}
