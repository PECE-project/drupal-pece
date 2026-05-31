# PECE AI — Discovery Feed (Track C)

**Date:** 2026-05-31
**Status:** Approved
**Track:** C (Session-aware personalized feed)
**Depends on:** Track A + D (`pece_ai` module, `SimilarityService`, `EmbeddingService`)
**Next track:** None planned

---

## Overview

A "Suggested for You" block placed on the researcher's dashboard alongside existing content tabs. It observes what the researcher has been viewing and interacting with (passive browsing + active engagement), blends those signals into a weighted-average vector, and queries Qdrant for the most conceptually relevant content the researcher has not yet seen.

**AI Compute:** Same hybrid model as Tracks A and B — Qdrant vector search, Ollama embeddings already indexed. No new external services. One Qdrant query per dashboard load.

---

## Architecture

```
Node view / Entity save
  → ActivityEventSubscriber
    → INSERT into pece_ai_activity (uid, entity_type, entity_id, weight, timestamp)

Dashboard load
  → DiscoveryFeedBlock::build()
    → ActivityFeedService::getFeedForUser($uid)
      → SELECT last N distinct entities (by weight × recency)
      → SimilarityService::getVector() for each seed
      → Compute weighted-average vector (unit-normalized)
      → SimilarityService::findSimilarByVector(blended, feed_limit, groupIds)
      → Exclude entities already in user's activity
      → Render via pece_ai_related_content template
```

One Qdrant query total per dashboard load — seed vectors are blended before querying. Same approach embedding models use for user taste profiles.

---

## Activity Tracking

### Database table `pece_ai_activity`

Defined in `pece_ai.install` via `hook_schema()`:

```sql
pece_ai_activity (
  id           INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  uid          INT UNSIGNED NOT NULL,
  entity_type  VARCHAR(32) NOT NULL,
  entity_id    INT UNSIGNED NOT NULL,
  weight       TINYINT UNSIGNED NOT NULL DEFAULT 1,
  timestamp    INT UNSIGNED NOT NULL,
  INDEX idx_uid_timestamp (uid, timestamp),
  INDEX idx_uid_entity (uid, entity_type, entity_id)
)
```

No entity API — raw schema for fast zero-overhead writes on every page view.

### Signal weights

| Event | Weight |
|---|---|
| Node page view (enabled bundle) | 1 |
| Enabled-bundle entity saved by current user | 3 |
| Annotation created | 5 |

### `ActivityEventSubscriber`

**Page view tracking** via `KernelEvents::TERMINATE` (post-response, non-blocking):
- Checks current route is `entity.node.canonical`
- Checks entity bundle is in `enabled_bundles` config
- Skips anonymous users
- Inserts row with weight 1

**Interaction tracking** via `hook_entity_insert()` / `hook_entity_update()` in `pece_ai.module`:
- Annotation insert → weight 5
- Any enabled-bundle entity saved by authenticated current user → weight 3

### Cron pruning

`hook_cron()` deletes rows older than `activity_retention` days (default 90) per user. Keeps the table bounded without manual maintenance.

---

## ActivityFeedService

Single public method:

```php
public function getFeedForUser(int $uid): array
```

Algorithm:

1. Query `pece_ai_activity` for the last `$activity_limit` distinct `(entity_type, entity_id)` pairs for `$uid`, summing weights, ordered by most recent timestamp
2. For each seed entity → `SimilarityService::getVector()` (skip if NULL — not yet indexed)
3. Compute weighted-average vector across all seed vectors, normalize to unit length
4. Read current user's `field_groups_with_view_access` for group scope (same pattern as `WritingCompanionCallback`)
5. Call `SimilarityService::findSimilarByVector($blended, $feed_limit, $groupIds)`
6. Filter out `entity_id` values already present in the user's activity (no re-surfacing seen content)
7. Load entities, check `$entity->access('view')`, return `[{entity, score}]`

**Empty state:** If `$uid` has no activity rows, or all seed vectors are NULL, return `[]` — the block renders an onboarding message.

---

## DiscoveryFeedBlock

`@Block(id = "pece_ai_discovery_feed")`, placed in the `two_e` region of the `pece` dashboard via `hook_install()`.

**`build()` logic:**
- Get `$uid` from `currentUser()`; return `[]` if anonymous
- Call `ActivityFeedService::getFeedForUser($uid)`
- If empty → render "Start exploring content to get personalized suggestions."
- If results → render via `pece_ai_related_content` theme hook (same template as sidebar block and Writing Companion — Bulma panel, score badges)

**Cache:**
```php
'#cache' => [
  'tags' => ['user:' . $uid, 'node_list', 'pece_ai_activity:' . $uid],
  'contexts' => ['user'],
  'max-age' => 3600,
]
```

The custom cache tag `pece_ai_activity:$uid` is invalidated by `ActivityEventSubscriber` after each write, ensuring the feed refreshes when the researcher visits new content.

---

## New Components

| File | Action | Purpose |
|------|--------|---------|
| `pece_ai.install` | Modify | Add `hook_schema()` for `pece_ai_activity`, `hook_post_update_place_discovery_feed_block()` for block placement on existing installs, `hook_cron()` for pruning |
| `src/Service/ActivityFeedService.php` | Create | Vector blending + feed generation |
| `src/EventSubscriber/ActivityEventSubscriber.php` | Create | Page view tracking via `KernelEvents::TERMINATE` |
| `src/Plugin/Block/DiscoveryFeedBlock.php` | Create | Dashboard block plugin |
| `pece_ai.module` | Modify | Add interaction-weight hooks (`hook_entity_insert`, `hook_entity_update`) for annotation/essay signals |
| `pece_ai.services.yml` | Modify | Register `pece_ai.activity_feed_service` and `pece_ai.activity_event_subscriber` |
| `config/install/pece_ai.settings.yml` | Modify | Add `activity_limit`, `feed_limit`, `activity_retention`, `activity_weights` |
| `config/schema/pece_ai.schema.yml` | Modify | Add schema for new config keys |

---

## Configuration

New keys added to `pece_ai.settings.yml`:

```yaml
activity_limit: 20
feed_limit: 5
activity_retention: 90
activity_weights:
  page_view: 1
  entity_save: 3
  annotation_create: 5
```

---

## Testing

### Unit tests — `ActivityFeedServiceTest`

1. Weighted-average vector is computed correctly from seed vectors and weights
2. Entities already in user activity are excluded from returned results
3. Empty activity returns empty array (no Qdrant call made)
4. NULL vectors (unindexed entities) are skipped without error

### Kernel tests — `ActivityEventSubscriberTest`

1. Visiting an enabled-bundle node inserts a row with weight 1
2. Anonymous user visits do not insert rows
3. Non-enabled-bundle node visits do not insert rows

### Kernel tests — `DiscoveryFeedBlockTest`

1. Block renders feed items when user has activity and vectors exist
2. Block renders onboarding message when user has no activity
3. Block returns empty array for anonymous users

---

## Edge States

| Condition | Behaviour |
|---|---|
| New researcher (no activity) | "Start exploring content to get personalized suggestions." |
| Activity exists but no vectors indexed yet | Same empty state — vectors pending cron |
| Qdrant unavailable | Block absent silently — consistent with Track A |
| All seeds produce NULL vectors | Empty state — no Qdrant call |
| feed_limit = 0 | Block hidden |

---

## Out of Scope (this spec)

- Platform-wide toggle (group-scoped only for MVP, same default as Tracks A + B)
- Explicit bookmarks / saved interests (B signal — deferred)
- Frequency weighting (same entity viewed 10× vs 1× — deferred)
- `/discover` page surface (noted as future Track C extension)
- Activity export or user-visible history
