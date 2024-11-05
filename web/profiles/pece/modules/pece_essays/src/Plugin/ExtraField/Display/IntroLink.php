<?php

namespace Drupal\pece_essays\Plugin\ExtraField\Display;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\extra_field\Plugin\ExtraFieldDisplayBase;

/**
 * Example Extra field Display.
 *
 * @ExtraFieldDisplay(
 *   id = "pece_essays_intro_link",
 *   label = @Translation("Link to view introduction"),
 *   description = @Translation("Displays a button link to view the introduction of the current PECE Essay."),
 *   bundles = {
 *     "node.pece_essay",
 *     "node.pece_timeline_essay",
 *     "node.pece_photo_essay",
 *   }
 * )
 */
class IntroLink extends ExtraFieldDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {
    $build['link'] = [
      '#type' => 'component',
      '#component' => 'pece:link-button',
      '#props' => [
         // Our OutboundPathProcessor makes this get the '/intro' suffix.
        'url' => $entity->toUrl()->toString(),
        'label' => t('View introduction'),
        'classes' => ['button'],
      ],
    ];
    return $build;
  }

}

