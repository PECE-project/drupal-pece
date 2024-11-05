<?php

namespace Drupal\pece_essays\Plugin\ExtraField\Display;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\extra_field\Plugin\ExtraFieldDisplayBase;
use Drupal\Core\Url;

/**
 * Example Extra field Display.
 *
 * @ExtraFieldDisplay(
 *   id = "pece_essays_essay_link",
 *   label = @Translation("Link to view essay"),
 *   description = @Translation("Displays a button link to view the actual PECE Essay from the intro page."),
 *   bundles = {
 *     "node.pece_essay",
 *     "node.pece_timeline_essay",
 *     "node.pece_photo_essay",
 *   }
 * )
 */
class EssayLink extends ExtraFieldDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {
    $build['link'] = [
      '#type' => 'component',
      '#component' => 'pece:link-button',
      '#props' => [
        'url' => Url::fromRoute('entity.node.canonical', ['node' => $entity->id()])->toString(),
        'label' => t('View essay'),
        'classes' => ['button'],
      ],
    ];
    return $build;
  }

}
