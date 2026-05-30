AI Features
===========

PECE includes a semantic AI layer that helps researchers discover related
content as they browse the platform. This page covers both the researcher-
facing features and the administrator setup required to enable them.

---

Related Content Sidebar
-----------------------

### What is it?

When viewing an artifact, essay, annotation, or memo, a **Related Content**
sidebar displays up to five pieces of content that are conceptually similar
to the current page. Similarity is computed using vector embeddings —
mathematical representations of meaning — so results reflect conceptual
proximity rather than keyword overlap.

### Group scope and platform-wide search

By default the sidebar shows results scoped to the researcher's current
Group. A **Platform-wide** toggle removes the group filter and searches
across all content the researcher has access to.

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
└─────────────────────────────────────┘
```

Match percentages are cosine similarity scores converted to percentages.
They indicate how conceptually close the related item is to the page you
are viewing.

### Pending state

When content is saved for the first time, the embedding is computed
asynchronously by Drupal's cron queue. Until the embedding is ready, the
sidebar shows **"Related content is being indexed…"** instead of results.
Refresh the page after the next cron run to see results.

### Supported content types

The sidebar is active on the following content types:

- PDF, Image, Video, Audio, Text, Website, and Bundle Artifacts
- Field Sites
- PECE Essays, Photo Essays, and Timeline Essays
- Annotations
- Memos

---

Administrator Setup
-------------------

The AI features require two additional services: **Qdrant** (vector
database) and **Ollama** (local embedding model). Both run as Docker
containers and require no GPU.

### Local development (DDEV)

DDEV configuration for both services is included in
`.ddev/docker-compose.ai.yaml`. Start them with your normal DDEV startup:

```bash
ddev start
```

On first start, Ollama automatically pulls the `nomic-embed-text` model
(~270 MB). Subsequent starts use the cached volume. Both services are
reachable from PHP at `http://qdrant:6333` and `http://ollama:11434`.

### Production

Add the same two containers to your Docker Compose stack. No changes to
the MariaDB or Drupal containers are required.

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
      "ollama serve & sleep 15 && ollama pull nomic-embed-text && wait"]

volumes:
  qdrant_storage:
  ollama_models:
```

Update `pece_ai.settings.yml` (or override via `$config` in
`settings.php`) so `qdrant_url` and `embedding_url` point to your
production hostnames.

### First-time setup

After starting the services, run the setup Drush command to create the
Qdrant collection and then backfill all existing content:

```bash
drush pece-ai:setup
drush pece-ai:backfill
```

`pece-ai:setup` creates the `pece_entities` collection in Qdrant with
768-dimensional cosine vectors. `pece-ai:backfill` queues every existing
artifact, essay, annotation, and memo for embedding. The queue is
processed by cron; run `drush cron` to process it immediately.

### Configuration

Settings are stored in `pece_ai.settings` and can be overridden in
`settings.php`:

| Key | Default | Description |
|-----|---------|-------------|
| `qdrant_url` | `http://qdrant:6333` | Qdrant service URL |
| `embedding_url` | `http://ollama:11434` | Ollama service URL |
| `embedding_model` | `nomic-embed-text` | Model name passed to Ollama |
| `sidebar_limit` | `5` | Maximum results shown in the sidebar |
| `enabled_bundles` | (13 bundles) | Content types included in indexing |

Example override in `settings.php`:

```php
$config['pece_ai.settings']['qdrant_url'] = 'http://qdrant.internal:6333';
$config['pece_ai.settings']['sidebar_limit'] = 8;
```

---

Troubleshooting
---------------

### Sidebar does not appear

- Confirm the `pece_ai` module is enabled: `drush pme pece_ai`
- Check that the block is placed in the sidebar region for node view pages
  via **Structure → Block layout**
- Verify Qdrant and Ollama are running and reachable from the web container

### "Related content is being indexed…" never goes away

- Run `drush cron` (or `ddev drush cron` locally) to process the queue
- Check for queue errors: `drush queue-list` and `drush queue-run pece_ai_embed`
- Check PHP logs for HTTP errors reaching `http://ollama:11434`

### No results after backfill

- Confirm `pece-ai:setup` was run and the `pece_entities` collection exists
  in Qdrant (visit `http://qdrant:6333/dashboard` in a browser)
- Confirm `pece-ai:backfill` completed and the queue was processed
- Check that content has body text — entities with no extractable text are
  excluded from indexing

### Qdrant unreachable in production

The sidebar fails silently when Qdrant is unavailable: the block is
absent from the page and no error is shown to researchers. Check the
Qdrant container health and network configuration.
