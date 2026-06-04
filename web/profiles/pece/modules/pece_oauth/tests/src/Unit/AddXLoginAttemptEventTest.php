<?php

namespace Drupal\Tests\pece_oauth\Unit;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Component\Datetime\TimeInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Database\Query\SelectInterface;
use Drupal\Core\Flood\FloodInterface;
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
  public function testHandlerMethodName(): void {
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

  /**
   * Tests a failed /oauth/token request registers flood and sets the header.
   *
   * @covers ::AddXLoginAttempt
   */
  public function testFailedOauthRequestRegistersFloodAndSetsHeader(): void {
    $flood = $this->createMock(FloodInterface::class);
    $flood->expects($this->once())->method('register')->with('user.failed_login_ip');

    $countQuery = $this->createMock(SelectInterface::class);
    $countQuery->method('execute')->willReturn(
      new class {

        /**
         * Returns the mocked count.
         */
        public function fetchField() {
          return 3;
        }

      }
    );

    $select = $this->createMock(SelectInterface::class);
    $select->method('condition')->willReturnSelf();
    $select->method('countQuery')->willReturn($countQuery);

    $database = $this->createMock(Connection::class);
    $database->method('select')->willReturn($select);

    $time = $this->createMock(TimeInterface::class);
    $time->method('getRequestTime')->willReturn(1000000);

    $container = new ContainerBuilder();
    $container->set('flood', $flood);
    $container->set('database', $database);
    $container->set('datetime.time', $time);
    \Drupal::setContainer($container);

    $kernel = $this->createMock(HttpKernelInterface::class);
    $request = Request::create('/oauth/token');
    $response = new Response('', 401);

    $event = new ResponseEvent(
      $kernel,
      $request,
      HttpKernelInterface::MAIN_REQUEST,
      $response
    );

    $subscriber = new AddXLoginAttemptEvent();
    $subscriber->AddXLoginAttempt($event);

    $this->assertEquals('3', $response->headers->get('X-Login-Attempt'));
  }

}
