<?php

namespace Drupal\pece_ai\Ajax;

use Drupal\Core\Ajax\AjaxResponse;
use Drupal\Core\Ajax\ReplaceCommand;
use Drupal\Core\Form\FormStateInterface;

/**
 * AJAX form callback for the Writing Companion "Find related content" button.
 */
class WritingCompanionCallback {

  /**
   * AJAX callback: embeds current draft text and returns similar content.
   *
   * @param array $form
   *   The form array.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current form state.
   *
   * @return \Drupal\Core\Ajax\AjaxResponse
   *   An AJAX response replacing the #pece-ai-suggestions div.
   */
  public static function suggest(
    array &$form,
    FormStateInterface $form_state,
  ): AjaxResponse {
    $response = new AjaxResponse();
    $renderer = \Drupal::service('renderer');

    $title = (string) (
      $form_state->getValue(['title', 0, 'value']) ?? ''
    );
    $body = (string) (
      $form_state->getValue(['body', 0, 'value']) ?? ''
    );
    $text = trim(
      $title . "\n\n" . trim(html_entity_decode(strip_tags($body)))
    );

    if ($text === '') {
      $build = [
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#attributes' => [
          'id' => 'pece-ai-suggestions',
          'class' => ['pece-ai-suggestions', 'panel'],
        ],
        'message' => [
          '#type' => 'html_tag',
          '#tag' => 'p',
          '#attributes' => [
            'class' => ['panel-block', 'has-text-grey'],
          ],
          '#value' => t(
            'Add a title or some text to find related content.'
          ),
        ],
      ];
      $response->addCommand(
        new ReplaceCommand(
          '#pece-ai-suggestions',
          $renderer->renderInIsolation($build)
        )
      );
      return $response;
    }

    try {
      $vector = \Drupal::service('pece_ai.embedding_service')
        ->embed($text);
    }
    catch (\RuntimeException $e) {
      $build = [
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#attributes' => [
          'id' => 'pece-ai-suggestions',
          'class' => ['pece-ai-suggestions', 'panel'],
        ],
        'message' => [
          '#type' => 'html_tag',
          '#tag' => 'p',
          '#attributes' => [
            'class' => ['panel-block', 'has-text-grey'],
          ],
          '#value' => t('Could not load suggestions right now.'),
        ],
      ];
      $response->addCommand(
        new ReplaceCommand(
          '#pece-ai-suggestions',
          $renderer->renderInIsolation($build)
        )
      );
      return $response;
    }

    $groupIds = [];
    $platformWide = (bool) $form_state->getValue('pece_ai_platform_wide');
    if (!$platformWide) {
      $uid = \Drupal::currentUser()->id();
      $userEntity = \Drupal::entityTypeManager()
        ->getStorage('user')
        ->load($uid);
      if ($userEntity
        && $userEntity->hasField('field_groups_with_view_access')
        && !$userEntity->get('field_groups_with_view_access')->isEmpty()
      ) {
        foreach (
          $userEntity->get('field_groups_with_view_access') as $item
        ) {
          $groupIds[] = (string) $item->target_id;
        }
      }
    }

    $hits = \Drupal::service('pece_ai.similarity_service')
      ->findSimilarByVector($vector, 5, $groupIds);

    $items = [];
    foreach ($hits as $hit) {
      $entity = \Drupal::entityTypeManager()
        ->getStorage($hit['entity_type'])
        ->load($hit['entity_id']);
      if ($entity && $entity->access('view')) {
        $items[] = ['entity' => $entity, 'score' => $hit['score']];
      }
    }

    $scopeLabel = $platformWide
      ? t('Platform-wide')
      : t('Within your groups');
    $build = [
      '#theme' => 'pece_ai_related_content',
      '#items' => $items,
      '#scope_label' => $scopeLabel,
      '#toggle_url' => NULL,
      '#prefix' => '<div id="pece-ai-suggestions"'
      . ' class="pece-ai-suggestions panel">',
      '#suffix' => '</div>',
    ];
    $response->addCommand(
      new ReplaceCommand(
        '#pece-ai-suggestions',
        $renderer->renderInIsolation($build)
      )
    );
    return $response;
  }

}
