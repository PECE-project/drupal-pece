<?php

/**
 * @file
 * Hooks related to registering manifests.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Define the manifests provided by a module.
 *
 * The hook enables modules to define manifests. It should be in the module's
 * .install file.
 *
 * @return
 *   An array of manifests. The array is keyed on the machine-readable manifest
 *   name. The name must be unique per module.
 *   - "callback": The function that should be called to execute the manifest
 *   - "callback arguments": (optional) Array of arguments that should be passed 
 *     into the callback. The allows you to keep your manifest callbacks a bit 
 *     more generic, so you can DRY your code up a little.
 *   - "file": (optional) A file that will be included before the manifest is 
 *     executed; this allows manifest callback functions to be in separate 
 *     files. The file should be relative to the implementing module's directory
 *     unless otherwise specified by the "file path" option.
 *   - "file path": (optional) The path to the directory containing the file 
 *     specified in "file". This defaults to the path to the module implementing
 *     the hook.
 *   - "dependencies": (optional) Array of manifests that should be executed 
 *     for the registered manifest. Every manifest is an associative array, 
 *     containing a "module" and a "name" key.
 *   - "require environment": (optional) Array of environments in which the 
 *     manifest should be executed. In all other environments, it should not be
 *     executed. Can be a string, which will be interpreted as an array with the
 *     string as its single item.
 *   - "exclude environment": (optional) Array of environments in which the
 *     manifest should not be executed. In all other environments, it should be
 *     executed. Can be a string, like "require environment".
 */
function hook_kw_manifests_info() {
  $manifests = array();

  $manifests['my_manifest'] = array(
    'callback' => 'mymodule_manifest_my_manifest',
    'file' => 'mymodule.manifests.inc',
    'dependencies' => array(
      array('module' => 'othermodule', 'name' => 'their_manifest'),
      array('module' => 'othermodule2', 'name' => 'other_manifest'),
    ),
    'require environment' => array('development')
  );

  return $manifests;
}

/**
 * @} End of "addtogroup hooks".
 */