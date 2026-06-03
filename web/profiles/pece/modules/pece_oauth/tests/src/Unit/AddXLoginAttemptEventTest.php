<?php

namespace Drupal\Tests\pece_oauth\Unit;

use Drupal\pece_oauth\EventSubscriber\AddXLoginAttemptEvent;
use Drupal\Tests\UnitTestCase;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpKernel\Event\ResponseEvent;
use Symfony\Component\HttpKernel\HttpKernelInterface;
use Symfony\Component\HttpKernel\KernelEvents;

/**
 * @coversDefaultClass \Drupal\pece_oauth\EventSubscriber\AddXLoginAttemptEvent
 * @group pece_oauth
 */
class AddXLoginAttemptEventTest extends UnitTestCase {

  /**
   * @covers ::getSubscribedEvents
   */
  public function testSubscribesToResponseEvent(): void {
    $events = AddXLoginAttemptEvent::getSubscribedEvents();
    $this->assertArrayHasKey(KernelEvents::RESPONSE, $events);
  }

  /**
   * @covers ::getSubscribedEvents
   */
  public function testHandlerMethodIsAddXLoginAttempt(): void {
    $events = AddXLoginAttemptEvent::getSubscribedEvents();
    $this->assertEquals('AddXLoginAttempt', $events[KernelEvents::RESPONSE][0][0]);
  }

  /**
   * @covers ::AddXLoginAttempt
   */
  public function testNonOauthPathDoesNotModifyResponse(): void {
    $kernel = $this->createMock(HttpKernelInterface::class);
    $request = Request::create('/some/other/path');
    $response = new Response('', 401);

    $event = new ResponseEvent(
      $kernel,
      $request,
      HttpKernelInterface::MAIN_REQUEST,
      $response
    );

    $subscriber = new AddXLoginAttemptEvent();
    $subscriber->AddXLoginAttempt($event);

    $this->assertFalse($response->headers->has('X-Login-Attempt'));
  }

  /**
   * @covers ::AddXLoginAttempt
   */
  public function testSuccessfulOauthResponseDoesNotAddHeader(): void {
    $kernel = $this->createMock(HttpKernelInterface::class);
    $request = Request::create('/oauth/token');
    $response = new Response('', 200);

    $event = new ResponseEvent(
      $kernel,
      $request,
      HttpKernelInterface::MAIN_REQUEST,
      $response
    );

    $subscriber = new AddXLoginAttemptEvent();
    $subscriber->AddXLoginAttempt($event);

    $this->assertFalse($response->headers->has('X-Login-Attempt'));
  }

}
