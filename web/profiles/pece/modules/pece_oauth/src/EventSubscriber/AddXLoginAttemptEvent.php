<?php

namespace Drupal\pece_oauth\EventSubscriber;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\ResponseEvent;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * Adds X-Login-Attempt header to failed OAuth token responses.
 */
class AddXLoginAttemptEvent implements EventSubscriberInterface {

  /**
   * Adds X-Login-Attempt header on failed OAuth token requests.
   *
   * @param \Symfony\Component\HttpKernel\Event\ResponseEvent $event
   *   The response event.
   */
  public function addXLoginAttempt(ResponseEvent $event): void {
    $response = $event->getResponse();

    if ($event->getRequest()->getPathInfo() == '/oauth/token' && !$response->isSuccessful()) {
      \Drupal::flood()->register('user.failed_login_ip');

      // Get number Attempt.
      $number = \Drupal::database()->select('flood', 'f')
        ->condition('event', 'user.failed_login_ip')
        ->condition('identifier', $event->getRequest()->getClientIp())
        ->condition('timestamp', \Drupal::time()->getRequestTime() - 3600, '>')
        ->countQuery()
        ->execute()
        ->fetchField();
      $response->headers->set('X-Login-Attempt', $number);
    }
  }

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents(): array {
    $events[KernelEvents::RESPONSE][] = ['addXLoginAttempt', -10];
    return $events;
  }

}
