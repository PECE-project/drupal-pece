<?php

namespace Drupal\pece_timeline_essay;

use Drupal\Core\Url;
use Drupal\node\Entity\Node;
use Drupal\paragraphs\Entity\Paragraph;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\entity_reference_revisions\Plugin\Field\FieldType\EntityReferenceRevisionsItem;

/**
 * {@inheritdoc}
 */
class TimelineFormatter {

  /**
   * {@inheritdoc}
   */
  protected $formattedTimeline;

  /**
   * {@inheritdoc}
   */
  protected $tlMediaObjAttr = [
    'url',
    'caption',
    'credit',
    'thumbnail',
    'alt',
    'title',
    'link',
    'link_target',
  ];

  /**
   * {@inheritdoc}
   */
  public function __construct() {
    $this->formattedTimeline = [];
  }

  /**
   * {@inheritdoc}
   */
  public function formatTimeline(Node $timelineEssay) {
    $timelineArray = [];
    $timelineArray['events'] = $this->formatTimelineEvents($timelineEssay);

    $obj = (object) $timelineArray;

    return json_encode($timelineArray);
  }

  /**
   * {@inheritdoc}
   */
  public function formatTimelineEvents(Node $timelineEssay) {

    $events = [];
    $timelineItems = $timelineEssay->field_pece_timeline_essay_items->referencedEntities();
    foreach ($timelineItems as $timelineItem) {
      $events[] = $this->formatSlide($timelineItem);
    }
    return $events;
  }

  /**
   * {@inheritdoc}
   */
  public function formatSlide(Paragraph $timelineItem) {
    return [
      'unique_id' => $timelineItem->uuid(),
      'text' => $this->formatText($timelineItem, $this->appendArtifactLink($timelineItem, $timelineItem->field_description->first()->getValue()['value'])),
      'media' => $this->formatMedia($this->prepareMediaFileObj($timelineItem)),
      'start_date' => $this->formatDate($timelineItem->field_pece_start_end_date->first()->getValue()['value']),
      'end_date' => $this->formatDate($timelineItem->field_pece_start_end_date->first()->getValue()['end_value']),
      'background' => $this->formatBgColor($timelineItem),
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getArtifactMediaFile(Node $artifactReference) {
    $artifactType = $artifactReference->getType();
    $artifact_field = [
      'pece_artifact_audio' => 'field_audio_audios',
      'pece_artifact_image' => 'field_image_images',
      'pece_artifact_video' => 'field_video_source',
      'pece_artifact_website' => 'field_website_url',
      'pece_artifact_pdf' => 'field_pdf_document',
      'pece_artifact_text' => 'body',
    ];
    if (!in_array($artifactReference->getType(), array_keys($artifact_field))) {
      return '';
    }
    $field = $artifact_field[$artifactReference->getType()];

    return $artifactReference->get($field)->first()->getValue()['value'];
  }

  /**
   * Extracts TL Essay Item fields to build TimelineJS Media field JSON object.
   *
   * @param Drupal\paragraphs\Entity\Paragraph $timelineItem
   *   Timeline Essay Item entity reference.
   *
   * @return array
   *   Array containing "file" as key and the artifacts as value.
   */
  public function prepareMediaFileObj(Paragraph $timelineItem) {
    $artifactId = $timelineItem->field_pece_timeline_artifact->first()->getValue()['target_id'];
    $artifact = Node::load($artifactId);
    $media = [
      'file' => $this->getArtifactMediaFile($artifact),
    ];
    return $media;
  }

  /**
   * Append node link to a given content.
   *
   * @param Drupal\paragraphs\Entity\Paragraph $timelineItem
   *   Timeline Item.
   * @param string $content
   *   Entity field value.
   *
   * @return string
   *   Returns the rendered html.
   *
   * @throws \Exception
   */
  public function appendArtifactLink(Paragraph $timelineItem, $content) {
    $renderer = \Drupal::service('renderer');
    $artifactId = $timelineItem->field_pece_timeline_artifact->first()->getValue()['target_id'];
    $artifact = Node::load($artifactId);
    $pathAlias = '/node/' . $artifactId;
    $artifactPath = \Drupal::service('path_alias.manager')->getAliasByPath($pathAlias);
    $artifactTitle = $artifact->getTitle();

    $titleWrapper = [
      '#type' => 'html_tag',
      '#tag' => 'h6',
      '#value' => $artifactTitle,
      '#attributes' => [
        'class' => 'pece-tle-item-title',
      ],
    ];
    $artifactLink = [
      '#type' => 'link',
      '#title' => 'See artifact details',
      '#url' => Url::fromUserInput($artifactPath),
    ];
    $linkWrapper = [
      '#type' => 'html_tag',
      '#tag' => 'p',
      '#value' => $renderer->render($artifactLink),
      '#attributes' => [
        'class' => 'pece-tle-item-link',
      ],
    ];
    return $content . $renderer->renderPlain($titleWrapper) . $renderer->render($linkWrapper);
  }

  /**
   * Format a given date to TimelineJS date object structure.
   *
   * @see: http://timeline.knightlab.com/docs/json-format.html
   */
  public function formatDate($timestamp) {
    $default = [
      'year' => date('Y', strtotime($timestamp)),
      'month' => date('m', strtotime($timestamp)),
      'day' => date('d', strtotime($timestamp)),
    ];
    return $default;
  }

  /**
   * Format a given value pair to TimelineJS standard field object structure.
   *
   * @see: http://timeline.knightlab.com/docs/json-format.html
   *
   * @$type string TimelineJS field type
   * @$value string Content
   * @return array
   *   Array of formatted field.
   */
  public function formatTlField($type, $value) {
    $default = [
      $type => $value,
    ];
    return $default;
  }

  /**
   * Format color to TimelineJS background object structure.
   */
  public function formatBgColor(Paragraph $timelineItem) {
    $bgColor = [];
    if (!$timelineItem->field_pece_timeline_color->isEmpty()) {
      $bgColor = $this->formatTlField('color', $timelineItem->field_pece_timeline_color->first()->getValue()['color']);
    }
    if (!$timelineItem->field_pece_timeline_background->isEmpty()) {
      $field_data = $timelineItem->field_pece_timeline_background->first()->getValue();
      $bgImg = $this->formatTlField('url', file_create_url($field_data['uri']));
      $bgColor = array_merge($bgColor, $bgImg);
    }

    return $bgColor;
  }

  /**
   * Format text to TimelineJS text object structure.
   */
  public function formatText(Paragraph $timelineItem, $content) {
    $text_obj = $this->formatTlField('text', $content);
    $text_obj['headline'] = $timelineItem->field_title->first()->getValue()["value"];
    return $text_obj;
  }

  /**
   * Format media to TimelineJS media object structure.
   */
  public function formatMedia($media_settings = []) {
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
    $media = (isset($media['url'])) ? $media : array_merge(['url' => ''], $media);
    return (isset($media)) ? $media : FALSE;
  }

  /**
   * Map TimelineJS media object structure to Timeline Essay Item media fields.
   *
   * @param array $media_fields
   *   Media Fields.
   *
   * @return array|bool
   *   Fields array or false if no fields.
   */
  private function mapMediaFields(array $media_fields) {
    $fields = [];
    foreach ($this->tlMediaObjAttr as $field) {
      if (
        !isset($media_fields[$field])
        || (isset($media_fields[$field]) && empty($media_fields[$field]))
      ) {
        continue;
      }
      $fields[$field] = $media_fields[$field];
    }
    return (isset($fields)) ? $fields : FALSE;
  }

}
