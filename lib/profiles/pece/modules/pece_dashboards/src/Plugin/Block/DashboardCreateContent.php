<?php

namespace Drupal\pece_dashboards\Plugin\Block;

use Drupal\Core\Block\BlockBase;

/**
 * Provides the Add content block for user dashboard.
 *
 * @Block(
 *   id = "pece_dashboards_user_dashboard_add_content",
 *   admin_label = @Translation("Add Content"),
 *   category = @Translation("PECE")
 * )
 */
class DashboardCreateContent extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    return [
        '#type' => 'container',
        '#markup' => 'this is my block'
    ];
  }

}
