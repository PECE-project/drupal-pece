<?php

namespace Drupal\pece_timeline_essay;

class TimelineEssayItemFormatter {

  protected $timelineEssay;
  protected $tlMediaObjAttr = array(
    'url',
    'caption',
    'credit',
    'thumbnail',
    'alt',
    'title',
    'link',
    'link_target',
  );

  function __construct(\EntityDrupalWrapper $TimelineNode) {
    $this->timelineEssay = $TimelineNode;
  }

  public function getArtifactMediaFile(\EntityDrupalWrapper $artifactWpr) {
    $artifact_field = array(
      'pece_artifact_audio' => 'field_pece_media_audio',
      'pece_artifact_image' => 'field_pece_media_image',
      'pece_artifact_video' => 'field_pece_media_video',
      'pece_artifact_website' => 'field_pece_website_url',
      'pece_artifact_pdf' => 'field_pece_media_pdf',
      'pece_artifact_text' => 'body',
    );
    if (!in_array($artifactWpr->getBundle(), array_keys($artifact_field))) {
      return '';
    }
    $field = $artifact_field[$artifactWpr->getBundle()];
    return $artifactWpr->$field->value();
  }

  /**
   * Extracts TL Essay Item fields to build TimelineJS Media field JSON object.
   *
   * @param \EntityDrupalWrapper Timeline Essay Item entity wrapper
   * @return array
   */
  public function prepareMediaFileObj(\EntityDrupalWrapper $tleiWpr) {
    $file = ($this->hasfield($tleiWpr, 'field_pece_timeline_media'))
      ? $tleiWpr->field_pece_timeline_media->value()
      : $this->getArtifactMediaFile($tleiWpr->field_pece_timeline_artifact);
    $thumbnail = ($this->hasField($tleiWpr, 'field_thumbnail'))
      ? $tleiWpr->field_thumbnail->value()
      : FALSE;
    $media = array(
      'file' => $file,
      'caption' => $this->prepareTimelineItemCaption($tleiWpr),
      'credit' => $this->prepareTimelineItemCredits($tleiWpr),
    );
    if ($thumbnail) {
      $media['thumbnail'] = $thumbnail;
    }
    return $media;
  }

  protected function hasfield(\EntityDrupalWrapper $timelineItem, $field_name) {
    return (null !== $timelineItem->$field_name && $timelineItem->$field_name->value());
  }

  protected function getRenderedField(\EntityDrupalWrapper $timelineItem, $field_name) {
    $field = field_view_field('pece_timeline_essay_item', $timelineItem->value(), $field_name);
    return drupal_render($field);
  }

  public function prepareTimelineItemCaption(\EntityDrupalWrapper $entityWpr){
    return $entityWpr->field_pece_timeline_caption->value();
  }

  public function prepareTimelineItemCredits(\EntityDrupalWrapper $entityWpr) {
    return drupal_render(field_view_field('pece_timeline_essay_item', $entityWpr->value(), 'field_image_credits'));
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
      'text' => 'See artifact details',
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
  public function formatBgColor(\EntityDrupalWrapper $timelineItem) {
    $bgColor = array();
    if (!empty($timelineItem->field_pece_timeline_color->value())) {
      $bgColor = $this->formatTlField('color', $timelineItem->field_pece_timeline_color->rgb->value());
    }
    if (!empty($timelineItem->field_pece_timeline_background->value())) {
      $field_data = $timelineItem->field_pece_timeline_background->value();
      $bgImg = $this->formatTlField('url', file_create_url($field_data['uri']));
      $bgColor = array_merge($bgColor, $bgImg);
    }

    return $bgColor;
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
  public function formatMedia($media_settings = array()) {
    $media = $this->mapMediaFields($media_settings);

    if (isset($media_settings['file']) && isset($media_settings['file']['uri'])) {
      $media['url'] = file_create_url($media_settings['file']['uri']);
      $media['alt'] = $media_settings['file']['alt'];
      $media['title'] = $media_settings['file']['title'];
    }

    if (isset($media_settings['thumbnail']) && isset($media_settings['thumbnail']['uri'])) {
      $media['thumbnail'] = file_create_url($media_settings['thumbnail']['uri']);
      $media['alt'] = $media_settings['thumbnail']['alt'];
      $media['title'] = $media_settings['thumbnail']['title'];
    }

    // Add mandatory url attr. on Timeline media object if still not present.
    $media = (isset($media['url'])) ? $media : array_merge(array('url' => ''), $media);
    return (isset($media)) ? $media : FALSE;
  }

  /**
   * Map TimelineJS media object structure to Timeline Essay Item media fields.
   * @param $media_fields
   * @return array|bool
   */
  private function mapMediaFields($media_fields) {
    $fields = array();
    foreach ($this->tlMediaObjAttr as $field) {
      if (!isset($media_fields[$field])
      || (isset($media_fields[$field]) && empty($media_fields[$field]))) {
        continue;
      }
      $fields[$field] = $media_fields[$field];
    }
    return (isset($fields)) ? $fields : FALSE;
  }
}