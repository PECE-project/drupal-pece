# PECE AI — Writing Companion (Track B)

**Date:** 2026-05-30
**Status:** Approved
**Track:** B (Writing Companion — annotation/essay form integration)
**Depends on:** Track A + D (`pece_ai` module, `EmbeddingService`, `SimilarityService`)
**Next track:** C (Session-aware feed — Phase 3)

---

## Overview

A "Find related content" button that appears on the annotation (step 2) and essay drafting forms. When clicked, the companion fetches conceptually similar content from Qdrant — using the current title and body text as the query — and renders suggestions inline below the body field. No page reload. No live typing triggers. The researcher clicks when they want inspiration.

**AI Compute:** Same hybrid model as Track A — fresh embedding computed on demand via Ollama (`nomic-embed-text`), no external LLM API calls.

---

## Architecture

Track B extends the existing `pece_ai` module. No new module required. The existing `EmbeddingService`, `SimilarityService`, and Twig template are unchanged.

```
[Find related button click]
  → Drupal #ajax form callback (WritingCompanionCallback::suggest)
    → read title + body from FormState
    → EmbeddingService::embed(title + "\n\n" + strip_tags(body))
    → SimilarityService::findSimilar(vector, groupIds, limit=5)
    → AjaxResponse + ReplaceCommand → #pece-ai-suggestions div
```

### Group scope

Since the researcher may not have selected groups on the form yet (especially when creating new content), group scope is derived from the **current user's group memberships** (`field_groups_with_view_access` on the user entity), not from the form's group field. A "Platform-wide" checkbox next to the button overrides this to an unfiltered query — identical toggle concept to the view-page sidebar.

### Error states

| Condition | Behaviour |
|---|---|
| Title and body both empty | "Add a title or some text to find related content." |
| Ollama unavailable | "Could not load suggestions right now." (silent, no exception exposed) |
| Qdrant unavailable | "Could not load suggestions right now." (silent) |
| No results found | "No related content found yet." |

---

## Form Integration

Five forms receive the Writing Companion, all via `pece_ai_form_alter()` in `pece_ai.module`.

| Form ID | Notes |
|---|---|
| `node_pece_annotation_annotation_step_2_form` | Step 2 only — step 1 (artifact) and step 3 (permissions) untouched |
| `node_pece_essay_form` | Add form |
| `node_pece_essay_edit_form` | Edit form |
| `node_pece_photo_essay_form` | Add form |
| `node_pece_photo_essay_edit_form` | Edit form |
| `node_pece_timeline_essay_form` | Add form |
| `node_pece_timeline_essay_edit_form` | Edit form |

The button and results placeholder are injected below the `body` field using `#suffix` on the body field wrapper:

```
[ Title field                               ]
[ Body textarea                             ]
[ Find related content  □ Platform-wide     ]
┌────────────────────────────────────────────┐
│  (results appear here after click)        │
└────────────────────────────────────────────┘
[ ...rest of form... ]
```

The results div has id `pece-ai-suggestions` and is the AJAX `#wrapper` target.

---

## New Components

### `src/Ajax/WritingCompanionCallback.php`

Static class. One public method:

```php
public static function suggest(array &$form, FormStateInterface $form_state): AjaxResponse
```

Responsibilities:
1. Read `title` and `body` values from `$form_state`
2. Concatenate: `$title . "\n\n" . trim(html_entity_decode(strip_tags($body)))`
3. If combined text is empty, return `ReplaceCommand` with "Add a title or some text" message
4. Call `EmbeddingService::embed($text)` — wrap in try/catch, return error message on failure
5. Read `platform_wide` checkbox from form state; if unchecked, build `$groupIds` from current user's `field_groups_with_view_access`
6. Call `SimilarityService::findSimilar($vector, $groupIds, 5)`
7. Load each result entity, check `$entity->access('view')`
8. Render results using `pece_ai_related_content` theme hook
9. Return `AjaxResponse` with `ReplaceCommand('#pece-ai-suggestions', $rendered)`

Services injected via `\Drupal::service()` (static context — same pattern as `PeceAiCommands`).

### `pece_ai.module` additions

```php
function pece_ai_form_alter(array &$form, FormStateInterface $form_state, string $form_id): void {
  $targets = [
    'node_pece_annotation_annotation_step_2_form',
    'node_pece_essay_form',
    'node_pece_essay_edit_form',
    'node_pece_photo_essay_form',
    'node_pece_photo_essay_edit_form',
    'node_pece_timeline_essay_form',
    'node_pece_timeline_essay_edit_form',
  ];
  if (!in_array($form_id, $targets, TRUE)) {
    return;
  }
  // Inject button, checkbox, placeholder div below body field.
}
```

The `#ajax` definition on the button:

```php
'#ajax' => [
  'callback' => [WritingCompanionCallback::class, 'suggest'],
  'wrapper'  => 'pece-ai-suggestions',
  'effect'   => 'fade',
  'progress' => ['type' => 'throbber', 'message' => t('Finding related content…')],
],
```

### `pece_ai.libraries.yml`

One library — `pece_ai/writing_companion` — CSS only, applied via `#attached` in `pece_ai_form_alter`. Scopes Bulma `panel` classes within the form context to avoid conflicts with the page layout.

---

## Testing

### Unit tests — `WritingCompanionCallbackTest`

1. Empty form state → response contains "Add a title or some text"
2. `EmbeddingService` throws → response contains "Could not load suggestions"
3. Valid text → `EmbeddingService::embed()` called with `title + "\n\n" + body`
4. Results returned → `AjaxResponse` contains `ReplaceCommand` with rendered items

### Kernel tests — `WritingCompanionFormTest`

1. `pece_ai_form_alter` adds button and `#pece-ai-suggestions` div to annotation step 2
2. `pece_ai_form_alter` adds button and div to essay add form
3. `pece_ai_form_alter` adds button and div to essay edit form
4. `pece_ai_form_alter` adds button and div to photo essay add form
5. `pece_ai_form_alter` adds button and div to photo essay edit form
6. `pece_ai_form_alter` adds button and div to timeline essay add form
7. `pece_ai_form_alter` adds button and div to timeline essay edit form

### E2E — Behat (`features/pece_ai_writing_companion.feature`)

Tagged `@javascript @ai` — excluded from standard CI, requires Selenium/Chrome driver and running Qdrant + Ollama with seeded vectors.

```gherkin
@javascript @ai
Feature: Writing Companion suggests related content while drafting

  Background:
    Given there is existing content seeded with vectors in Qdrant

  Scenario: Researcher finds related content while drafting an annotation
    Given I am logged in as a researcher with group membership
    When I go to create a new annotation
    And I advance to annotation step 2
    And I fill in "Title" with "Coastal flooding patterns"
    And I fill in "Body" with "Observations on tidal changes near the port"
    And I click "Find related content"
    Then I should see the suggestions panel
    And the panel should not show an error message

  Scenario: Researcher finds related content while drafting an essay
    Given I am logged in as a researcher with group membership
    When I go to create a new PECE Essay
    And I fill in "Title" with "Seasonal knowledge systems"
    And I fill in "Body" with "How fishing communities adapt their practices to seasonal change"
    And I click "Find related content"
    Then I should see the suggestions panel
    And the panel should not show an error message
```

> **Note:** Behat `@javascript` scenarios require a Selenium or Chrome WebDriver configured in `behat.yml`. If not already set up, add a `selenium2` or `chrome` Mink session before running these scenarios.

---

## Out of Scope (this spec)

- Live/debounced suggestions as the researcher types
- Suggestions panel on step 1 or step 3 of the annotation form
- Multimodal input (images, audio)
- Saving a suggestion as a linked artifact from the form
- Track C (session-aware feed)
