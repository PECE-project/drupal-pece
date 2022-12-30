<?php

namespace Drupal\pece_about\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the AboutPeceSummary block.
 *
 * @Block(
 *   id = "pece_about_about_pece_summary",
 *   admin_label = @Translation("About PECE Summary")
 * )
 */
class AboutPeceSummary extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    // @FIXME
    // theme() has been renamed to _theme() and should NEVER be called directly.
    // Calling _theme() directly can alter the expected output and potentially
    // introduce security issues (see https://www.drupal.org/node/2195739). You
    // should use renderable arrays instead.
    //
    //
    // @see https://www.drupal.org/node/2195739
    $summary = [
      '#theme' => 'about_pece',
      '#markup' => '',
    ];

    return [
      '#type' => 'inline_template',
      '#template' => '{{ summary }}',
      '#context' => [
        'sommary' => $summary,
      ],
    ];
  }

}
