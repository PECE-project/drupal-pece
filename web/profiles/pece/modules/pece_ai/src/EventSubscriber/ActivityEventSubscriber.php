<?php

namespace Drupal\pece_ai\EventSubscriber;

use Drupal\Core\Cache\Cache;
use Drupal\Component\Datetime\TimeInterface;
use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\node\NodeInterface;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\TerminateEvent;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * Records researcher page views for the AI discovery feed.
 */
class ActivityEventSubscriber implements EventSubscriberInterface {

  public function __construct(
    private readonly AccountProxyInterface $currentUser,
    private readonly RouteMatchInterface $routeMatch,
    private readonly ConfigFactoryInterface $configFactory,
    private readonly Connection $database,
    private readonly TimeInterface $time,
  ) {}

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents(): array {
    return [KernelEvents::TERMINATE => 'onTerminate'];
  }

  /**
   * Records a page view when a researcher views an enabled-bundle node.
   *
   * @param \Symfony\Component\HttpKernel\Event\TerminateEvent $event
   *   The terminate event.
   */
  public function onTerminate(TerminateEvent $event): void {
    if ($this->currentUser->isAnonymous()) {
      return;
    }
    $node = $this->routeMatch->getParameter('node');
    if (!$node instanceof NodeInterface) {
      return;
    }
    $config = $this->configFactory->get('pece_ai.settings');
    $enabledBundles = $config->get('enabled_bundles') ?? [];
    $key = $node->getEntityTypeId() . ':' . $node->bundle();
    if (!in_array($key, $enabledBundles, TRUE)) {
      return;
    }
    $exists = $this->database->select('pece_ai_activity', 'a')
      ->condition('a.uid', (int) $this->currentUser->id())
      ->condition('a.entity_type', $node->getEntityTypeId())
      ->condition('a.entity_id', (int) $node->id())
      ->condition('a.timestamp', $this->time->getRequestTime() - 3600, '>=')
      ->countQuery()->execute()->fetchField();
    if ($exists) {
      return;
    }
    $weights = $config->get('activity_weights') ?? [];
    $this->database->insert('pece_ai_activity')
      ->fields([
        'uid' => (int) $this->currentUser->id(),
        'entity_type' => $node->getEntityTypeId(),
        'entity_id' => (int) $node->id(),
        'weight' => (int) ($weights['page_view'] ?? 1),
        'timestamp' => $this->time->getRequestTime(),
      ])
      ->execute();
    Cache::invalidateTags(['pece_ai_activity:' . $this->currentUser->id()]);
  }

}
