<?php

use Drupal\pece_timeline_essay\TimelineEssayItemFormatter;

/**
 * Wrap node's timeline essay items with EntityMetadataWrapper.
 *
 * @param $node
 * @return mixed
 */
function pece_timeline_essay_pane_get_items($node) {
  $nodeWpr = entity_metadata_wrapper('node', $node);
  return $nodeWpr->field_pece_timeline_essay_items->getIterator();
}

/**
 * Build Timeline Items slide structure for TimelineJS plugin.
 *
 * @param $node
 * @return mixed
 * @throws \Exception
 */
function pece_timeline_essay_get_tl_items($node) {
  $tlei_slides = array();
  $TlFormatter = new TimelineEssayItemFormatter(entity_metadata_wrapper('node', $node));
  foreach (pece_timeline_essay_pane_get_items($node) as $item) {
    $tlei_slides[] = pece_timeline_tl_slide_prepare($item, $TlFormatter);
  }
  return $tlei_slides;
}

/**
 * Format TimelineJS Slides structure.
 *
 * @param $item Timeline Essay Item Entity
 * @param \Drupal\pece_timeline_essay\TimelineEssayItemFormatter $formatter
 * @return array
 * @throws \Exception
 */
function pece_timeline_tl_slide_prepare($item, TimelineEssayItemFormatter $formatter) {
  return array (
    'unique_id' => $item->uuid->value(),
    'text' => $formatter->formatText($item, $formatter->appendArtifactLink($item, $item->field_description->value())),
    'media' => $formatter->formatMedia($formatter->prepareMediaFileObj($item)),
    'start_date' => $formatter->formatDate($item->field_pece_start_end_date->value->value()),
    'end_date' => $formatter->formatDate($item->field_pece_start_end_date->value2->value()),
    'background' => $formatter->formatBgColor($item),
  );
}
