<?php

namespace Drupal\pece_ai\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Cache\Cache;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\pece_ai\Service\ActivityFeedService;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Provides a personalized discovery feed block for the researcher dashboard.
 *
 * @Block(
 *   id = "pece_ai_discovery_feed",
 *   admin_label = @Translation("Suggested for You (AI)"),
 *   category = @Translation("PECE")
 * )
 */
class DiscoveryFeedBlock extends BlockBase implements ContainerFactoryPluginInterface {

  /**
   * Constructs a DiscoveryFeedBlock.
   *
   * @param array $configuration
   *   A configuration array.
   * @param string $plugin_id
   *   The plugin ID.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Session\AccountProxyInterface $currentUser
   *   The current user.
   * @param \Drupal\pece_ai\Service\ActivityFeedService $activityFeedService
   *   The activity feed service.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    private readonly AccountProxyInterface $currentUser,
    private readonly ActivityFeedService $activityFeedService,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): static {
    return new static(
      $configuration, $plugin_id, $plugin_definition,
      $container->get('current_user'),
      $container->get('pece_ai.activity_feed_service'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function build(): array {
    $uid = (int) $this->currentUser->id();
    if ($uid === 0) {
      return [];
    }

    $cacheBase = [
      'contexts' => ['user'],
      'tags' => ['node_list', 'pece_ai_activity:' . $uid],
      'max-age' => 3600,
    ];

    $items = $this->activityFeedService->getFeedForUser($uid);

    if (empty($items)) {
      return [
        '#markup' => $this->t('Start exploring content to get personalized suggestions.'),
        '#cache' => $cacheBase,
      ];
    }

    return [
      '#theme' => 'pece_ai_related_content',
      '#items' => $items,
      '#scope_label' => $this->t('Based on your recent activity'),
      '#toggle_url' => NULL,
      '#cache' => $cacheBase,
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheTags(): array {
    $uid = (int) $this->currentUser->id();
    return Cache::mergeTags(
      parent::getCacheTags(),
      ['node_list', 'pece_ai_activity:' . $uid]
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheContexts(): array {
    return Cache::mergeContexts(parent::getCacheContexts(), ['user']);
  }

  /**
   * {@inheritdoc}
   */
  public function getCacheMaxAge(): int {
    return 3600;
  }

}
