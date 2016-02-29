<?php
/**
 * @file
 * pece_frontpage_slideshow.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_frontpage_slideshow_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node frontpage_image_slideshow breadcrumbs'.
  $permissions['administer panelizer node frontpage_image_slideshow breadcrumbs'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow breadcrumbs',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow content'.
  $permissions['administer panelizer node frontpage_image_slideshow content'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow context'.
  $permissions['administer panelizer node frontpage_image_slideshow context'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow context',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow defaults'.
  $permissions['administer panelizer node frontpage_image_slideshow defaults'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow layout'.
  $permissions['administer panelizer node frontpage_image_slideshow layout'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow layout',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow overview'.
  $permissions['administer panelizer node frontpage_image_slideshow overview'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow overview',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow settings'.
  $permissions['administer panelizer node frontpage_image_slideshow settings'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'create frontpage_image_slideshow content'.
  $permissions['create frontpage_image_slideshow content'] = array(
    'name' => 'create frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any frontpage_image_slideshow content'.
  $permissions['delete any frontpage_image_slideshow content'] = array(
    'name' => 'delete any frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own frontpage_image_slideshow content'.
  $permissions['delete own frontpage_image_slideshow content'] = array(
    'name' => 'delete own frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any frontpage_image_slideshow content'.
  $permissions['edit any frontpage_image_slideshow content'] = array(
    'name' => 'edit any frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own frontpage_image_slideshow content'.
  $permissions['edit own frontpage_image_slideshow content'] = array(
    'name' => 'edit own frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'set frontpage_image_slideshow published on date'.
  $permissions['set frontpage_image_slideshow published on date'] = array(
    'name' => 'set frontpage_image_slideshow published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  return $permissions;
}
