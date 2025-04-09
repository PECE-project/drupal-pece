<?php

/**
 * Test PECE access.
 * Need simpletest module installed
 *
 */
class PeceAccessMatrix  extends DrupalWebTestCase {

  protected $user;
  protected $userRole = NULL;

  // Create getInfo method
  public static function getInfo() {
    return array(
      'name' => 'Pece Access Matrix',
      'description' => 'Create Pece Access Matrix',
      'group' => 'PECE',
    );
  }

  /**
   * Override this function to use the same database for all tests.
   * @return void
   */
  protected function prepareDatabasePrefix()
  {

  }

  /**
   * Override this function to use the same database for all tests.
   * @return void
   */
  protected function tearDown () {
    // Remove the user.
    user_delete($this->user->uid);
  }

  /**
   * Override this function to use the same database for all tests.
   * @return void
   */
  protected function prepareEnvironment() {
    global $user, $language, $language_url, $conf;

    // Store necessary current values before switching to prefixed database.
    $this->originalLanguage = $language;
    $this->originalLanguageUrl = $language_url;
    $this->originalLanguageDefault = variable_get('language_default');
    $this->originalFileDirectory = variable_get('file_public_path', conf_path() . '/files');
    $this->verboseDirectoryUrl = file_create_url($this->originalFileDirectory . '/simpletest/verbose');
    $this->originalProfile = drupal_get_profile();
    $this->originalCleanUrl = variable_get('clean_url', 0);
    $this->originalUser = $user;

    // Set to English to prevent exceptions from utf8_truncate() from t()
    // during install if the current language is not 'en'.
    // The following array/object conversion is copied from language_default().
    $language_url = $language = (object) array('language' => 'en', 'name' => 'English', 'native' => 'English', 'direction' => 0, 'enabled' => 1, 'plurals' => 0, 'formula' => '', 'domain' => '', 'prefix' => '', 'weight' => 0, 'javascript' => '');

    // Save and clean the shutdown callbacks array because it is static cached
    // and will be changed by the test run. Otherwise it will contain callbacks
    // from both environments and the testing environment will try to call the
    // handlers defined by the original one.
    $callbacks = &drupal_register_shutdown_function();
    $this->originalShutdownCallbacks = $callbacks;
    $callbacks = array();

    // Create test directory ahead of installation so fatal errors and debug
    // information can be logged during installation process.
    // Use temporary files directory with the same prefix as the database.
    $this->public_files_directory = $this->originalFileDirectory;
    $this->private_files_directory = $this->public_files_directory . '/private';
    $this->temp_files_directory = $this->private_files_directory . '/temp';

    // Create the directories
    file_prepare_directory($this->public_files_directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    file_prepare_directory($this->private_files_directory, FILE_CREATE_DIRECTORY);
    file_prepare_directory($this->temp_files_directory, FILE_CREATE_DIRECTORY);
    $this->generatedTestFiles = FALSE;

    // Log fatal errors.
    ini_set('log_errors', 1);
    ini_set('error_log', $this->public_files_directory . '/error.log');

    // Set the test information for use in other parts of Drupal.
    $test_info = &$GLOBALS['drupal_test_info'];
    $test_info['test_run_id'] = $this->databasePrefix;
    $test_info['in_child_site'] = FALSE;

    // Indicate the environment was set up correctly.
    $this->setupEnvironment = TRUE;
  }

  /**
   * Override this function to use the same file folders.
   * @return void
   */
  // Create setUp method
  function setUp() {

    $this->profile = 'PECE';
    $this->databasePrefix = '';
    $this->prepareEnvironment();
    $this->setupDatabasePrefix = TRUE;
    $this->setup = TRUE;
    $this->public_files_directory = $this->originalFileDirectory . '/simpletest/' . substr($this->databasePrefix, 10);
    $this->private_files_directory = $this->public_files_directory . '/private';
    $this->temp_files_directory = $this->private_files_directory . '/temp';
  }

  /**
   * Check Access Permissions of all content types available on the platform.
   */
  public function testContentTypesAccessPerms() {
    // Get full list of all content types to validate its permissions.
    foreach ($contentTypes = $this->getAllContentTypes() as $contentType) {
      $this->validateAccessPermsByType($contentType);
    }
  }

  /**
   * Helper function to map and validate the access permission matrix for all nodes of a given content type.
   *
   * @param String $contentTypeName
   * @return void
   */
  protected function validateAccessPermsByType($contentTypeName) {

    $module_path = drupal_realpath(drupal_get_path('module', 'pece_access'));
    $nodes = node_load_multiple(array(), array('type' => $contentTypeName));
    if (empty($nodes)) {
      return;
    }
    // If there is no directory named with $contentType, then create it.
    if (!file_exists($module_path . '/files/' . $contentTypeName)) {
      mkdir($module_path . "/files/$contentTypeName", 0766, TRUE);
    }
    $this->assertTrue(file_exists($module_path . "/files/$contentTypeName"), "Folder $contentTypeName created");

    $data = array(
      'role' => $this->userRole,
      'size' => count($nodes),
      'access' => array(),
    );
    if ($this->user)
      $this->drupalLogin($this->user);
    // Create JSON file with Node ID for each and every node.
    foreach ($nodes as $node) {
      $file_name = $module_path . "/files/$contentTypeName/" . $this->userRole . '.json';
      // create object to salve in json file
      $data['access'][$node->nid] = $this->viewContentWithUser($node, $this->user);
      $file_content = json_encode($data, JSON_PRETTY_PRINT);
      file_put_contents($file_name, $file_content);
    }
    $this->assertTrue(file_exists($file_name), 'File exists');
    if ($this->user)
      $this->drupalLogout();
  }

  /**
   *  Create user with role.
   *
   * @param $role
   */
  protected function drupalCreateUserWithRole($prefixname = '', $role) {
    $user = $this->drupalCreateUser();
    $user->name = $prefixname . $user->name;
    $role = user_role_load_by_name($role);
    $user->roles = array($role->rid => $role->name);
    user_save($user);
    return $user;
  }

  /**
   * Check view content with user.
   */
  public function viewContentWithUser($node, $user = null) {
    $this->drupalGet('/node/' . $node->nid);
    // get the response code
    $testView = $this->getResponseCode() == 200 ? TRUE : FALSE;
    if ($user)
      $this->drupalLogout();
    return $testView;
  }

  /**
   * Get the response code.
   * @return value
   *
   */
  protected function getResponseCode() {
    $curl_code = curl_getinfo($this->curlHandle, CURLINFO_HTTP_CODE);
    return $curl_code;
  }

  /**
   * Get all available content types.
   * @return array types
   */
  protected function getAllContentTypes() {
    $artifactsTypes = [
      'pece_artifact_audio',
      'pece_artifact_bundle',
      'pece_artifact_fieldnote',
      'pece_artifact_image',
      'pece_artifact_pdf',
      'pece_artifact_tabular',
      'pece_artifact_text',
      'pece_artifact_video',
      'pece_artifact_website',
      'pece_essay',
      'pece_photo_essay',
      'pece_timeline_essay',
      'pece_project',
      'pece_annotation',
    ];

    return $artifactsTypes;
  }

  /**
   * Add user in all groups.
   * @param $user user
   * @param $role int
   */
  protected function addUserInAllGroups($user, $role = 4) {
    $groups = node_load_multiple([], ['type' => 'pece_group']);
    $group_type = 'node';
    foreach ($groups as $group) {
      // Add the user to the group
      og_group($group_type, $group->nid, [
        "entity_type" => "user",
        "entity" => $user,
        'state' => OG_STATE_ACTIVE,
        "membership_type" => OG_MEMBERSHIP_TYPE_DEFAULT,
        "field_name" => 'og_user_node',
      ]);
      // Add researcher grant user to group, the number 5.
      og_role_grant($group_type, $group->nid, $user->uid, $role);
    }
  }

}
