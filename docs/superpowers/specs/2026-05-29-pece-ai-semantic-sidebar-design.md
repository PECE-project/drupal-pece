# PECE AI — Semantic Sidebar (Track A + D)

**Date:** 2026-05-29  
**Status:** Approved  
**Tracks covered:** A (platform-wide browsing), D (group-scoped discovery)  
**Next track:** B (Writing Companion — annotation/essay form integration)

---

## Overview

A "Related Content" sidebar that appears on artifact, essay, annotation, and memo view pages. It uses vector similarity to surface the five most conceptually related pieces of content. Results are scoped to the researcher's current Group by default (Track D), with an optional toggle to search platform-wide (Track A).

**AI Compute model:** Hybrid. Embeddings are computed locally using a self-hosted open-source model (no GPU required). No external LLM API is called — the sidebar is entirely self-contained. LLM-heavy features (summarization, drafting assistance) are reserved for future tracks and only triggered by explicit researcher action.

---

## Architecture

Three layers, cleanly separated:

```
Content save → [Drupal Queue] → [EmbedEntityWorker] → [EmbeddingService] → [Qdrant]
                                                                                ↑
Content view → [RelatedContentBlock] → [SimilarityService] ────────────────────┘
```

**Layer 1 — Embedding Pipeline (async, batch)**  
When a researcher saves an artifact, essay, annotation, or memo, Drupal queues the entity. A cron-driven queue worker extracts the text, calls the embedding service, and upserts the resulting vector into Qdrant. A one-time backfill command covers existing content on first deploy.

**Layer 2 — Vector Store (Qdrant)**  
Qdrant is a purpose-built vector database running as a single Docker container (~50 MB image, CPU-only). Each point stores a 768-dim vector plus metadata payload: `entity_type`, `entity_id`, `bundle`, `group_ids[]`. Payload filtering enables Group-scoped queries without a second collection or system.

PECE uses MariaDB 11.4, which has no native vector support. Qdrant fills this gap without modifying the existing database setup.

**Layer 3 — Drupal Integration (`pece_ai` module)**  
A Block plugin renders the sidebar. On page load it queries Qdrant via HTTP with the current entity's stored vector, applies an optional group filter, and renders the top-5 results using existing entity view modes.

---

## Multi-Track Progression

All four tracks share this infrastructure. Only the query parameters and trigger surface change:

| Track | Change from baseline |
|---|---|
| A — Browsing, platform-wide | Remove `group_ids` filter from Qdrant query |
| D — Group-scoped (MVP) | Add `group_ids` payload filter — built in from day one |
| B — Writing Companion (Phase 2) | Same Qdrant query called via AJAX from annotation/essay form |
| C — Session-aware feed (Phase 3) | Batch-query recent entity IDs → blend scores into Discovery feed |

---

## Drupal Module: `pece_ai`

**Location:** `web/profiles/pece/modules/pece_ai/`

```
pece_ai/
├── src/
│   ├── Plugin/
│   │   ├── Block/RelatedContentBlock.php
│   │   └── QueueWorker/EmbedEntityWorker.php
│   ├── Service/
│   │   ├── EmbeddingService.php
│   │   └── SimilarityService.php
│   └── EventSubscriber/EntityEmbedSubscriber.php
├── config/install/pece_ai.settings.yml
└── templates/pece-ai-related-content.html.twig
```

**`EntityEmbedSubscriber`** — listens to `hook_entity_insert` / `hook_entity_update` for configured bundles, queues `{entity_type, entity_id}` into the `pece_ai_embed` queue.

**`EmbedEntityWorker`** (QueueWorker plugin) — extracts text from entity fields, calls `EmbeddingService`, upserts vector to Qdrant with payload `{entity_type, entity_id, bundle, group_ids[]}`. The `group_ids` array is populated from the entity's `field_groups` reference field (taxonomy term IDs). Entities with no group assignment are stored with an empty array and appear only in platform-wide queries.

**`EmbeddingService`** — HTTP client wrapper around the Ollama embeddings endpoint. Responsible for text extraction per bundle (title + body fields, configurable in settings).

**`SimilarityService`** — HTTP client wrapper around the Qdrant search endpoint. Accepts an entity, limit, and optional group filter. Returns `[{entity_type, entity_id, score}]`.

**`RelatedContentBlock`** — Drupal Block plugin. Calls `SimilarityService`, loads entities via `entity_type.manager`, renders with `teaser` view mode. Outputs pending state if embedding not yet computed. Fails silently if Qdrant is unavailable.

**`pece_ai.settings.yml`:**
```yaml
qdrant_url: 'http://qdrant:6333'
embedding_url: 'http://ollama:11434'
embedding_model: 'nomic-embed-text'
sidebar_limit: 5
enabled_bundles:
  - node:pece_artifact_pdf
  - node:pece_artifact_image
  - node:pece_artifact_video
  - node:pece_artifact_audio
  - node:pece_artifact_text
  - node:pece_artifact_website
  - node:pece_artifact_fieldsite
  - node:pece_artifact_bundle
  - node:pece_essay
  - node:pece_photo_essay
  - node:pece_timeline_essay
  - node:pece_annotation
  - node:pece_memo
```

---

## Embedding Service

**Model:** `nomic-embed-text` via Ollama  
**Dimensions:** 768  
**Distance metric:** Cosine (angle-based, length-invariant — a short annotation and a long essay are comparable)  
**RAM:** ~270 MB at runtime  
**GPU:** Not required  

**Embedding request:**
```
POST http://ollama:11434/api/embeddings
{"model": "nomic-embed-text", "prompt": "<title>\n\n<body text>"}
→ {"embedding": [0.023, -0.14, ...]}
```

**Qdrant collection setup (run once):**
```json
PUT /collections/pece_entities
{
  "vectors": { "size": 768, "distance": "Cosine" },
  "payload_schema": {
    "entity_type": "keyword",
    "entity_id":   "integer",
    "bundle":      "keyword",
    "group_ids":   "keyword"
  }
}
```

---

## Infrastructure

**DDEV local — `.ddev/docker-compose.ai.yaml`:**
```yaml
services:
  qdrant:
    image: qdrant/qdrant:latest
    ports: ["6333:6333"]
    volumes: ["qdrant_storage:/qdrant/storage"]

  ollama:
    image: ollama/ollama:latest
    ports: ["11434:11434"]
    volumes: ["ollama_models:/root/.ollama"]
    entrypoint: ["/bin/sh", "-c",
      "ollama serve & sleep 5 && ollama pull nomic-embed-text && wait"]
```

First `ddev start` pulls `nomic-embed-text` (~270 MB). Subsequent starts use the cached volume. Both services are reachable from PHP as `http://qdrant:6333` and `http://ollama:11434`.

**Production:** Same two containers added to the existing Docker Compose stack. No changes to the MariaDB or Drupal containers.

**Cache:** Qdrant query results are cached in Drupal's render cache, tagged with the entity's cache tags. Entity update → cache invalidated → new embedding queued automatically.

---

## UI/UX

Block placed in the sidebar region on `node.view` for all enabled bundles.

```
┌─────────────────────────────────────┐
│ Related Content                     │
│ Showing within: Coastal Field Study │
│                    [Platform-wide ↗]│
├─────────────────────────────────────┤
│ ○ Fishermen's Accounts — July 2023  │
│   PDF Artifact · 94% match          │
│                                     │
│ ○ Notes on Tidal Calendars          │
│   Essay · 91% match                 │
│                                     │
│ ○ Interview with Port Authority     │
│   Annotation · 88% match            │
│                                     │
│ ○ Field Site: Ilha do Mel           │
│   Artifact · 85% match              │
│                                     │
│ ○ Seasonal Knowledge Systems        │
│   Memo · 83% match                  │
└─────────────────────────────────────┘
```

**Group scope toggle:** Defaults to current researcher's groups. Clicking "Platform-wide" removes the group filter and refreshes via AJAX. Toggle state persists in session.

**Match percentage:** Cosine similarity (0–1) converted to percentage display. Keeps the interface readable without exposing raw floats. Can be hidden via settings if it feels too technical.

**Edge states:**

| State | Behavior |
|---|---|
| Embedding pending | "Related content is being indexed…" — no blank block |
| Fewer than 5 results | Shows however many exist |
| Qdrant unavailable | Block absent silently — no error shown to researcher |
| Entity has no text | Excluded from embedding and from results |

**Theme:** Twig template using Bulma `panel` + `panel-block` components, consistent with existing peceful card patterns.

---

## Testing

All tests run within the existing PHPUnit Unit + Kernel CI job. No additional CI infrastructure required.

**Unit tests (mock all HTTP calls):**
- `EmbeddingService`: text extraction per bundle, correct prompt format, empty body handling
- `SimilarityService`: Qdrant response parsing, group filter construction, score-to-percentage conversion, graceful degradation on Qdrant error

**Kernel tests (real Drupal bootstrap, mocked external services):**
- `EntityEmbedSubscriber`: saving a configured entity creates a queue item
- `EmbedEntityWorker`: processes queue item, calls services with correct arguments
- `RelatedContentBlock`: renders expected output with mocked `SimilarityService`; renders pending state when embedding absent

Live Qdrant and Ollama calls are excluded from CI — they belong in a future integration/smoke test suite.

---

## Out of Scope (this spec)

- Summarization or drafting assistance (requires external LLM API, explicit user trigger)
- Session-aware personalized feed (Track C — Phase 3)
- Writing Companion form integration (Track B — Phase 2)
- Multimodal embeddings for image/audio artifacts (future)
- Fine-tuning the embedding model on PECE-specific corpus (future)
