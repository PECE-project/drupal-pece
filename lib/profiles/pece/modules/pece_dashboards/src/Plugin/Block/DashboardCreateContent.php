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

    $artifactsItems = [
      '#theme' => 'item_list',
      '#list_type' => 'ul',
      '#items' => [],
      '#attributes' => ['class' => ['artifacts_items', 'hide']],
      '#wrapper_attributes' => ['id' => 'artifacts_menu'],
      '#prefix' => '<a href="#" class="pece_dashboards_artifacts_title">' . $this->t('Artifacts') . '</a>',
    ];

    $block['content'] = [
      '#theme' => 'item_list',
      '#list_type' => 'ul',
      '#items' => ['Artifacts' => $artifactsItems],
      '#wrapper_attributes' => ['class' => 'container'],
      '#attached' => [
        'library' => [
          'pece_dashboards/dashboard',
        ],
      ],
    ];

    foreach ($types as $key => $value) {

      $isArtifact = str_contains($types[$key], 'Artifact - ');
      $typeName = $isArtifact ? str_replace('Artifact - ', '', $types[$key]) : $types[$key];

      $addProjectLink = [
        '#title' => $this->t($typeName),
        '#type' => 'link',
        '#url' => \Drupal\Core\Url::fromRoute('node.add', ['node_type' => $key]),
      ];

      if ($isArtifact) {
        array_push($block['content']['#items']['Artifacts']['#items'], $addProjectLink);
      } else {
        array_push($block['content']['#items'], $addProjectLink);
      }
    }

    return $block;
  }

  private function sortContentTypesList(array $contentTypes) {
    
    $contentTypes = array_flip($contentTypes);
    ksort($contentTypes);

    return array_flip($contentTypes);

  }

}