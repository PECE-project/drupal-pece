<?php

/**
 * @file
 * Contains FeedsPreviewSource.
 */

/**
 * FeedsPreviewSource overrides FeedsSource to be able to save
 * config entered in the FeedsPreview form, but at the same time
 * prevent the previewed items from being imported automatically.
 */
class FeedsPreviewSource extends FeedsSource {
  /**
   * Overrides FeedsSource::instance().
   *
   * Provides a FeedsPreviewSource instance instead.
   *
   * @return FeedsPreviewSource
   *   An instance of this class.
   */
  public static function instance($importer_id, $feed_nid = 0) {
    $class = 'FeedsPreviewSource';
    static $instances = array();
    if (!isset($instances[$class][$importer_id][$feed_nid])) {
      $instances[$class][$importer_id][$feed_nid] = new $class($importer_id, $feed_nid);
    }
    return $instances[$class][$importer_id][$feed_nid];
  }

  /**
   * Overrides FeedsSource::save().
   *
   * Saves records to feedspreview_source table instead.
   */
  public function save() {
    // Alert implementers of FeedsSourceInterface to the fact that we're saving.
    foreach ($this->importer->plugin_types as $type) {
      $this->importer->$type->sourceSave($this);
    }
    $config = $this->getConfig();

    // Store the source property of the fetcher in a separate column so that we
    // can do fast lookups on it.
    $source = '';
    if (isset($config[get_class($this->importer->fetcher)]['source'])) {
      $source = $config[get_class($this->importer->fetcher)]['source'];
    }
    $object = array(
      'id' => $this->id,
      'imported' => $this->imported,
      'config' => $config,
      'source' => $source,
      'state' => isset($this->state) ? $this->state : FALSE,
      'fetcher_result' => isset($this->fetcher_result) ? $this->fetcher_result : FALSE,
    );
    if (db_query_range("SELECT 1 FROM {feedspreview_source} WHERE id = :id", 0, 1, array(':id' => $this->id))->fetchField()) {
      drupal_write_record('feedspreview_source', $object, array('id'));
    }
    else {
      drupal_write_record('feedspreview_source', $object);
    }
  }

  /**
   * Overrides FeedsSource::load().
   *
   * Loads records from feedspreview_source table instead.
   */
  public function load() {
    if ($record = db_query("SELECT imported, config, state, fetcher_result FROM {feedspreview_source} WHERE id = :id", array(':id' => $this->id))->fetchObject()) {
      // While FeedsSource cannot be exported, we still use CTool's export.inc
      // export definitions.
      ctools_include('export');
      $this->export_type = EXPORT_IN_DATABASE;
      $this->imported = $record->imported;
      $this->config = unserialize($record->config);
      if (!empty($record->state)) {
        $this->state = unserialize($record->state);
      }
      if (!is_array($this->state)) {
        $this->state = array();
      }
      if (!empty($record->fetcher_result)) {
        $this->fetcher_result = unserialize($record->fetcher_result);
      }
    }
  }

  /**
   * Overrides FeedsSource::delete().
   *
   * Delete configuration from feedspreview_source instead.
   */
  public function delete() {
    // Alert implementers of FeedsSourceInterface to the fact that we're
    // deleting.
    foreach ($this->importer->plugin_types as $type) {
      $this->importer->$type->sourceDelete($this);
    }
    db_delete('feedspreview_source')
      ->condition('id', $this->id)
      ->execute();
  }
}
