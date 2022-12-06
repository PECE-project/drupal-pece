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
    $summary = text_summary(_theme('about_pece'), 'panopoly_wysiwyg_text', 800);

    // Add ellipsis and read more link.
    return pece_about_trim_summary($summary, TRUE);
  }

}
