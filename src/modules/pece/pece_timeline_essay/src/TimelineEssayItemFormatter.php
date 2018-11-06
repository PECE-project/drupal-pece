<?php

namespace Drupal\pece_timeline_essay;

class TimelineEssayItemFormatter {

  protected $timelineEssay;

  function __construct(\EntityDrupalWrapper $TimelineNode) {
    $this->timelineEssay = $TimelineNode;
  }

  /**
   * Append node link to a given content.
   *
   * @param $TimelineItem Drupal entity
   * @param $content Entity field value
   * @return string
   * @throws \Exception
   */
  public function appendArtifactLink(\EntityDrupalWrapper $TimelineItem, $content) {
    $artifact_path = drupal_get_path_alias('node/' . $TimelineItem->field_pece_timeline_artifact->nid->value());
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
  public function formatDate($timestamp) {
    $default = array(
      'year' => date('Y', $timestamp),
      'month' => date('m', $timestamp),
      'day' => date('d', $timestamp),
    );
    return $default;
  }

  /**
   * Format a given value pair to TimelineJS standard field object structure.
   * @see: http://timeline.knightlab.com/docs/json-format.html
   *
   * @$type string TimelineJS field type
   * @$value string Content
   * @return array
   */
  public function formatTlField($type, $value) {
    $default = array(
      $type => $value,
    );
    return $default;
  }

  /**
   * Format color to TimelineJS background object structure.
   */
  public function formatBgColor($color) {
    return $this->formatTlField('color', $color);
  }

  /**
   * Format text to TimelineJS text object structure.
   */
  public function formatText($raw_data) {
    return $this->formatTlField('text', $raw_data) ;
  }

  /**
   * Format media to TimelineJS media object structure.
   */
  public function formatMedia($media_array) {
    $file_path = (!empty($media_array['uri'])) ? file_create_url($media_array['uri']) : '';
    $default = array(
      'url'=> $file_path,
      'caption' => $media_array['title'],
      'credit' => '',
    );
    return $default;
  }
}