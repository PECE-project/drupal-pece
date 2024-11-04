<?php

namespace Drupal\pece_timeline_essay\Plugin\ExtraField\Display;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\extra_field\Plugin\ExtraFieldDisplayBase;
use Drupal\node\Entity\Node;
use Drupal\pece_timeline_essay\TimelineFormatter;

/**
 * Example Extra field Display.
 *
 * @ExtraFieldDisplay(
 *   id = "pece_timeline_essay",
 *   label = @Translation("Timeline essay"),
 *   description = @Translation("Displays a formatted timeline."),
 *   bundles = {
 *     "node.pece_timeline_essay",
 *   }
 * )
 */
class Timeline extends ExtraFieldDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {
    $timeline = $entity;
    $timelineFormatter = new TimelineFormatter();
    $formattedTimeline = $timelineFormatter->formatTimeline($timeline);
    $build = [
      '#theme' => 'timeline_essay_view',
      '#attached' => [
        'library' => 'pece_timeline_essay/pece-timeline',
        'drupalSettings' => [
          'slides' => $formattedTimeline,
          'slideSettings' => [],
        ],
      ],
    ];
    return $build;
  }

}

