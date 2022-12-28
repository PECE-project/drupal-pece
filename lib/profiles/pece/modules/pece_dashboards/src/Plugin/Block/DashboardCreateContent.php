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

    $skipTypes = [
      'about_page',
      'pece_annotation',
      'page',
      'pece_slideshow_image'
    ];

    $types = $this->getExistingContentTypes($skipTypes);

    return $this->buildRenderArray($types);

  }

  /**
   * Returns a list of all the content types currently installed.
   *
   * @return array
   *   An array of content types.
   */
  public function getExistingContentTypes(array $skipTypes = []) {

    $contentTypes = array_map(function ($bundle_info) {
                      return $bundle_info['label'];
                    }, \Drupal::service('entity_type.bundle.info')
                        ->getBundleInfo('node'));

    foreach ($skipTypes as $skipType) {
      unset($contentTypes[$skipType]);
    }

    return $this->sortContentTypesList($contentTypes);
  }

  /**
   * Returns a drupal render array of all the content types currently installed.
   *
   * @return array
   *   An array of content types.
   */
  public function buildRenderArray(array $types = null) {

    $block['content'] = [
      '#theme' => 'item_list',
      '#list_type' => 'ul',
      '#items' => [],
      '#attributes' => ['class' => 'mylist'],
      '#wrapper_attributes' => ['class' => 'container'],
    ];

    foreach ($types as $key => $value) {

      $addProjectLink = [
          '#title' => $this->t($types[$key]),
          '#type' => 'link',
          '#url' => \Drupal\Core\Url::fromRoute('node.add', ['node_type' => $key]),
        ];
  
      array_push($block['content']['#items'], $addProjectLink);
    }

    return $block;
  }

  private function sortContentTypesList(array $contentTypes) {
    
    foreach ($contentTypes as $key => $value) {
      $contentTypes[$key] = str_replace('Artifact - ', '', $contentTypes[$key]);
    }

    $contentTypes = array_flip($contentTypes);
    ksort($contentTypes);

    return array_flip($contentTypes);

  }

}