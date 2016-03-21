<?php

/**
 * @file
 *   Drush support for entities.
 */

/**
 * Define how a print out needs to be.
 */
define('DRUSH_ENTITY_SEPARATED_SPACE', 'space-separated');

/**
 * Implementation of hook_drush_command().
 */
function entity_drush_command() {
  // Some standard settings
  $output_json = 'Process the entity as JSON';
  $output_format = 'Define output format. Known formats are: json, print_r, properties, export';
  $type = 'Entity type';
  $nids = 'A list of space-separated entity IDs to print to stdout.';
  $bundles = 'Filter by entity bundles. Provide a comma separated list of entity types.';

  $items = array();

  // Entity type commands
  $items['entity-type-read'] = array(
    'description' => 'List details of entity types',
    'arguments' => array(
      'type' => 'Entity type to list. If omitted all types are listed.',
    ),
    'options' => array(
      'format' => $output_format,
      'fields' => 'fields of type to list specific info.',
      'exclude-fields' => 'exclude fields from the list',
      'include-fieldapi' => 'include the bundle specific field definitions',
    ),
    'examples' => array(
      'entity-type-read' => 'List available entity types',
      'entity-type-read node' => 'List node type information',
      'entity-type-read node --fields=bundles' => 'List bundles for node type',
      "etr --fields='entity keys',fieldable" => 'List all entity keys and fieldable.',
      'entity-type-read node --fields=bundles/*/admin/path' => 'List admin path for all bundles',
    ),
    'aliases' => array('etr'),
  );

  $items['entity-list'] = array(
    'callback' => 'drush_entity_list',
    'description' => 'Get a list of entity type information in a summary table.',
    'aliases' => array('el'),
    'arguments' => array(
      'types' => dt('A space separated list of entity types to show.'),
    ),
    'examples' => array(
      'entity-list' => 'Displays all entity summaries',
      'entity-list node' => 'Displays node entity summary',
      'entity-list node user' => 'Displays node and user entity summaries.',
    ),
  );

  // Entity commands
  $items['entity-create'] = array(
    'description' => 'Create an entity from a json object',
    'arguments' => array(
      'type' => 'Entity type',
    ),
    'options' => array(
      'json' => $output_json,
    ),
    'examples' => array(
      'entity-read node 4 --json | drush entity-create node' => 'Copy node/4 to a new entity.',
    ),
    'aliases' => array('ec'),
  );

  $items['entity-read'] = array(
    'description' => 'Print entity contents',
    'arguments' => array(
      'type' => $type,
      'nids' => $nids,
    ),
    'options' => array(
      'format' => $output_format,
      'fields' => 'fields of type to list specific info',
      'bundles' => $bundles,
      'load' => 'Load all entities returned, rather than return list of IDs (default).'
    ),
    'examples' => array(
      'entity-read user 4' => 'Print the user object 4',
      'entity-read taxonomy_vocabulary 1' => 'Print the taxonomy_vocabulary object 1',
    ),
    'aliases' => array('er'),
  );

  $items['entity-update'] = array(
    'description' => 'Update an entity as json in the default editor',
    'arguments' => array(
      'type' => $type,
      'nids' => $nids,
    ),
    'options' => array(
      'json' => $output_json,
      'fields' => 'fields of type to list specific info',
      'json-input' => 'Filename with json content, or - for STDIN'
    ),
    'examples' => array(
      'entity-update node 4' => 'Update node 4 as json in the default editor',
    ),
    'aliases' => array('eu'),
  );

  $items['entity-delete'] = array(
    'description' => 'Delete entities.',
    'arguments' => array(
      'type' => $type,
      'nids' => $nids,
    ),
    'options' => array(
      'json' => $output_json,
      'bundles' => $bundles,
    ),
    'examples' => array(
      'entity-delete' => '.',
      'entity-delete node 64' => '.',
      'entity-delete node --type=story' => '.',
    ),
    'aliases' => array('ed'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function entity_drush_help($section) {
  switch ($section) {
    case 'drush:entity-show':
      return dt('Print entity objects to stdout');
    case 'drush:entity-create':
      return dt('Create an entity from a json object');
    case 'drush:entity-edit':
      return dt('Edit an entity as json in the default editor');
    case 'drush:entity-delete':
      return dt('Delete entities');
    case 'meta:entity:title':
      return dt('Entity commands');
    case 'meta:entity:summary':
      return dt('Query (perform CRUD operations) drupal entities');
  }
}

/**
 * Drush callback function to get entity info.
 */
function drush_entity_list() {
  $entities = _drush_entity_get_info();
  $types = func_get_args();

  if (count($types)) {
    foreach (array_keys($entities) as $entity) {
      if (!in_array($entity, $types)) {
        unset($entities[$entity]);
      }
    }
  }

  $entity_count = count($entities);
  drush_print("\n" . dt('Entity count: @count', array('@count' => $entity_count)) . "\n");

  $header = array(
    dt('Entity'),
    dt('Label'),
    dt('Bundles'),
    dt('Base table'),
    dt('Revision table'),
    dt('Count'),
    dt('Fieldable'),
    dt('Entity class'),
    dt('Controller class'),
  );

  function __drush_entity_newline($value) {
     return $value . "\n";
  };

  $header = array_map('__drush_entity_newline', $header);

  // drush etr `drush etr` --fields="bundles/*/label,label,base table,revision table,fieldable,entity class,controller class,drush/count"
  $rows = array();
  $row = array();
  foreach ($entities as $machine => $info) {
    if ($entity_count > 1) {
      $rows[] = array('---------------');
    }

    $row[] = $machine;
    $row[] = isset($info['label']) ? $info['label'] : dt('No label found');
    $row[] = is_array($info['bundles']) ? _drush_entity_get_bundle_labels($info['bundles']) : NULL;
    $row[] = $info['base table'];
    $row[] = isset($info['revision table']) ? $info['revision table'] : NULL;
    $row[] = $info['drush']['count'];
    $row[] = $info['fieldable'] ? dt('TRUE') : dt('FALSE');
    $row[] = isset($info['entity class']) ? $info['entity class'] : dt('Default');
    $row[] = isset($info['controller class']) ? $info['controller class'] : dt('Default');
    // Add row to rows array.
    $rows[$machine] = $row;
    //Unset so we can start again on next iteration.
    unset($row);
  }
  array_unshift($rows, $header);

  $widths = array(15, 10, 30, 15, 15, 6, 9, 15);

  drush_print_table($rows, TRUE, $widths);
}

/**
 * Get list of bundle labels for an entity type.
 * This list can be returned as an array or csv list.
 *
 * @param $bundles
 *  bundles array from entity_get_info().
 * @param $csv
 *  (bool) return as csv list or as array of bundle labels.
 */
function _drush_entity_get_bundle_labels($bundles, $csv = TRUE) {
  $labels = array();
  foreach ($bundles as $bundle_key => $bundle_info) {
    if (drush_drupal_major_version() < 7) {
      $bundle_name = $bundle_info;
    }
    else {
      $bundle_name = $bundle_info['label'];
    }
    $label = isset($bundle_name) ? $bundle_name : dt('No label found');
    $labels[] = $label . " ($bundle_key)";
  }
  return $csv ? implode("\n", $labels) : $labels;
}

/**
 * List details of entity types
 *
 * @param $entity_types
 *   Entity type machine names.
 *
 * @return
 *   An array of entity info for selected entities.
 */
function drush_entity_type_read($entity_types = NULL) {
  $types = func_get_args();
  $entity_info = _drush_entity_get_info();
  $fields = _drush_entity_explode_options('fields');
  $format = drush_get_option('format', 'print_r');

  // List the available types if no types are passed in.
  if (empty($entity_types)) {
    $types = array_keys($entity_info);
    if (!$fields) {
      // Just print the key of each type.
      drush_print(drush_format($types, NULL, $format));
      return;
    }
  }

  $result = array();

  if (count($types)) {
    foreach ($types as $type) {
      if (isset($entity_info[$type])) {
        $info = $entity_info[$type];
        // Filter and return only selected fields, if any have been specified.
        $result_type = _drush_entity_filter_fields($info, $fields, _drush_entity_get_exclude_fields());
        if (!empty($result_type)) {
          $result[$type] = $result_type;
        }
      }
    }
  }

  if (empty($result)) {
    drush_set_error(dt('No entity type information returned for: @types',
      array('@types' => implode(', ', $types))));
  }
  else {
    drush_print(drush_format($result, NULL, $format));
  }
}

/**
 * Filter on the given paths
 *
 * Each path may contain forward slashes / to filter subtrees
 *
 * A path may contain a star * or ** to wildcard a path
 *
 * Example paths (ignore space after *)
 * - schema_fields_sql
 * - bundles/* /label
 * - ** /display
 *
 * @param array $value
 * @param array $paths
 *   List of paths to filter about.
 *
 * @return Array
 *   The matching path.
 */
function _drush_entity_filter_fields(array $value = array(), array $paths, array $delete_path = array()) {
  // Store object hashs to prevent object ref recursion
  $object_hash_list = array();
  $return = array();
  if (empty($paths)) {
    $return = $value;
  }
  // List of path already done
  $visited = array();
  while (count($paths) > 0) {
    $path = array_shift($paths);
    if (isset($visited[$path])) {
      continue;
    }
    $visited[$path] = $path;
    // Contains the resulting path
    $head = array();
    // The result is a linked list done with an key => array construct
    $tail = &$head;  // By ref
    $sub_tree = explode('/', $path);
    $current_path = '';
    $work_value = $value;
    $failed_path = FALSE;
    while (count($sub_tree) > 0) {
      $p = array_shift($sub_tree);
      if ($p == '*' || $p == '**') {
        // Wildcards only usefull on arrays
        if (is_array($work_value) || _drush_entity_visit_object($object_hash_list, $work_value)) {
          // Say a/**/b was requested
          // We need to search for a/b and a/$option/**/b
          $new_tree = $sub_tree;
          $new_path = $current_path . join('/', $new_tree);
          if (!isset($visited[$new_path])) {
            array_push($paths, $new_path);
          }
          // We cast to array only to generate paths
          $p_options = array_keys((array) $work_value);
          foreach ($p_options as $p_option) {
            // Create
            $new_tree = $sub_tree;
            array_unshift($new_tree, $p_option);
            $new_path = $current_path . join('/', $new_tree);
            if (!isset($visited[$new_path])) {
              array_push($paths, $new_path);
              if ($p == '**') {
                $new_tree = $sub_tree;
                array_unshift($new_tree, '**');
                array_unshift($new_tree, $p_option);
                $new_path = $current_path . join('/', $new_tree);
                if (!isset($visited[$new_path])) {
                  array_push($paths, $new_path);
                }
              }
            }
          }
        }
        else {
          $failed_path = TRUE;
        }
        // We processed the wildcard paths so stop processing
        break; // sub tree processing
      }
      // Remember current path
      $current_path .= $p . '/';
      // Consume key
      $temp = (array) $work_value;
      if (is_array($temp) && isset($temp[$p])) {
        $work_value = $temp[$p];
        if (is_object($work_value) || is_array($work_value)) {
          if (count($sub_tree)) {
            // We are not done yet
            $tail[$p] = array();
          }
          else {
            // Stuff value: object or array
            $tail[$p] = $work_value;
          }
        }
        else {
          $tail[$p] = $work_value;
        }
        // Follow the build tree
        $tail = &$tail[$p]; // By ref
      }
      else {
        $failed_path = TRUE;
        break; // while
      }
    }
    if (!$failed_path && count($sub_tree) == 0) {
      $return = array_merge_recursive($return, $head);
    }
  }
  if ($delete_path) {
    $delete = _drush_entity_filter_fields($return, $delete_path);
    // TODO substract $delete from $return .. next command deletes more
    // try etr --include-fieldapi ... the are deleted too
    // $return = array_diff($return, $delete);
  }

  return $return;
}

/**
 * List the entity IDs of the given type
 *
 * @param $entity_type
 * @param $bundles
 *   Array of bundles (as returned from drush_get_option).
 * @param $print
 *   TRUE/FALSE - print ids to screen.
 */
function _drush_entity_id_list($entity_type, array $bundles = array(), $print = TRUE) {
  $entity_info = _drush_entity_get_info($entity_type);
  $bundle_list = '';
  $result = array();

  if (drush_drupal_major_version() < 7) {
    if (isset($entity_info['load list sql'])) {
      $sql = $entity_info['load list sql'];
      $entities = array();
      // Add bundle condition to query.
      if ($bundles) {
        $sql .= " WHERE type ";
        // If there is only 1 bundle type, we don't need placeholders.
        if (count($bundles) == 1) {
          $sql .= "= '%s'";
          // Make bundle a string, instead of an array.
          $bundles = reset($bundles);
        }
        // Add placeholders for each bundle type.
        else {
          $sql .= "IN (" . db_placeholders($bundles, 'varchar') . ")";
        }
      }
      $result = db_query($sql, $bundles);
      // Create our own list of ids, to mimic return from EFQ.
      while ($row = db_fetch_object($result)) {
        $entities[$entity_type][$row->id] = $row->id;
      }
    }
  }
  else {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type);
    if ($bundles) {
      $query->entityCondition('bundle', $bundles);
      //Return bundle values back to csv format.
      $bundle_list = implode(',', $bundles);
    }
    $entities = $query->execute();
  }

  if (isset($entities[$entity_type])) {
    $result = array_keys($entities[$entity_type]);
  }

  if ($print) {
    // If it's an empty result in D6 it will just return resource id, so check it's an array too.
    if (!empty($result) && is_array($result)) {
      // Will only be set if there are results.
      $drush_format = drush_get_option('format');
      $format = $drush_format ? $drush_format : DRUSH_ENTITY_SEPARATED_SPACE;
			$header = NULL;
    }
    else {
      $format = DRUSH_ENTITY_SEPARATED_SPACE;
      $header = $bundles ? dt("No $bundle_list entities found for $entity_type") : dt("No ids found for $entity_type");
      $result = array();
    }
    _drush_entity_print($result, $format, $header);
  }

  return $result;
}

/**
 * Show entities by given type and ids.
 *
 * @param string $type
 *   Given entity type.
 * @param $ids
 *   List of entity IDs to read.
 *
 * @return
 *   Loaded entity information.
 */
function drush_entity_read($entity_type = NULL) {
  if (!$entity_type) {
    drush_set_error('DRUSH_ENTITY_READ_ERROR', dt('You must specify an entity_type'));
    return;
  }
  $ids = func_get_args();
  $entity_type = array_shift($ids);
  _drush_entity_check_type($entity_type);
  $bundles = _drush_entity_explode_options('bundles');

	// Do listing
	if (count($ids) == 0) {
		if (drush_get_option('load')) {
      // Get all the ids, Don't print list - return as array.
			$ids = _drush_entity_id_list($entity_type, $bundles, FALSE);
		}
		else {
      // Print the list to the screen and return.
			_drush_entity_id_list($entity_type, $bundles);
			return;
		}
	}

  // Do content
  $entities = _drush_entity_load($entity_type, $ids);

  $fields = _drush_entity_explode_options('fields');
  if ($fields) {
    $entities = _drush_entity_select_fields($entities, $fields, TRUE);
  }

  if (drush_get_option('json', FALSE) && count($entities) == 1) {
    // We only shift when requesting json and just one entity
    $entities = array_shift($entities);
  }

	if ($entities) {
		drush_print_pipe(drush_format($entities));
		drush_print(drush_format($entities));
	}
	else {
		drush_set_error('DRUSH_ENTITY_READ_ERROR', dt('No entities returned'));
	}
}

/**
 * Extract the selected fields from a number of entities.
 *
 * @param $entities
 *   Array of entities.
 * @param $fields
 *   Array of fileds to be returned for each entity.
 *
 * @return
 *   Array of entity values with return value from _drush_entity_filter_fields
 *   for each.
 */
function _drush_entity_select_fields(array $entities, array $fields, $allow_path = FALSE) {
  if (!$allow_path) {
    foreach ($fields as $path) {
      if (strpos($path, '/') !== FALSE) {
        drush_set_error('DRUSH_ENTITY_FIELD_ERROR', dt('No path supported yet : @path',
          array('@path' => $path)));
      }
      if (strpos($path, '*') !== FALSE) {
        drush_set_error('DRUSH_ENTITY_FIELD_ERROR', dt('No wildcard supported yet : @path',
          array('@path' => $path)));
      }
    }
  }

  $result = array();
  foreach ($entities as $eid => $entity) {
    $result[$eid] = _drush_entity_filter_fields((array) $entity, $fields);
  }

  return $result;
}

/**
 * Create an entity by the given type.
 *
 * @param $entity_type
 *   The entity type to create.
 * @param $file
 *   The (optional) source file to create entities from.
 */
function drush_entity_create($entity_type = NULL, $file = NULL) {
  if (!$entity_type) {
    drush_set_error('DRUSH_ENTITY_CREATE_ERROR', dt('You must specify an entity type'));
    return;
  }

  _drush_entity_check_type($entity_type);

  if (empty($file)) {
    $entity_class = isset($entity_info['entity class']) ? $entity_info['entity class'] : 'stdClass';
    $entity = new $entity_class();
    // Create defaults on the entity object.
    if (isset($entity_info['drush']['defaults'])) {
      foreach ($entity_info['drush']['defaults'] as $key => $value) {
        $entity->$key = $value;
      }
    }
    $entity_json = _drush_entity_edit_string(drush_json_encode($entity));
  }
  else if ($file === '-' || file_exists($file)) {
    if ($file === '-') {
      $entity_json = stream_get_contents(STDIN);
    }
    else {
      drush_log("Reading file $file");
      $entity_json = file_get_contents($file);
    }
  }
  else {
    drush_set_error('DRUSH_ENTITY_CREATE_ERROR', dt('Improper input/args'));
  }

  if (!empty($entity_json)) {
    $entities = drush_json_decode($entity_json);
    // The file contains an array of entity objects.
		if (is_array($entities)) {
			foreach ($entities as $entity_array) {
				$entity = (object) $entity_array;
				_drush_entity_create_entity($entity_type, $entity);
			}
		}
    // The files has just one entity object.
		else {
			$entity = $entities;
			_drush_entity_create_entity($entity_type, $entity);
		}
  }
	else if ($file === '-') {
		drush_set_error('DRUSH_NO_STDIN', dt('stdin empty!'));
	}
	else {
		drush_set_error('DRUSH_EMPTY_FILE', dt('Empty file!'));
	}
}

/**
 * Helper function to create entities.
 *
 * @param $entity_type
 * @param $entity
 *
 */
function _drush_entity_create_entity($entity_type, $entity) {
	$entity_info = _drush_entity_get_info($entity_type);
	$eid = $entity_info['drush']['new'][0];

	if (_drush_entity_save($entity_type, $entity, TRUE)) {
		_drush_entity_print('', DRUSH_ENTITY_SEPARATED_SPACE, 'Entity created.');
	}
	elseif (isset($entity->$eid)) {
		_drush_entity_print(array($entity->$eid), DRUSH_ENTITY_SEPARATED_SPACE, 'Entity created.');
	}
	else {
		drush_set_error('DRUSH_ENTITY_CREATE_ERROR', dt('Failed to create entity!'));
	}
}

/**
 * Edit a string with the default shell editor.
 *
 * @param $string
 *
 * @return type
 */
function _drush_entity_edit_string($string) {
  $editor = getenv('EDITOR');
  if (empty($editor)) {
    drush_set_error('DRUSH_NO_EDITOR', dt('The environment variable EDITOR is not set'));
    return $string;
  }
  else {
    $file = drush_save_data_to_temp_file($string);
    drush_shell_exec_interactive('$EDITOR ' . $file);
    return file_get_contents($file, 'r');
  }
}

/**
 * Convert the drush options from a csv list into an array.
 *
 * @param $drush_option
 *  The drush option to invoke values from.
 *
 * @return
 *   Exploded array of options.
 */
function _drush_entity_explode_options($drush_option) {
  $options = drush_get_option($drush_option, array());
  if ($options) {
    return explode(',', $options);
  }
  return $options;
}

/**
 * @TODO
 */
function _drush_entity_get_exclude_fields() {
  $fields = drush_get_option('exclude-fields', '');
  // We always include 'drush' to exclude fields
  if (!$fields) {
    $fields = 'drush';
  }
  else {
    $fields .= ',drush';
  }
  $exclude_fields = explode(',', $fields);
  return array_diff($exclude_fields, _drush_entity_explode_options('fields'));
}

/**
 * Update given entity.
 *
 * @param $entity_type
 * @param $id
 *   A single entity ID.
 *
 */
function drush_entity_update($entity_type, $id) {
  $fields = _drush_entity_explode_options('fields');
  $entities = _drush_entity_load($entity_type, array($id));

  if (isset($entities[$id])) {
    $entity = $entities[$id];
    $input = drush_get_option('json-input', NULL);
    if ($input === '-') {
      $edited_obj_json = stream_get_contents(STDIN);
    }
    elseif (file_exists($input)) {
      drush_log("Reading file $input");
      $edited_obj_json = file_get_contents($input);
    }
    else {
      // Prepare to EDIT a json string
      if ($fields) {
        $entities_fields = _drush_entity_select_fields($entities, $fields, FALSE);
      }

      if ($fields) {
        $edit_obj = $entities_fields[$id];
      }
      else {
        $edit_obj = $entity;
      }
      $edited_obj_json = _drush_entity_edit_string(drush_json_encode($edit_obj));
    }

    // Prepare the changed entity to be saved
    if ($fields) {
      // Remap fields onto entity
      $edited_entity = $entity;
      $edited_fields = (object) drush_json_decode($edited_obj_json);
      foreach ($fields as $field) {
        $edited_entity->$field = $edited_fields->$field;
      }
    }
    else {
      $edited_entity = (object) drush_json_decode($edited_obj_json);
    }

    // Save
    _drush_entity_save($entity_type, $edited_entity);
  }
  else {
    drush_set_error('DRUSH_ENTITY_UPDATE_ERROR', dt('Entity to update not found!'));
  }
}

/**
 * Load entities with the given type and IDs.
 *
 * @param $entity_type
 * @param $ids
 *   An array of entity IDs.
 *
 * @return
 *   Array with entity objects.
 */
function _drush_entity_load($entity_type = NULL, array $ids = array()) {
  $entities = array();
  switch (drush_drupal_major_version()) {
    case 5:
    case 6:
      foreach ($ids as $id) {
        $entity = _drush_entity_op('load', $entity_type, $id);
        $entities[$id] = (object) $entity;
      }
    break;
    default:
      // This should always be the latest API core version.
      // For now both 7 and 8
      $entities = entity_load($entity_type, $ids);
    break;
  }
  return $entities;
}

/**
 * Entity delete command callback.
 *
 * @param $entity_type
 * @param $ids
 *   An array of entity IDs.
 */
function drush_entity_delete($entity_type = NULL, array $ids = array()) {
  $ids = func_get_args();
  $entity_type = array_shift($ids);
  $bundles = _drush_entity_explode_options('bundles');

  if (!isset($entity_type)) {
    drush_set_error('DRUSH_ENTITY_DELETE_ERROR', dt('You must specify an entity type'));
    return;
  }
  $info = _drush_entity_get_info($entity_type);
  if (!isset($info)) {
    drush_set_error('DRUSH_ENTITY_DELETE_ERROR', dt("Type '$entity_type' does not exist."));
    return;
  }

  if (!empty($ids)) {
    $result = _drush_entity_delete($entity_type, $ids);
    if (count($result) > 0) {
      $header = dt("Deleted $entity_type entities:");
      _drush_entity_print($result, DRUSH_ENTITY_SEPARATED_SPACE, $header);
    }
  }
  else {
    $ids = _drush_entity_id_list($entity_type, $bundles, FALSE);
    $bundle_list = $bundles ? implode(', ', $bundles) : NULL;
    if (!empty($ids) && drush_confirm(dt("Are you sure you want to delete all $entity_type $bundle_list entities?"))) {
      _drush_entity_delete($entity_type, $ids);
      drush_print(dt("All $entity_type entities deleted."));
    }
    elseif (empty($ids)) {
      drush_print(dt("There are no $entity_type entities to delete."));
    }
  }
}

/**
 * Save the given entity as a given type.
 *
 *
 * @param $entity_type
 *   The type of the entity.
 * @param $entity
 *   The entity to save.
 *
 * @return
 *   Depending on implementation and drupal version.
 *
 * @see entity_type_supports()
 */
function _drush_entity_save($entity_type, &$entity, $new = FALSE) {
  if ($new) {
    $entity_info = _drush_entity_get_info($entity_type);
    if (isset($entity_info['drush']['new'])) {
      foreach ($entity_info['drush']['new'] as $field) {
        unset($entity->$field);
      }
    }
  }

  return _drush_entity_op('save', $entity_type, $entity);
}

/**
 * Try running CRUD op on the given id or entity.
 *
 * This mimics from D7 Entity API entity.module but for all CRUD ops.
 *
 * @param $op
 *   Operation to perform. Supported ops are: save, delete, load.
 * @param $entity_type
 * @param $entity_or_id
 *   TODO: why by ref?
 *
 * @return type
 */
function _drush_entity_op($op, $entity_type, &$entity_or_id) {
  // TODO: We need to fix for D7 when $op == delete
  $op_alias = $op;
  if ($op == 'delete') {
    // D7 operator rename ..
    // TODO: is this changed ?
    $op_alias = 'deletion';
    // D6 user_delete requires two arguments
    if (drush_drupal_major_version() < 7 && $entity_type == 'user') {
      user_delete(array(), $entity_or_id);
      return;
    }
  }
  $info = _drush_entity_get_info($entity_type);

  // TODO: add comment
  if (isset($info['drush'][$op . ' needs'])) {
    switch ($info['drush'][$op . ' needs']) {
      case 'array':
        $entity_or_id = (array) $entity_or_id;
        break;
      case 'entity':
        $old = $entity_or_id;
        $entity_or_id = _drush_entity_load($entity_type, array($entity_or_id));
        if (empty($entity_or_id)) {
          drush_log("Unable to run $op on $entity_type : $old", 'warning');
          return;
        }
        break;
      default:
        break;
    }
  }
  if (method_exists($entity_or_id, $op)) {
    return $entity_or_id->$op();
  }
  elseif (isset($info[$op . ' callback'])) {
    return $info[$op . ' callback']($entity_or_id);
  }
  elseif (isset($info['controller class']) && in_array('EntityAPIControllerInterface', class_implements($info['controller class']))) {
    return entity_get_controller($entity_type)->$op($entity_or_id);
  }
  elseif (function_exists($entity_type . '_' . $op)) {
    $op_function = $entity_type . '_' . $op;
    // Fix user_save
    if ($op == 'save' && isset($info['drush']['save needs keys'])) {
      $keys = (array) $entity_or_id;
      return $op_function($entity_or_id, $keys);
    }
    else {
      return $op_function($entity_or_id);
    }
  }
  else {
    drush_log("Unable to $op the entity $entity_type. Maybe you could try to install and enable the entity.module");
    return FALSE;
  }
}

/**
 * Try to run _delete_multiple or otherwise iterate.
 *
 * @param $entity_type
 * @param $ids
 *   Array of entity IDs.
 *
 * @return
 *   The delete results per type implementation.
 */
function _drush_entity_delete($entity_type, array $ids = array()) {
  if ($entity_type == 'node') {
    // We want to use _delete_multiple
    return _drush_entity_delete_node($ids);
  }
  else {
    $result = array();
    foreach ($ids as $id) {
      $result[$id] = _drush_entity_op('delete', $entity_type, $id);
    }
  }

  return array_keys($result);
}

/**
 * This is special as we have node_delete_multiple
 *
 * The code for D6 is also special as cache_clear_all is only invoked in the end
 *
 * @param array $nids
 *  An array of node IDs.
 *
 * @return
 *   The drupal behaviour for the delete function used.
 */
function _drush_entity_delete_node(array $nids = array()) {
  if (drush_drupal_major_version() >= 7) {
    node_delete_multiple($nids);
    return $nids;
  }
  else {
    // Drupal 5/6
    // node-delete is implemented this way to prevent calling cache_clear_all() for each node.
    foreach ($nids as $nid) {
      $node = node_load($nid, NULL, TRUE);
      db_query('DELETE FROM {node} WHERE nid = %d', $nid);
      db_query('DELETE FROM {node_revisions} WHERE nid = %d', $nid);
      node_invoke($node, 'delete');
      node_invoke_nodeapi($node, 'delete');
      if (function_exists('search_wipe')) {
        search_wipe($node->nid, 'node');
      }
    }
    cache_clear_all();
  }
  
  return $nids;
}

/**
 * Wrapper for entity_info()
 *
 * We wrap entity_info to make D5/6 compatible.
 *
 * @param $entity_type
 *
 * @return
 *  An array of entity info.
 */
function _drush_entity_get_info($entity_type = NULL) {
  static $entities_info;

  if (!isset($entities_info)) {
    if (drush_drupal_major_version() < 7) {
      /*
       * Mapping for D6/5 which mimic D7 info structure
       */
      $entities_info = array(
        'node' => array(
          'label' => 'Node',
          'base table' => 'node',
          'entity keys' => array(
            'id' => 'nid',
            'revision' => 'vid',
            'label' => 'title',
          ),
          'bundles' => node_get_types('names'),
          'fieldable' => TRUE,
          'drush' => array(
            'defaults' => array(
              'type' => '',
              'title' => '',
            ),
            // What fields to zap for a new entity
            'new' => array('nid', 'vid'),
          ),
          'load list sql' => 'select nid as id from {node}',
        ),
        'user' => array(
          'label' => 'User',
          'base table' => 'users',
          'entity keys' => array(
            'id' => 'nid',
            'label' => 'name',
          ),
          'bundles' => array(),
          'fieldable' => FALSE,
          'drush' => array(
            'defaults' => array(
              'name' => '',
            ),
            // What fields to zap for a new entity
            'new' => array('uid'),
            // user_save needs list of keys
            'save needs keys' => TRUE,
          ),
          'load list sql' => 'select uid as id from {users}',
        ),
        'taxonomy_vocabulary' => array(
          'label' => 'Taxonomy vocabulary',
          'base table' => 'vocabulary',
          'entity keys' => array(
            'id' => 'nid',
            'label' => 'name',
          ),
          'bundles' => array(),
          'fieldable' => FALSE,
          'drush' => array(
            'defaults' => array(
              'name' => '',
            ),
            // What fields to zap for a new entity
            'new' => array('vid'),
          ),
          'load list sql' => 'select vid as id from {vocabulary}',
        ),
        'taxonomy_term' => array(
          'label' => 'Taxonomy term',
          'base table' => 'term_data',
          'entity keys' => array(
            'id' => 'nid',
            'label' => 'name',
          ),
          'bundles' => array(),
          'fieldable' => FALSE,
          'drush' => array(
            'defaults' => array(
              'name' => '',
            ),
            // What fields to zap for a new entity
            'new' => array('tid'),
            'save needs' => 'array',
          ),
          'load list sql' => 'select tid as id from {term_data}',
          'load callback' => 'taxonomy_get_term',
          'save callback' => 'taxonomy_save_term',
        ),
      );
      // Added entity counts
      foreach ($entities_info as $key => $info) {
        $table = db_escape_table($info['base table']);
        $entities_info[$key]['drush']['count'] = db_result(db_query("SELECT COUNT(*) FROM {{$table}}"));
      }
    }
    else {
      $entities_info = entity_get_info();
      foreach ($entities_info as $key => $info) {
        $entities_info[$key]['drush'] = array(
          'defaults' => array(),
        );
        $query = new EntityFieldQuery();
        $entities = $query->entityCondition('entity_type', $key)->execute();
        $entities_info[$key]['drush']['count'] = isset($entities[$key]) ? count($entities[$key]) : 0;

        if (drush_get_option('include-fieldapi', FALSE)) {
          // Add field related values
          foreach ($entities_info[$key]['bundles'] as $bundle => $dummy) {
            // Merge in the fields
            $field_info_instances = field_info_instances($key, $bundle);
            if ($field_info_instances) {
              $entities_info[$key]['field_info_instances'][$bundle] = $field_info_instances;
            }
            // Merge in the pseudo fields
            foreach (array('form', 'display') as $context) {
              $field_info_extra_fields = field_info_extra_fields($entity_type, $bundle, $context);
              if ($field_info_extra_fields) {
                $entities_info[$key]['field_info_extra_fields'][$bundle][$context] = $field_info_extra_fields;
              }
            }
          }
        }
      }
      // What keys to delete on create
      $entities_info['node']['drush']['new'] = array('nid', 'vid');
      $entities_info['user']['drush']['new'] = array('uid');
      $entities_info['file']['drush']['new'] = array('fid');

      // Defaults
      $entities_info['node']['drush']['defaults']['type'] = '';
      $entities_info['node']['drush']['defaults']['title'] = '';
      $entities_info['node']['drush']['defaults']['language'] = 'und';
      $entities_info['node']['drush']['defaults']['body'] = array(
        LANGUAGE_NONE => array(
          0 => array(
            'value' => '',
            'format' => filter_default_format(),
          ),
        ),
      );
      // To delete a file we need the file object
      $entities_info['file']['drush']['delete needs'] = 'entity';
    }
  }
  if (!empty($entity_type) && !empty($entities_info[$entity_type])) {
    return $entities_info[$entity_type];
  }
  elseif (!empty($entity_type) && !isset($entities_info[$entity_type])) {
    return;
  }

  return $entities_info;
}

/**
 * Print the given object depending on json switch
 *
 * @param $object
 * @param $format
 * @param $header
 */
function _drush_entity_print($object, $format = NULL, $header = '') {
  if ($format == DRUSH_ENTITY_SEPARATED_SPACE) {
    if ($header) {
      drush_print($header);
    }
    drush_print(implode(' ', (array) $object));
  }
  else {
    // Send it through drush_format.
    drush_print(drush_format($object, $header, $format));
  }
}

/**
 * Prevent D5/6 from invoking wrong types
 *
 * @param $type
 *   An entity type name to check.
 */
function _drush_entity_check_type($type) {
  switch (drush_drupal_major_version()) {
    case 5:
    case 6:
      $entity_info = _drush_entity_get_info();
      if (!isset($entity_info[$type])) {
        drush_set_error('DRUSH_ERROR', dt("No support for $type for drupal core < 7.x"));
      }
  }
}

/**
 * Helper to prevent recursion on objects
 *
 * @see drush_format_properties().
 *
 * @param type $cache
 *   Reference array
 * @param type $value
 *   A value of any kind.
 *
 * @return boolean
 *   The current $value is not an object or not visited yet.
 */
function _drush_entity_visit_object(&$object_hash_list, $value) {
  if (!is_array($object_hash_list)) {
    $object_hash_list = array();
  }
  if (is_object($value)) {
    $hash = spl_object_hash($value);
    if (isset($object_hash_list[$hash])) {
      return FALSE;
    }
    $object_hash_list[$hash] = $hash;
    return TRUE;
  }
  else if (is_array($value)) {
    return TRUE;
  }

  return FALSE;
}
