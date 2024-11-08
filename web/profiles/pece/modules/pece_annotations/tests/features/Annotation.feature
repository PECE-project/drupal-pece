Feature: Home Page
  @api
  Scenario: Visit the home page
    Given I am logged in as a user with the "authenticated" role
    When I go to "/node/pece_annotation/step_1"
    Then I should see the heading "Step 1"
    And I should see the text "Select one Structured Analytic (Question Set) and Analytic (Question)"
