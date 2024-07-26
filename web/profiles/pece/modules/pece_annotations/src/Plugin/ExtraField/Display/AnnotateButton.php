<?php

namespace Drupal\pece_annotations\Plugin\ExtraField\Display;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\extra_field_plus\Plugin\ExtraFieldPlusDisplayBase;

/**
 * Annotate button pseudo-field display.
 *
 * @ExtraFieldDisplay(
 *   id = "pece_annotations_annotate_button",
 *   label = @Translation("Annotate button"),
 *   bundles = {
 *     "node.*"
 *   },
 *   visible = false
 * )
 */
class AnnotateButton extends ExtraFieldPlusDisplayBase {

  /**
   * {@inheritdoc}
   */
  public function view(ContentEntityInterface $entity) {
    $settings = $this->getEntityExtraFieldSettings();
    $link_to_entity = $settings['link_to_entity'];
    $wrapper = $settings['wrapper'];
    // Indicate that this is the example:
    $label = $entity->label() . ' (from extra_field_plus example)';
    $url = NULL;

    // These prepopulated reference links can only be provided to artifacts.
    if (strpos($entity->bundle(), 'artifact') === FALSE) {
      return;
    }

    $url = base_path() . 'node/add/pece_annotation?edit[field_annotation_artifact][widget][0][target_id]=' . $entity->id();
    $build = [
      '#type' => 'inline_template',
      '#template' => '<a href="{{ url }}" class="button is-primary is-medium">{{ label}}</a>',
      '#context' => [
        'url' => $url,
        'label' => $this->t('Annotate'),
      ],
    ];
    return $build;
  }

  /**
   * {@inheritdoc}
   */
  protected static function extraFieldSettingsForm(): array {
    $form = parent::extraFieldSettingsForm();

    $form['link_to_entity'] = [
      '#type' => 'checkbox',
      '#title' => t('Link to the entity'),
    ];

    $form['wrapper'] = [
      '#type' => 'select',
      '#title' => t('Wrapper'),
      '#options' => [
        'span' => 'span',
        'p' => 'p',
        'h1' => 'h1',
        'h2' => 'h2',
        'h3' => 'h3',
        'h4' => 'h4',
        'h5' => 'h5',
      ],
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  protected static function defaultExtraFieldSettings(): array {
    $values = parent::defaultExtraFieldSettings();

    $values += [
      'link_to_entity' => FALSE,
      'wrapper' => 'span',
    ];

    return $values;
  }

  /**
   * {@inheritdoc}
   */
  protected static function settingsSummary(string $field_id, string $entity_type_id, string $bundle, string $view_mode = 'default'): array {
    return [
      t('Link to the entity: @link', [
        '@link' => self::getExtraFieldSetting($field_id, 'link_to_entity', $entity_type_id, $bundle, $view_mode) ? t('Yes') : t('No'),
      ]),
      t('Wrapper: @wrapper', [
        '@wrapper' => self::getExtraFieldSetting($field_id, 'wrapper', $entity_type_id, $bundle, $view_mode),
      ]),
    ];
  }

}
