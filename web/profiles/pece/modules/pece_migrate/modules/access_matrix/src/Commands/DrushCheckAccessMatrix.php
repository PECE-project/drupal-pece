<?php

namespace Drupal\access_matrix\Commands;

use Drupal\Core\Extension\ExtensionPathResolver;
use Drupal\Core\Session\AccountInterface;
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
  protected function anonymous() {
    return $this->anonymousUser;
  }

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
  protected function authenticated_group() : User {
    if (!$this->authenticatedGroupUser) {
      $this->authenticatedGroupUser = $this->createUser('migrate_');
      $this->addUserInGroups($this->authenticatedGroupUser);
    }
    return $this->authenticatedGroupUser;
  }

  protected $researcherUser;
  protected function researcher() {
    if (!$this->researcherUser) {
      $this->researcherUser = $this->createUser('migrate_');
      $this->addUserInGroups($this->researcherUser, 'researcher');
    }
    return $this->researcherUser;
  }

  protected $researcherGroup;
  protected function researcher_group() {
    if (!$this->researcherGroup) {
      $this->researcherGroup = $this->createUser('migrate_');
      $this->addUserInGroups($this->researcherGroup, 'researcher');
    }
    return $this->researcherGroup;
  }

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
    // Activate user.
    $user->activate();
//    // Add Role to user.
    if (!in_array($role, [AccountInterface::ANONYMOUS_ROLE, AccountInterface::AUTHENTICATED_ROLE])) {
      $user->addRole($role);
    }

    // Save user account.
    $user->save();
    //add logger
    $this->logger()->notice(dt('Created user: @name', ['@name' => $user->id()]));
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
    $nids = \Drupal::entityQuery('node')->condition('type','group')->execute();
    $groups =  \Drupal\node\Entity\Node::loadMultiple($nids);
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

    foreach ($filesCheck as $role => $file) {
      $csvFileName = $role . '.csv';
      $this->logger()->notice(dt('Checking file: @file', ['@file' => $file]));
      $permissions = $this->loadJson($file);
      foreach ($permissions['access'] as $key => $permission) {
        $this->logger()->notice(dt('Checking permission: @permission', ['@permission' => $key]));
        if ($node = Node::load($key)) {
          $result = $node->access('view', $this->{$role}(), FALSE);
          if ($result == $permission) {
            $this->logger()->notice(dt('OK to content @id for @role user.', ['@id' => $key, '@role' => $role]));
            $this->saveToCsv([date('Y-m-d h:i:s'),'success', $key, 'Expect ' . $permission . 'for view and return ' . $result], $csvFileName);
          }
          else {
            $this->logger()->error(dt('Fail to content @id for @role user.', ['@id' => $key, '@role' => $role]));
            $this->saveToCsv([date('Y-m-d h:i:s'),'fail', $key, 'Expect ' . $permission . 'for view and return ' . $result], $csvFileName);
          }
        }
        else {
          $this->logger()->alert(dt("Content with id @id doesn't exist", ['@id' => $key]));
          $this->saveToCsv([date('Y-m-d h:i:s'),'alert',$key, 'Content doesn\'t exist'], $csvFileName);
        }
      }
      //delete the user in drupal
      if($this->{$role})
        $this->{$role}->delete();
    }
  }

  /**
   * Load json file with access test.
   * @param $path
   *
   * @return mixed
   */
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

  /**
   * Function to save value in csv file
   * @param $data array with line to save
   * @param $fileName string with name of file
   *
   * @return void
   */
  private function saveToCsv(array $data, string $fileName) {
    // create folder in public folder if not exist.
    $folder = \Drupal::service('file_system')->realpath('public://') . '/access_matrix';
    if (!file_exists($folder)) {
      mkdir($folder);
    }
    // get file path in drupal
    $filePath = \Drupal::service('file_system')->realpath('public://access_matrix/' . $fileName);
    //create file if not exist with folder migrate-logs
    $file = fopen($filePath, 'a');
    fputcsv($file, $data);
    fclose($file);
  }

}
