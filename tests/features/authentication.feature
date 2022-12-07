Feature: User authentication
  In order to protect the integrity of the website
  As a product owner
  I want to make sure users with various roles can only access pages they are authorized to

  Scenario: Anonymous user can see the user login page
    Given I am not logged in
    When I visit "user"
    Then I should see the text "Log in"
    And I should see the text "Create new account"
    And I should see the text "Reset your password"
    And I should see the text "Username"
    And I should see the text "Password"
    But I should not see the text "Log out"
    And I should not see the text "View profile"

  Scenario Outline: Anonymous user can access public pages
    Given I am not logged in
    # By visiting the path an access check is done automatically.
    Then I visit "<path>"

    Examples:
      | path          |
      | user/login    |
      | user/password |
      | user/register |

  Scenario Outline: Anonymous user cannot access restricted pages
    Given I am not logged in
    When I go to "<path>"
    Then I should get an access denied error

    Examples:
      | path             |
      | admin            |
      | admin/appearance |
      | admin/config     |
      | admin/content    |
      | admin/people     |
      | admin/structure  |
      # To do: the 'node/' path should be disabled on most Drupal sites.
      # | node            |
      | node/add         |
      | user/1           |

  @api
  Scenario Outline: Authenticated user can access pages they are authorized to
    Given I am logged in as a user with the "authenticated" role
    Then I visit "<path>"

    Examples:
      | path |
      | user |

  @api
  Scenario Outline: Authenticated user cannot access site administration
    Given I am logged in as a user with the "authenticated" role
    When I go to "<path>"
    Then I should get an access denied error

    Examples:
      | path             |
      | admin            |
      | admin/appearance |
      | admin/config     |
      | admin/content    |
      | admin/people     |
      | admin/structure  |
      # To do: the 'node/' path should be disabled on most Drupal sites.
      # | node            |
      | node/add         |
      | user/1           |
