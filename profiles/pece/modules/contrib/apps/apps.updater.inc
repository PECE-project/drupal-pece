<?php
/**
 *  @file
 *  Provides the LibraryUpdater class.
 */

class LibraryUpdater extends Updater implements DrupalUpdaterInterface {
  public function getInstallDirectory() {
     return DRUPAL_ROOT . "/sites/all/libraries";
  }

  public function isInstalled() {
    return is_dir(DRUPAL_ROOT . "/sites/all/libraries/{$this->name}");
  }

  public static function canUpdateDirectory($directory) {
    if ($info = file_scan_directory($directory, '/.*\.info$/')) {
      // Allow apps.info as it contains our app information.
      foreach ($info as $file_path => $file_info) {
        if ($file_info->filename != APPS_APP_INFO) {
          return FALSE;
        }
      }
    }
    return TRUE;
  }

  public static function canUpdate($project_name) {
    return is_dir(DRUPAL_ROOT . "/sites/all/libraries/$project_name");
  }
  public function __construct($source) {
    $this->source = $source;
    $this->name = self::getProjectName($source);
    $this->title = self::getProjectName($source);
  }
}

