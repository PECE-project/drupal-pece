<?php

/**
 * @file
 * Functions to handle the SFTP backup destination.
 */

/**
 * A destination for sending database backups to an SFTP server.
 * @ingroup backup_migrate_destinations
 *
 * NOTE: This format cannot pass PAReview and still comply with Backup and
 * Migrate's own standards (re: camel-casing of class names).
 */
class BackupMigrateDestinationSFTP extends backup_migrate_destination_remote {
  public $supported_ops = array(
    'scheduled backup',
    'manual backup',
    'restore',
    'list files',
    'configure',
    'delete',
  );

  protected $sftp = NULL;
  protected $connection = NULL;

  /**
   * Save a local file to the remote server.
   */
  public function _save_file($file, $settings) {
    if (!$this->sftpConnect()) {
      return FALSE;
    }

    $source = $file->filepath();
    $filename = $file->filename();

    $sftp = $this->sftp;
    $path = $this->dest_url['path'];
    $stream = @fopen("ssh2.sftp://$sftp/$path/$filename", 'w');
    if (!$stream) {
      throw new Exception("Could not open remote stream.");
      return FALSE;
    }

    $data = file_get_contents($source);
    if (!$data) {
      throw new Exception("Could not open source file.");
      return FALSE;
    }

    if (@fwrite($stream, $data) === FALSE) {
      throw new Exception("Could not transfer file.");
      return FALSE;
    }

    @fclose($stream);
    return $file;
  }

  /**
   * Download a remote file to the local server.
   */
  public function load_file($file_id) {
    backup_migrate_include('files');
    $file = new backup_file(array('filename' => $file_id));

    if (!$this->sftpConnect()) {
      return FALSE;
    }

    $sftp = $this->sftp;
    $path = $this->dest_url['path'];
    $stream = @fopen("ssh2.sftp://$sftp/$path/$file_id", 'r');
    if (!$stream) {
      throw new Exception("Could not open file: $file_id");
      return FALSE;
    }

    $data = fread($stream, filesize("ssh2.sftp://$sftp/$path/$file_id"));
    if (!$data) {
      throw new Exception("Could not transfer file.");
      return FALSE;
    }

    file_put_contents($file->filepath(), $data);
    @fclose($stream);

    return $file;
  }

  /**
   * Delete a remote file.
   */
  public function _delete_file($file_id) {
    if (!$this->sftpConnect()) {
      return FALSE;
    }

    $sftp = $this->sftp;
    $path = $this->dest_url['path'];
    unlink("ssh2.sftp://$sftp/$path/$file_id");
  }

  /**
   * List the files in the remote server.
   */
  public function _list_files() {
    backup_migrate_include('files');

    $files = array();

    if (!$this->sftpConnect()) {
      return $files;
    }

    $sftp = $this->sftp;
    $path = $this->dest_url['path'];
    $dir = "ssh2.sftp://$sftp/$path";
    $handle = opendir($dir);

    // List all the files.
    while (($file = readdir($handle)) !== FALSE) {
      // Skip dotfiles and special paths.
      if (drupal_substr($file, 0, 1) == '.') {
        continue;
      }

      $stat = stat("ssh2.sftp://$sftp/$path/$file");
      if (!$stat) {
        continue;
      }

      // Skip directories.
      if (($stat['mode'] & 0170000) == 040000) {
        continue;
      }

      $files[$file] = new backup_file(array(
        'filename' => $file,
        'filesize' => $stat['size'],
        'filetime' => $stat['mtime'],
      ));
    }
    closedir($handle);

    return $files;
  }

  /**
   * Connect to the remote server.
   */
  protected function sftpConnect() {
    $host = $this->dest_url['host'];
    $port = !empty($this->dest_url['port']) ? $this->dest_url['port'] : 22;
    $this->connection = @ssh2_connect($host, $port);
    if (!$this->connection) {
      throw new Exception("Could not connect to $host on port $port.");
      return FALSE;
    }

    $user = $this->dest_url['user'];
    $pass = $this->dest_url['pass'];
    if (!@ssh2_auth_password($this->connection, $user, $pass)) {
      throw new Exception("Could not authenticate with username $username " . "and password $password.");
      return FALSE;
    }

    $this->sftp = @ssh2_sftp($this->connection);
    if (!$this->sftp) {
      throw new Exception("Could not initialize SFTP subsystem.");
      return FALSE;
    }

    return TRUE;
  }

  /**
   * SFTP settings form.
   */
  public function edit_form() {
    $form = parent::edit_form();
    $form['scheme']['#type'] = 'value';
    $form['scheme']['#value'] = 'sftp';

    $form['port'] = array(
      "#type" => "textfield",
      "#title" => t("Port"),
      "#default_value" => @$this->dest_url['port'] ? $this->dest_url['port'] : '22',
      "#weight" => 15,
    );

    return $form;
  }
}
