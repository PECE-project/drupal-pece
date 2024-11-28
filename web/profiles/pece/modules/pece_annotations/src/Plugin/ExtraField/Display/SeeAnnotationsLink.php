<?php

namespace Drupal\pece_annotations\Plugin\ExtraField\Display;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\extra_field_plus\Plugin\ExtraFieldPlusDisplayBase;

/**
 * Annotations referencing the current node pseudo-field display.
 *
 * @TODO restrict to artifact bundles?  Or too much risk of bug of not being available when new one added.
 *
 * @ExtraFieldDisplay(
 *   id = "pece_annotations_see_annotations_link",
 *   label = @Translation("Link to see all related annotations"),
 *   bundles = {
 *     "node.*"
 *   },
 *   visible = false
 * )
 */
class SeeAnnotationsLink extends ExtraFieldPlusDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {

    // These prefilled facet links can only be provided to artifacts.
    // OR to essays (PECE, timeline, photo) OR memos.
    if (strpos($entity->bundle(), 'artifact') === FALSE
      && strpos($entity->bundle(), 'essay') === FALSE
      && $entity->bundle() !== 'pece_memo') {
      return;
    }

    $content_type = \Drupal::entityTypeManager()->getStorage('node_type')->load($entity->bundle())->label();

    $url = base_path() . 'search?type[0]=pece_annotation&annotated_artifact[0]=' . $entity->id();
    $build = [
      '#type' => 'inline_template',
      '#template' => '<a href="{{ url }}" title="{{ tooltip }}" class="is-primary is-medium">{{ label}}</a>',
      '#context' => [
        'url' => $url,
        'label' => $this->t('See all Annotations of this Artifact'),
        'tooltip' => $this->t('Filter content to that which annotates this :content_type', [':content_type' => $content_type]),
      ],
    ];
    return $build;
  }

}
