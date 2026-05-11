<?php

namespace Drupal\Tests\graphql_people\Functional;

use Drupal\Tests\BrowserTestBase;
use Drupal\user\Entity\Role;
use Drupal\user\Entity\User;

/**
 * Test CreateUser GraphQL endpoint security.
 *
 * Functional tests for the createPeople GraphQL mutation to verify that
 * authorization is properly enforced at the API level.
 *
 * @group graphql_people
 * @group nyx_graphql
 */
class CreateUserGraphQLTest extends BrowserTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'graphql',
    'graphql_people',
    'user',
  ];

  /**
   * {@inheritdoc}
   */
  protected $defaultTheme = 'stark';

  /**
   * The GraphQL endpoint URL.
   *
   * @var string
   */
  protected $graphqlEndpoint;

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    // Typically GraphQL endpoints are at /graphql but this may vary.
    // Adjust based on your actual GraphQL configuration.
    $this->graphqlEndpoint = '/graphql';
  }

  /**
   * Test that anonymous users cannot create accounts via GraphQL.
   *
   * This is the primary security test verifying the fix for the
   * dangerous isAnonymous() authorization bypass.
   */
  public function testAnonymousCannotCreateUserViaGraphQL() {
    // Ensure user is logged out (anonymous).
    $this->drupalLogout();

    // Attempt to create a user via GraphQL.
    $query = <<<'GQL'
mutation {
  createPeople(data: {
    name: "anonymous_created_user"
    mail: "anonymous@example.com"
    pass: "Password123!"
  }) {
    uid
    name
    mail
  }
}
GQL;

    $response = $this->executeGraphQLQuery($query);

    // The response should either be NULL or contain an authorization error.
    // The important thing is that no user should be created.
    if (isset($response['data']['createPeople'])) {
      $this->assertNull(
        $response['data']['createPeople'],
        'CreatePeople should return NULL for anonymous users'
      );
    }

    // Verify no user was created in the database.
    $users = \Drupal::entityTypeManager()
      ->getStorage('user')
      ->loadByProperties(['name' => 'anonymous_created_user']);
    $this->assertEmpty(
      $users,
      'Anonymous user should not be able to create accounts via GraphQL'
    );
  }

  /**
   * Test that authenticated users without permission cannot create accounts.
   */
  public function testRegularUserCannotCreateUserViaGraphQL() {
    // Create and login as a regular user without admin permissions.
    $regular_user = $this->drupalCreateUser();
    $this->drupalLogin($regular_user);

    $query = <<<'GQL'
mutation {
  createPeople(data: {
    name: "unauthorized_created_user"
    mail: "unauthorized@example.com"
    pass: "Password123!"
  }) {
    uid
    name
    mail
  }
}
GQL;

    $response = $this->executeGraphQLQuery($query);

    // Should return NULL for unauthorized users.
    if (isset($response['data']['createPeople'])) {
      $this->assertNull(
        $response['data']['createPeople'],
        'CreatePeople should return NULL for users without admin permission'
      );
    }

    // Verify no user was created.
    $users = \Drupal::entityTypeManager()
      ->getStorage('user')
      ->loadByProperties(['name' => 'unauthorized_created_user']);
    $this->assertEmpty(
      $users,
      'Regular user should not be able to create accounts via GraphQL'
    );
  }

  /**
   * Test that admin users can create accounts via GraphQL.
   *
   * This verifies that the security fix did not break legitimate functionality.
   */
  public function testAdminCanCreateUserViaGraphQL() {
    // Create and login as an admin user.
    $admin_user = $this->drupalCreateUser(['administer users']);
    $this->drupalLogin($admin_user);

    $query = <<<'GQL'
mutation {
  createPeople(data: {
    name: "admin_created_user"
    mail: "admin_created@example.com"
    pass: "Password123!"
  }) {
    uid
    name
    mail
  }
}
GQL;

    $response = $this->executeGraphQLQuery($query);

    // Should successfully create the user.
    $this->assertNotNull(
      $response['data']['createPeople'] ?? NULL,
      'Admin user should be able to create accounts via GraphQL'
    );

    $created_user = $response['data']['createPeople'];
    $this->assertNotEmpty($created_user['uid'], 'Created user should have a uid');
    $this->assertEquals('admin_created_user', $created_user['name'], 'Created user should have correct name');
    $this->assertEquals('admin_created@example.com', $created_user['mail'], 'Created user should have correct email');

    // Verify user exists in database.
    $users = \Drupal::entityTypeManager()
      ->getStorage('user')
      ->loadByProperties(['name' => 'admin_created_user']);
    $this->assertNotEmpty(
      $users,
      'User should be created in database when requested by admin'
    );
  }

  /**
   * Execute a GraphQL query.
   *
   * @param string $query
   *   The GraphQL query to execute.
   *
   * @return array
   *   The decoded JSON response.
   */
  protected function executeGraphQLQuery($query) {
    $response = $this->drupalPost(
      $this->graphqlEndpoint,
      json_encode(['query' => $query]),
      [
        'Content-Type' => 'application/json',
      ]
    );

    return json_decode($response, TRUE);
  }

}
