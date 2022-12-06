<?php

namespace Drupal\pece_oauth\EventSubscriber;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\FilterResponseEvent;
use Symfony\Component\HttpKernel\KernelEvents;

class AddXLoginAttemptEvent implements EventSubscriberInterface {

  public function AddXLoginAttempt(FilterResponseEvent $event) {
    $response = $event->getResponse();

    if ($event->getRequest()->getPathInfo() == '/oauth/token' && !$response->isSuccessful()) {
      \Drupal::flood()->register('user.failed_login_ip');

      // Get number Attempt
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

  public static function getSubscribedEvents() {
    $events[KernelEvents::RESPONSE][] = array('AddXLoginAttempt', -10);
    return $events;
  }
}
