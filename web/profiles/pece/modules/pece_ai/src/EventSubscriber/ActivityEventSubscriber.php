<?php

namespace Drupal\pece_ai\EventSubscriber;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\Component\Datetime\TimeInterface;
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
    if (!$node) {
      return;
    }
    $config = $this->configFactory->get('pece_ai.settings');
    $enabledBundles = $config->get('enabled_bundles') ?? [];
    $key = $node->getEntityTypeId() . ':' . $node->bundle();
    if (!in_array($key, $enabledBundles, TRUE)) {
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
  }

}
