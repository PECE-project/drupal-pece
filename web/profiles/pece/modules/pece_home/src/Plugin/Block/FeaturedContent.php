<?php

namespace Drupal\pece_homepage\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the Featured Content block.
 *
 * @Block(
 *   id = "pece_home_featured",
 *   admin_label = @Translation("Featured")
 * )
 */
class FeaturedContent extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    $viewFeatured = 'Here goes the view of Featured content';
    return $viewFeatured;
  }

}
