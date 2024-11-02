<?php

namespace Drupal\pece_essays\PathProcessor;

use Drupal\Core\PathProcessor\OutboundPathProcessorInterface;
use Drupal\Core\Render\BubbleableMetadata;
use Symfony\Component\HttpFoundation\Request;

class OutboundPathProcessor implements OutboundPathProcessorInterface {

  /**
   * {@inheritdoc}
   */
  public function processOutbound($path, &$options = [], Request $request = NULL, BubbleableMetadata $bubbleable_metadata = NULL) {
    if (!isset($options['entity'])
      || $options['route']->getPath() !== "/node/{node}"
      || ! $options['entity'] instanceof \Drupal\node\NodeInterface
    ) {
      return $path;
    }
    // We are linking to a node at its canonical path.
    /** @var Drupal\node\NodeInterface $node */
    $node = $options['entity'];
    if ($node->bundle() === "pece_essay"
      || $node->bundle() === "pece_photo_essay"
      || $node->bundle() === "pece_timeline_essay"
    ) {
      return $path . '/intro';
    }
    return $path;
  }
}
