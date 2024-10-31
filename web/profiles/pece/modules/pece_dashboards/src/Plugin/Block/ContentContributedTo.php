<?php

namespace Drupal\pece_dashboards\Plugin\Block;

use Drupal\Core\Block\Attribute\Block;
use Drupal\Core\Block\BlockBase;
use Drupal\Core\Cache\Cache;
use Drupal\Core\StringTranslation\TranslatableMarkup;

/**
 * Provides a link to content you have contributed to.
 */

#[Block(
  id: "pece_dashboards_content_contributed_to",
  admin_label: new TranslatableMarkup("Link to content the current user has contributed to"),
  category: new TranslatableMarkup("PECE")
)]

class ContentContributedTo extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function build() {
    $uid = \Drupal::currentUser()->id();
    $url = base_path() . 'search/?contributor[0]=' . $uid;
    $build['button'] = [
      '#type' => 'component',
      '#component' => 'pece_dashboards:button',
      '#props' => [
        'url' => $url,
        'label' => $this->t('Content I contributed to'),
        'tooltip' => $this->t('Filter all content on the site for ones where I am credited as a contributor, if any.'),
        'classes' => [],
      ],
    ];

    return $build;
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheContexts() {
    return Cache::mergeContexts(parent::getCacheContexts(), ['user']);
  }

}
