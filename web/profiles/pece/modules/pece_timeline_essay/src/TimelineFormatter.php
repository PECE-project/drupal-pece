<?php

namespace Drupal\pece_timeline_essay;

use Drupal\Core\Url;
use Drupal\file\Entity\File;
use Drupal\node\Entity\Node;
use Drupal\media\Entity\Media;
use Drupal\paragraphs\Entity\Paragraph;

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
  public function __construct() {
    $this->formattedTimeline = [];
  }

  /**
   * Receives the Timeline Essay Node and returns a string in the JSON format.
   *
   * @param \Drupal\node\Entity\Node $timelineEssay
   *   A node object of type Timeline Essay.
   *
   * @return string
   *   A string in the JSON format.
   */
  public function formatTimeline(Node $timelineEssay) {
    $timelineArray = [];
    $timelineArray['events'] = [];

    $timelineItems = $timelineEssay->field_pece_timeline_essay_items->referencedEntities();
    foreach ($timelineItems as $timelineItem) {
      $timelineArray['events'][] = $this->formatSlide($timelineItem);
    }

    return json_encode($timelineArray);
  }

  /**
   * Receives Timeline Essay Item and returns an array.
   *
   * @param \Drupal\paragraphs\Entity\Paragraph $timelineItem
   *   A paragraph entity object with information about the timeline slide.
   *
   * @return array
   *   An array with unique_id, text, media, start_date, end_date and background
   *   keys.
   */
  public function formatSlide(Paragraph $timelineItem) {
    return [
      'unique_id' => $timelineItem->uuid(),
      'text' => $this->formatText($timelineItem, $this->appendArtifactLink($timelineItem, $timelineItem->field_description->first()->getValue()['value'])),
      'media' => $this->formatMedia($this->prepareMediaField($timelineItem)),
      'start_date' => $this->formatDate($timelineItem->field_pece_start_end_date->first()->getValue()['value']),
      'end_date' => $this->formatDate($timelineItem->field_pece_start_end_date->first()->getValue()['end_value']),
      'background' => $this->formatBgColor($timelineItem),
    ];
  }

  /**
   * Receives artifact and returns its media field or false if no media field.
   *
   * @param \Drupal\node\Entity\Node $artifact
   *   Artifact Node of type audio, image, pdf, text, video or website.
   *
   * @return \Drupal\Core\Field\EntityReferenceFieldItemList|bool
   *   Returns the Media Entity reference that was on the artifact. Or false,
   *   if there are no Media Entity referenced.
   */
  public function getArtifactMediaField(Node $artifact) {
    $artifact_field = [
      'pece_artifact_audio' => 'field_pece_media_audio',
      'pece_artifact_image' => 'field_pece_media_image',
      'artifact_video' => 'field_pece_media_video',
      // 'pece_artifact_website' => 'field_website_url',
      'pece_artifact_pdf' => 'field_pece_media_pdf',
      // 'pece_artifact_text' => 'body',
    ];
    if (!in_array($artifact->getType(), array_keys($artifact_field))) {
      return FALSE;
    }
    $field = $artifact_field[$artifact->getType()];
    return $artifact->get($field);
  }

  /**
   * Extracts TL Essay Item fields to build TimelineJS Media field JSON object.
   *
   * @param Drupal\paragraphs\Entity\Paragraph $timelineItem
   *   Timeline Essay Item entity reference.
   *
   * @return \Drupal\Core\Field\EntityReferenceFieldItemList|false
   *   Returns the Media Entity reference that was on the artifact. Or false,
   *   if there are no Media Entity referenced.
   */
  public function prepareMediaField(Paragraph $timelineItem) {
    $artifactId = $timelineItem->field_pece_timeline_artifact->first()->getValue()['target_id'];
    $artifact = Node::load($artifactId);

    return $this->getArtifactMediaField($artifact);
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
      $fileId = $timelineItem->field_pece_timeline_background->first()->getValue()['target_id'];
      $file = File::load($fileId);
      $fileUrl = \Drupal::request()->getSchemeAndHttpHost() . $file->createFileUrl();
      $bgImg = $this->formatTlField("url", $fileUrl);
      $bgColor = array_merge($bgColor, $bgImg);
    }

    return $bgColor;
  }

  /**
   * Formats text and headline to be inserted in the slide's text key.
   *
   * @param \Drupal\paragraph\Entity\Paragraph $timelineItem
   *   The timeline item to be formatted as a slide.
   * @param string $content
   *   The string content to be inserted as text.
   *
   * @return array
   *   An array with headline and text keys
   */
  public function formatText(Paragraph $timelineItem, string $content) {
    $text_obj = $this->formatTlField('text', $content);
    $text_obj['headline'] = $timelineItem->field_title->first()->getValue()["value"];
    return $text_obj;
  }

  /**
   * Format Media Entity to TimelineJS media object structure.
   *
   * @param mixed $media
   *   Receives Media Entity from the Artifact node.
   *
   * @return array
   *   Returns an array with url of the media object or empty if there is no
   *   media object.
   */
  public function formatMedia($media) {
    $rtn = [];
    if ($media) {
      $mediaId = $media->first()->getValue()["target_id"];
      $file = $this->getFileFromMediaId($mediaId);
      $rtn["url"] = \Drupal::request()->getSchemeAndHttpHost() . $file->createFileUrl();
    }
    else {
      $rtn["url"] = "";
    }

    return $rtn;
  }

  /**
   * Returns the file object from the Media Entity ID.
   *
   * @param int $mediaId
   *   Media Fields.
   *
   * @return \Drupal\file\Entity\File
   *   Fields array or false if no fields.
   */
  private function getFileFromMediaId(int $mediaId) {
    $mediaTypeMapping = [
      'audio' => 'field_media_audio_file',
      'image' => 'field_media_image',
      'video' => 'field_media_video_file',
      'pdf_document' => 'field_media_file',
    ];

    $media = Media::load($mediaId);
    $field = $mediaTypeMapping[$media->bundle()];
    $fileId = $media->get($field)->first()->getValue()['target_id'];

    return File::load($fileId);
  }

}
