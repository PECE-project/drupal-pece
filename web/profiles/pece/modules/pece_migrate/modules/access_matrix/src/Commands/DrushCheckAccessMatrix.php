<?php

namespace Drupal\access_matrix\Commands;

use Drupal\Core\Extension\ExtensionPathResolver;
use Drupal\Core\Session\AccountSwitcherInterface;
use Drupal\Core\Session\UserSession;
use Drupal\node\Entity\Node;
use Drupal\user\Entity\User;
use Drush\Commands\DrushCommands;

/**
 * A drush command file to check access matrix for view content.
 *
 * @package Drupal\access_matrix\Commands
 */
class DrushCheckAccessMatrix extends DrushCommands {

  /**
   * The account switcher service.
   *
   * @var \Drupal\Core\Session\AccountSwitcherInterface
   */
  protected $accountSwitcher;

  protected $anonymousUser = NULL;

  /**
   * Authenticated user.
   * @var
   */
  private $authenticatedUser;
  protected function authenticated() {
    if (!$this->authenticatedUser)
      $this->authenticatedUser = $this->createUser('migrate_');

    return $this->authenticatedUser;
  }

  private $authenticatedGroupUser;
  protected function authenticated_group() {
    if (!$this->authenticatedGroupUser) {
      $this->authenticatedGroupUser = $this->createUser('migrate_');
      addUserInGroups($this->authenticatedGroupUser);
    }
    return $this->authenticatedGroupUser;
  }

  protected $researcherUser;
  //TODO: need create function to create user with role researcher

  protected $researcherGroup;
  //TODO: need create function to create user with role researcher in groups


  /**
   * @param $prefixName
   * @param $role string
   * @return \Drupal\user\Entity\User
   */
  private function createUser($prefixName = "", $role = 'authenticated'): \Drupal\user\Entity\User {
    $name = $prefixName . $this->generateRandomString();
    $user = \Drupal\user\Entity\User::create([
      'name' => $name,
      'mail' => $name . '@example.com',
      'pass' => $name . 'pass',
    ]);

    // Add Role to user.
    $role = \Drupal::entityTypeManager()
      ->getStorage('user_role')
      ->load($role);
    // Mandatory.
    $user->addRole($role->id());
    // Activate user.
    $user->activate();

    // Save user account.
    $user->save();
    return $user;
  }

  /**
   * Create random string for user mail.
   * @param int $length
   *
   * @return string
   */
  private function generateRandomString(int $length = 5):string {
    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < $length; $i++) {
      $randomString .= $characters[rand(0, $charactersLength - 1)];
    }
    return $randomString;
  }

  /**
   * Add user in all groups
   * @param $user \Drupal\user\Entity\User
   */
  private function addUserInGroups(User $user) {
    //TODO: need test this code
    $groups = \Drupal::entityTypeManager()
      ->getStorage('group')
      ->loadMultiple();
    $user->set('field_pbc_ref_group', $groups);
    $user->save();
  }

  /**
   * Drush command that displays the given text.
   * This code don't get subfolders.
   *
   * @param string $path
   *   Path to file or folder with the access to test.
   * @command access_matrix:access
   * @aliases pece-access-test pc-ac
   * @usage access_matrix:access files/pece_annotations
   * @handle-remote-commands true
   */
  public function access(string $path) {
    $filesCheck = [];
    //Check path is folder of file.
    if (is_dir($path)) {
      //get all files in the folder and save in the filesCheck array.
      $filesCheck = $this->getFiles($path);
    }
    elseif (is_file($path)) {
      //get file name and remove the extension.
      $fileName = pathinfo($path, PATHINFO_FILENAME);
      $filesCheck[$fileName] = $path;
    }
    else {
      $this->logger()->error(dt('The path is not valid.'));
      return;
    }

    //TODO: need test with user can view content.
    foreach ($filesCheck as $role => $file) {
      //load_node($key)->access('view', NULL, TRUE);
     // Node::load($id)->access('view', NULL, TRUE);
      $this->logger()->notice(dt('Checking file: @file', ['@file' => $file]));
      $datas = $this->loadJson($file);
      //TODO: foreach to check access.
      foreach ($datas as $data) {
        
      }
      //TODO: check in foreach if value in array is the same as the access value.
    }

    $this->output()->writeln($path);
  }

  private function loadJson($path) {
    $json = file_get_contents($path);
    $data = json_decode($json, TRUE);
    return $data;
  }

  /**
   * Get all files in the folder.
   */
  private function getFiles($path) {
    $files = scandir($path);
    $filesCheck = [];
    foreach ($files as $file) {
      if (is_file($path . '/' . $file)) {
        //get file name and remove the extension.
        $fileName = pathinfo($file, PATHINFO_FILENAME);
        $filesCheck[$fileName] = $path . '/' . $file;
      }
    }
    return $filesCheck;
  }

}
