<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\user\Entity\User;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpKernel\Event\TerminateEvent;
use Symfony\Component\HttpKernel\HttpKernelInterface;

/**
 * Tests the ActivityEventSubscriber.
 *
 * @group pece_ai
 */
class ActivityEventSubscriberTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter', 'pece_ai',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installSchema('node', ['node_access']);
    $this->installSchema('pece_ai', ['pece_ai_activity']);
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);
    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
  }

  /**
   * Dispatches a terminate event for the given node and user.
   */
  private function dispatchTerminate(mixed $node, int $uid): void {
    $routeMatch = $this->createMock(RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn($node);
    $this->container->set('current_route_match', $routeMatch);

    $account = User::load($uid);
    $this->container->get('current_user')->setAccount($account);

    $kernel = $this->createMock(HttpKernelInterface::class);
    $event = new TerminateEvent($kernel, Request::create('/'), new Response());
    $this->container->get('pece_ai.activity_event_subscriber')
      ->onTerminate($event);
  }

  /**
   * Tests that viewing an enabled-bundle node inserts a weight-1 row.
   */
  public function testPageViewInsertsActivityRow(): void {
    $user = User::create(['name' => 'researcher', 'status' => 1]);
    $user->save();
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Test', 'uid' => $user->id()]);
    $node->save();

    $this->dispatchTerminate($node, (int) $user->id());

    $count = \Drupal::database()
      ->select('pece_ai_activity', 'a')
      ->condition('a.uid', $user->id())
      ->condition('a.entity_id', $node->id())
      ->condition('a.weight', 1)
      ->countQuery()->execute()->fetchField();
    $this->assertEquals(1, $count);
  }

  /**
   * Tests that anonymous users do not insert activity rows.
   */
  public function testAnonymousUserSkipped(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Test', 'uid' => 1]);
    $node->save();

    $routeMatch = $this->createMock(RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn($node);
    $this->container->set('current_route_match', $routeMatch);
    // current_user remains anonymous (uid=0)
    $kernel = $this->createMock(HttpKernelInterface::class);
    $event = new TerminateEvent($kernel, Request::create('/'), new Response());
    $this->container->get('pece_ai.activity_event_subscriber')->onTerminate($event);

    $count = \Drupal::database()
      ->select('pece_ai_activity', 'a')
      ->countQuery()->execute()->fetchField();
    $this->assertEquals(0, $count);
  }

  /**
   * Tests that non-enabled-bundle nodes do not insert rows.
   */
  public function testDisabledBundleNodeSkipped(): void {
    $user = User::create(['name' => 'researcher2', 'status' => 1]);
    $user->save();
    NodeType::create(['type' => 'page', 'name' => 'Basic page'])->save();
    $node = Node::create(['type' => 'page', 'title' => 'A page', 'uid' => $user->id()]);
    $node->save();

    $this->dispatchTerminate($node, (int) $user->id());

    $count = \Drupal::database()
      ->select('pece_ai_activity', 'a')
      ->condition('a.uid', $user->id())
      ->countQuery()->execute()->fetchField();
    $this->assertEquals(0, $count);
  }

  /**
   * Tests that a non-entity node route parameter does not fatal or insert rows.
   */
  public function testStringNodeParameterSkipped(): void {
    $user = User::create(['name' => 'researcher3', 'status' => 1]);
    $user->save();
    $this->container->get('current_user')->setAccount($user);

    $routeMatch = $this->createMock(RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn('42');
    $this->container->set('current_route_match', $routeMatch);

    $kernel = $this->createMock(HttpKernelInterface::class);
    $event = new TerminateEvent($kernel, Request::create('/'), new Response());
    $this->container->get('pece_ai.activity_event_subscriber')->onTerminate($event);

    $count = \Drupal::database()
      ->select('pece_ai_activity', 'a')
      ->condition('a.uid', $user->id())
      ->countQuery()->execute()->fetchField();
    $this->assertEquals(0, $count);
  }

}
