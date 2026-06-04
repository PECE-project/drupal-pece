<?php

namespace Drupal\Tests\nyx_recaptcha\Kernel;

use Drupal\KernelTests\KernelTestBase;

/**
 * Verifies the nyx_recaptcha route is registered correctly.
 *
 * @group nyx_recaptcha
 */
class RecaptchaRouteTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = ['system', 'user', 'nyx_recaptcha'];

  /**
   * Tests that the verify route is registered with the correct path.
   */
  public function testVerifyRoutePathIsRegistered(): void {
    $route = $this->container->get('router.route_provider')
      ->getRouteByName('nyx_recaptcha.settings');

    $this->assertEquals('/recaptcha/verify/{token}', $route->getPath());
  }

  /**
   * Tests that the verify route points to the correct controller.
   */
  public function testVerifyRouteControllerIsRecaptchaController(): void {
    $route = $this->container->get('router.route_provider')
      ->getRouteByName('nyx_recaptcha.settings');

    $this->assertStringContainsString('RecaptchaController::verify', $route->getDefault('_controller'));
  }

  /**
   * Tests that the route requires the access content permission.
   */
  public function testVerifyRouteRequiresAccessContentPermission(): void {
    $route = $this->container->get('router.route_provider')
      ->getRouteByName('nyx_recaptcha.settings');

    $this->assertEquals('access content', $route->getRequirement('_permission'));
  }

}
