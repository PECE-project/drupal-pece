<?php
/**
 * @file
 * panopoly_test.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function panopoly_test_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node panopoly_test_landing_page breadcrumbs'.
  $permissions['administer panelizer node panopoly_test_landing_page breadcrumbs'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page breadcrumbs',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_landing_page content'.
  $permissions['administer panelizer node panopoly_test_landing_page content'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_landing_page context'.
  $permissions['administer panelizer node panopoly_test_landing_page context'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page context',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_landing_page defaults'.
  $permissions['administer panelizer node panopoly_test_landing_page defaults'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_landing_page layout'.
  $permissions['administer panelizer node panopoly_test_landing_page layout'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page layout',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_landing_page overview'.
  $permissions['administer panelizer node panopoly_test_landing_page overview'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page overview',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_landing_page settings'.
  $permissions['administer panelizer node panopoly_test_landing_page settings'] = array(
    'name' => 'administer panelizer node panopoly_test_landing_page settings',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page breadcrumbs'.
  $permissions['administer panelizer node panopoly_test_page breadcrumbs'] = array(
    'name' => 'administer panelizer node panopoly_test_page breadcrumbs',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page content'.
  $permissions['administer panelizer node panopoly_test_page content'] = array(
    'name' => 'administer panelizer node panopoly_test_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page context'.
  $permissions['administer panelizer node panopoly_test_page context'] = array(
    'name' => 'administer panelizer node panopoly_test_page context',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page defaults'.
  $permissions['administer panelizer node panopoly_test_page defaults'] = array(
    'name' => 'administer panelizer node panopoly_test_page defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page layout'.
  $permissions['administer panelizer node panopoly_test_page layout'] = array(
    'name' => 'administer panelizer node panopoly_test_page layout',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page overview'.
  $permissions['administer panelizer node panopoly_test_page overview'] = array(
    'name' => 'administer panelizer node panopoly_test_page overview',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node panopoly_test_page settings'.
  $permissions['administer panelizer node panopoly_test_page settings'] = array(
    'name' => 'administer panelizer node panopoly_test_page settings',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'create panopoly_test_landing_page content'.
  $permissions['create panopoly_test_landing_page content'] = array(
    'name' => 'create panopoly_test_landing_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create panopoly_test_page content'.
  $permissions['create panopoly_test_page content'] = array(
    'name' => 'create panopoly_test_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create panopoly_test_page_simple content'.
  $permissions['create panopoly_test_page_simple content'] = array(
    'name' => 'create panopoly_test_page_simple content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any panopoly_test_landing_page content'.
  $permissions['delete any panopoly_test_landing_page content'] = array(
    'name' => 'delete any panopoly_test_landing_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any panopoly_test_page content'.
  $permissions['delete any panopoly_test_page content'] = array(
    'name' => 'delete any panopoly_test_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any panopoly_test_page_simple content'.
  $permissions['delete any panopoly_test_page_simple content'] = array(
    'name' => 'delete any panopoly_test_page_simple content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own panopoly_test_landing_page content'.
  $permissions['delete own panopoly_test_landing_page content'] = array(
    'name' => 'delete own panopoly_test_landing_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own panopoly_test_page content'.
  $permissions['delete own panopoly_test_page content'] = array(
    'name' => 'delete own panopoly_test_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own panopoly_test_page_simple content'.
  $permissions['delete own panopoly_test_page_simple content'] = array(
    'name' => 'delete own panopoly_test_page_simple content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any panopoly_test_landing_page content'.
  $permissions['edit any panopoly_test_landing_page content'] = array(
    'name' => 'edit any panopoly_test_landing_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any panopoly_test_page content'.
  $permissions['edit any panopoly_test_page content'] = array(
    'name' => 'edit any panopoly_test_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any panopoly_test_page_simple content'.
  $permissions['edit any panopoly_test_page_simple content'] = array(
    'name' => 'edit any panopoly_test_page_simple content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own panopoly_test_landing_page content'.
  $permissions['edit own panopoly_test_landing_page content'] = array(
    'name' => 'edit own panopoly_test_landing_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own panopoly_test_page content'.
  $permissions['edit own panopoly_test_page content'] = array(
    'name' => 'edit own panopoly_test_page content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own panopoly_test_page_simple content'.
  $permissions['edit own panopoly_test_page_simple content'] = array(
    'name' => 'edit own panopoly_test_page_simple content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
