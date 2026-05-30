<?php

namespace Drupal\pece_ai\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\pece_ai\Service\SimilarityService;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\RequestStack;

/**
 * Provides a PECE AI Related Content sidebar block.
 *
 * @Block(
 *   id = "pece_ai_related_content",
 *   admin_label = @Translation("Related Content (AI)"),
 *   category = @Translation("PECE")
 * )
 */
class RelatedContentBlock extends BlockBase implements ContainerFactoryPluginInterface {

  /**
   * Constructs a RelatedContentBlock.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin ID for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Routing\RouteMatchInterface $routeMatch
   *   The current route match service.
   * @param \Drupal\pece_ai\Service\SimilarityService $similarityService
   *   The similarity service.
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityTypeManager
   *   The entity type manager.
   * @param \Symfony\Component\HttpFoundation\RequestStack $requestStack
   *   The request stack.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    private readonly RouteMatchInterface $routeMatch,
    private readonly SimilarityService $similarityService,
    private readonly EntityTypeManagerInterface $entityTypeManager,
    private readonly RequestStack $requestStack,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): static {
    return new static(
      $configuration, $plugin_id, $plugin_definition,
      $container->get('current_route_match'),
      $container->get('pece_ai.similarity_service'),
      $container->get('entity_type.manager'),
      $container->get('request_stack'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function build(): array {
    $node = $this->routeMatch->getParameter('node');
    if (!$node) {
      return [];
    }

    $request = $this->requestStack->getCurrentRequest();
    $isGlobal = $request && $request->query->get('ai_scope') === 'global';
    $groupIds = [];
    if (!$isGlobal && $node->hasField('field_groups') && !$node->get('field_groups')->isEmpty()) {
      foreach ($node->get('field_groups') as $item) {
        $groupIds[] = (string) $item->target_id;
      }
    }

    $results = $this->similarityService->findSimilar($node, 5, $groupIds);

    if (empty($results) && $this->similarityService->getVector($node) === NULL) {
      return [
        '#markup' => $this->t('Related content is being indexed…'),
        '#cache' => ['max-age' => 60],
      ];
    }

    $items = [];
    foreach ($results as $result) {
      $entity = $this->entityTypeManager
        ->getStorage($result['entity_type'])
        ->load($result['entity_id']);
      if ($entity) {
        $items[] = ['entity' => $entity, 'score' => $result['score']];
      }
    }

    $toggleUrl = '';
    if ($request) {
      $toggleUrl = $isGlobal ? $request->getPathInfo() : $request->getPathInfo() . '?ai_scope=global';
    }
    $scopeLabel = $isGlobal ? $this->t('Platform-wide') : (
      $groupIds ? $this->t('Within group') : $this->t('Platform-wide')
    );

    return [
      '#theme' => 'pece_ai_related_content',
      '#items' => $items,
      '#scope_label' => $scopeLabel,
      '#toggle_url' => $toggleUrl,
      '#cache' => [
        'tags' => $node->getCacheTags(),
        'contexts' => ['url.query_args:ai_scope'],
      ],
    ];
  }

}
