<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the About block.
 *
 * @Block(
 *   id = "pece_about_about_site",
 *   admin_label = @Translation("About this site")
 * )
 */
class AboutSiteBlock extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {

    $config = \Drupal::service('config.factory')->get('pece_about.settings');
    $content = $config->get('body');
    // Hide the block if no content.
    if (empty($content)) {
      return FALSE;
    }

    return [
      '#type' => 'container',
      '#markup' => $content,
    ];
  }

}
