<?php

namespace Drupal\pece_timeline_essay\Controller;

use Drupal\node\Entity\Node;
use Drupal\Core\Controller\ControllerBase;
use Drupal\pece_timeline_essay\TimelineFormatter;

/**
 * Defines PeceTimelineEssayController class.
 */
class PeceTimelineEssayController extends ControllerBase {

  /**
   * Displays the Timeline essay.
   *
   * @param int $node
   *   Id of the timeline node.
   *
   * @return array
   *   Returns markup array.
   */
  public function content($node) {
    $timeline = Node::load($node);
    $timelineFormatter = new TimelineFormatter();
    $formattedTimeline = $timelineFormatter->formatTimeline($timeline);
    $build = [
      '#theme' => 'timeline_essay_view',
      '#content' => [
        'title' => $timeline->getTitle(),
        'button' => [
          '#type' => 'link',
          '#title' => $this->t('Return to Timeline Essay Landing Page'),
          '#url' => $timeline->toUrl(),
          '#attributes' => [
            'class' => [
              'btn',
              'btn-primary',
            ],
          ],
        ],
      ],
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
