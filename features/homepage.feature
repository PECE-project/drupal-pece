Feature: Home Page
  Scenario: Visit the home page
    Given I am an anonymous user
    When I go to "/"
    Then I should see the link "Log in"

  Scenario: Visit the home page as a provider
    Given I am logged in as user "admin"
    When I go to "/"
    Then I should see the link "Log out"
    And I should see the link "My account"
    And I should see the link "Dashboard"
