@javascript @ai
Feature: Writing Companion suggests related content while drafting

  As a researcher drafting new content,
  I want to find conceptually related content while I write,
  so that I can reference and link relevant existing work.

  Background:
    Given there is existing content seeded with vectors in Qdrant

  Scenario: Researcher finds related content while drafting an annotation
    Given I am logged in as a researcher with group membership
    When I go to create a new annotation
    And I advance to annotation step 2
    And I fill in "Title" with "Coastal flooding patterns"
    And I fill in "Body" with "Observations on tidal changes near the port"
    And I click "Find related content"
    Then I should see the element "#pece-ai-suggestions"
    And the element "#pece-ai-suggestions" should not contain "Could not load suggestions"
    And the element "#pece-ai-suggestions" should not contain "Add a title or some text"

  Scenario: Researcher finds related content while drafting a PECE Essay
    Given I am logged in as a researcher with group membership
    When I go to create a new "PECE Essay"
    And I fill in "Title" with "Seasonal knowledge systems"
    And I fill in "Body" with "How fishing communities adapt their practices to seasonal change"
    And I click "Find related content"
    Then I should see the element "#pece-ai-suggestions"
    And the element "#pece-ai-suggestions" should not contain "Could not load suggestions"
    And the element "#pece-ai-suggestions" should not contain "Add a title or some text"
