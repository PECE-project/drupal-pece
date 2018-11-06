<?php

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
 */
function pece_timeline_essay_get_tl_items($node) {
  $tlei_slides = array();
  foreach (pece_timeline_essay_pane_get_items($node) as $index => $item) {
    $tlei_slides[$index]['unique_id'] = $item->uuid->value();
    $tlei_slides[$index]['text'] = _tlei_format_text(_tlei_append_artifact_link($item, $item->field_description->value()));
    $tlei_slides[$index]['media'] = _tlei_format_media(tlei_get_artifact_value($item->field_pece_timeline_artifact));
    $tlei_slides[$index]['start_date'] = _tlei_format_date($item->field_pece_start_end_date->value->value());
    $tlei_slides[$index]['end_date'] = _tlei_format_date($item->field_pece_start_end_date->value2->value());
    $tlei_slides[$index]['background'] = (!empty($item->field_pece_timeline_color->value()))
      ? _tlei_format_bg_color($item->field_pece_timeline_color->rgb->value())
      : '';
  }
  return $tlei_slides;
}

function tlei_get_artifact_value($artifactWpr) {
  switch ($artifactWpr->type->value()) {
    case 'pece_artifact_audio':
      return $artifactWpr->field_pece_media_audio->value();
    case 'pece_artifact_image':
      return $artifactWpr->field_pece_media_image->value();
    case 'pece_artifact_video':
      return $artifactWpr->field_pece_media_video->value();
    case 'pece_artifact_website':
      return $artifactWpr->field_pece_website_url->value();
    case 'pece_artifact_pdf':
      return $artifactWpr->field_pece_media_pdf->value();
    case 'pece_artifact_text':
      return $artifactWpr->body->value();
    default:
      return Null;
  }
}


/**
 * Append node link to a given content.
 *
 * @param $entity Drupal entity
 * @param $content Entity field value
 * @return string
 * @throws \Exception
 */
function _tlei_append_artifact_link($entity, $content) {
  $artifact_path = drupal_get_path_alias('node/' . $entity->field_pece_timeline_artifact->nid->value());
  $node_link = array(
    'text' => 'Read more',
    'path' => url($artifact_path, array('absolute' => TRUE)),
    'options' => array(
      'attributes' => array(),
      'html' => FALSE,
    ),
  );
  $link_wrapper = array(
    '#theme' => 'html_tag',
    '#tag' => 'p',
    '#value' => theme('link', $node_link),
    '#attributes' => array(
      'class' => 'pece-tle-item-link',
    ),
  );
  return $content . drupal_render($link_wrapper);
}


/**
 * Format a given date to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_date($timestamp) {
  $default = array(
    'year' => date('Y', $timestamp),
    'month' => date('m', $timestamp),
    'day' => date('d', $timestamp),
  );
  return $default;
}

/**
 * Format a given text to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_text($raw_data) {
  $default = array(
    'text' => $raw_data
  );
  return $default;
}

/**
 * Format a given media to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_media($media_array) {
  $file_path = (!empty($media_array['uri'])) ? file_create_url($media_array['uri']) : '';
  $default = array(
    'url'=> $file_path,
    'caption' => $media_array['title'],
    'credit' => '',
  );
  return $default;
}

/**
 * Format a given background color to TimelineJS date object structure.
 * @see: http://timeline.knightlab.com/docs/json-format.html
 */
function _tlei_format_bg_color($color) {
  $default = array(
    'color'=> $color,
  );
  return $default;
}
