<?php

namespace Drupal\pece_annotations\Plugin\ExtraField\Display;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\extra_field_plus\Plugin\ExtraFieldPlusDisplayBase;

/**
 * Annotate button pseudo-field display.
 *
 * @TODO restrict to artifact bundles?  Or too much risk of bug of not being available when new one added.
 *
 * @ExtraFieldDisplay(
 *   id = "pece_annotations_annotate_button",
 *   label = @Translation("Annotate button"),
 *   bundles = {
 *     "node.*"
 *   },
 *   visible = false
 * )
 */
class AnnotateButton extends ExtraFieldPlusDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {

    // These prepopulated reference links can only be provided to artifacts
    // OR to essays (PECE, timeline, photo).
    if (strpos($entity->bundle(), 'artifact') === FALSE
      && strpos($entity->bundle(), 'essay') === FALSE) {
      return;
    }

    $content_type = \Drupal::entityTypeManager()->getStorage('node_type')->load($entity->bundle())->label();

    $url = base_path() . 'node/pece_annotation/step_1?artifact=' . $entity->id();
    $build = [
      '#type' => 'inline_template',
      '#template' => '<a href="{{ url }}" title="{{ tooltip }}" class="button is-primary is-medium">{{ label}}</a>',
      '#context' => [
        'url' => $url,
        'label' => $this->t('Annotate'),
        'tooltip' => $this->t('Create new Annotation content referencing this :content_type', [':content_type' => $content_type]),
      ],
    ];
    return $build;
  }

}
