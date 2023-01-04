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

    $config = \Drupal::service('config.factory')->getEditable('about.settings');

    return [
      '#type' => 'container',
      '#markup' => $config->get('body'),
    ];
  }

}
