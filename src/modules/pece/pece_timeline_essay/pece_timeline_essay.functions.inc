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
    'text' => $formatter->formatText($formatter->appendArtifactLink($item, $item->field_description->value())),
    'media' => $formatter->formatMedia(tlei_get_artifact_value($item->field_pece_timeline_artifact)),
    'start_date' => $formatter->formatDate($item->field_pece_start_end_date->value->value()),
    'end_date' => $formatter->formatDate($item->field_pece_start_end_date->value2->value()),
    'background' => (!empty($item->field_pece_timeline_color->value()))
      ? $formatter->formatBgColor($item->field_pece_timeline_color->rgb->value())
      : '',
  );
}

/**
 * Artifacts media field map.
 *
 * @param $artifactWpr
 * @return mixed
 */
function tlei_get_artifact_value($artifactWpr) {
  $artifact_field = array(
    'pece_artifact_audio' => 'field_pece_media_audio',
    'pece_artifact_image' => 'field_pece_media_image',
    'pece_artifact_video' => 'field_pece_media_video',
    'pece_artifact_website' => 'field_pece_website_url',
    'pece_artifact_pdf' => 'field_pece_media_pdf',
    'pece_artifact_text' => 'body',
  );
  if (!in_array($artifactWpr->type->value(), array_keys($artifact_field))) {
    return '';
  }
  $field = $artifact_field[$artifactWpr->type->value()];
  return $artifactWpr->$field->value();
}