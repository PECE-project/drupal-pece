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
 *   }
 * )
 */
class IntroLink extends ExtraFieldDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {
    // This successfully gets our OutboundPathProcessor to make it go to '/intro'.
    $link_array = $entity->toLink()->toRenderable();
    $link_array['#title'] = t('View introduction');
    return $link_array;
  }

}

