<?php

namespace Drupal\Tests\graphql_people\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\user\Entity\User;
use Drupal\user\Entity\Role;

/**
 * Test CreateUser GraphQL DataProducer security.
 *
 * Verifies that the CreateUser DataProducer properly enforces authorization
 * and prevents anonymous users from creating accounts.
 *
 * @group graphql_people
 * @group nyx_graphql
 */
class CreateUserTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system',
    'user',
    'graphql',
    'graphql_people',
  ];

  /**
   * The CreateUser DataProducer plugin.
   *
   * @var \Drupal\graphql_people\Plugin\GraphQL\DataProducer\CreateUser
   */
  protected $createUserPlugin;

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    $this->installEntitySchema('user');
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['user', 'system']);

    // Create the DataProducer plugin.
    $plugin_manager = \Drupal::service('plugin.manager.graphql.data_producer');
    $this->createUserPlugin = $plugin_manager->createInstance('create_user');
  }

  /**
   * Test that anonymous users cannot create accounts.
   *
   * This test verifies the security fix that removed the dangerous
   * isAnonymous() authorization bypass.
   */
  public function testAnonymousUserCannotCreateAccount() {
    // Set current user to anonymous.
    $anonymous_user = User::getAnonymousUser();
    \Drupal::currentUser()->setAccount($anonymous_user);

    // Attempt to create a user.
    $user_data = [
      'name' => 'test_user_anonymous',
      'mail' => 'anonymous@example.com',
      'pass' => 'password123',
    ];

    $result = $this->createUserPlugin->resolve($user_data);

    // Should return NULL for unauthorized access.
    $this->assertNull($result, 'Anonymous user should not be able to create accounts');

    // Verify no user was created in the database.
    $users = \Drupal::entityTypeManager()
      ->getStorage('user')
      ->loadByProperties(['name' => 'test_user_anonymous']);
    $this->assertEmpty($users, 'No user should be created for anonymous request');
  }

  /**
   * Test that authenticated users without permission cannot create accounts.
   */
  public function testAuthenticatedUserWithoutPermissionCannotCreateAccount() {
    // Create an authenticated user without "administer users" permission.
    $regular_user = User::create([
      'name' => 'regular_user',
      'mail' => 'regular@example.com',
      'status' => 1,
    ]);
    $regular_user->save();

    \Drupal::currentUser()->setAccount($regular_user);

    // Attempt to create a user.
    $user_data = [
      'name' => 'test_user_unauthorized',
      'mail' => 'unauthorized@example.com',
      'pass' => 'password123',
    ];

    $result = $this->createUserPlugin->resolve($user_data);

    // Should return NULL for unauthorized access.
    $this->assertNull($result, 'Authenticated user without permission should not be able to create accounts');

    // Verify no user was created in the database.
    $users = \Drupal::entityTypeManager()
      ->getStorage('user')
      ->loadByProperties(['name' => 'test_user_unauthorized']);
    $this->assertEmpty($users, 'No user should be created for unauthorized request');
  }

  /**
   * Test that admin users can create accounts.
   *
   * This test verifies that the security fix did not break legitimate
   * admin functionality.
   */
  public function testAdminUserCanCreateAccount() {
    // Create an admin user with "administer users" permission.
    $admin_role = Role::create([
      'id' => 'test_admin',
      'label' => 'Test Admin',
    ]);
    $admin_role->grantPermission('administer users');
    $admin_role->save();

    $admin_user = User::create([
      'name' => 'admin_user',
      'mail' => 'admin@example.com',
      'status' => 1,
    ]);
    $admin_user->addRole('test_admin');
    $admin_user->save();

    \Drupal::currentUser()->setAccount($admin_user);

    // Attempt to create a user.
    $user_data = [
      'name' => 'test_user_authorized',
      'mail' => 'authorized@example.com',
      'pass' => 'password123',
    ];

    $result = $this->createUserPlugin->resolve($user_data);

    // Should return a User entity.
    $this->assertNotNull($result, 'Admin user should be able to create accounts');
    $this->assertInstanceOf(User::class, $result, 'Result should be a User entity');
    $this->assertEquals('test_user_authorized', $result->getAccountName(), 'Created user should have correct name');
    $this->assertEquals('authorized@example.com', $result->getEmail(), 'Created user should have correct email');

    // Verify user was created in the database.
    $users = \Drupal::entityTypeManager()
      ->getStorage('user')
      ->loadByProperties(['name' => 'test_user_authorized']);
    $this->assertNotEmpty($users, 'User should be created in database');
  }

  /**
   * Test that duplicate user creation is properly handled.
   */
  public function testDuplicateUserCreationHandling() {
    // Create an admin user.
    $admin_role = Role::create([
      'id' => 'test_admin_dup',
      'label' => 'Test Admin Dup',
    ]);
    $admin_role->grantPermission('administer users');
    $admin_role->save();

    $admin_user = User::create([
      'name' => 'admin_user_dup',
      'mail' => 'admin_dup@example.com',
      'status' => 1,
    ]);
    $admin_user->addRole('test_admin_dup');
    $admin_user->save();

    \Drupal::currentUser()->setAccount($admin_user);

    // Create the first user.
    $user_data = [
      'name' => 'duplicate_test_user',
      'mail' => 'duplicate@example.com',
      'pass' => 'password123',
    ];

    $result1 = $this->createUserPlugin->resolve($user_data);
    $this->assertNotNull($result1, 'First user creation should succeed');

    // Attempt to create duplicate user.
    $this->expectException(\Exception::class);
    $this->expectExceptionMessage('User already registered');

    $result2 = $this->createUserPlugin->resolve($user_data);
  }

}
