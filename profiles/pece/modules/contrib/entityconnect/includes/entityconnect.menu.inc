<?php
/**
 * @file
 * Handles all entityconnect menu item page callbacks.
 */

/**
 * Page callback: Redirects to the form page.
 *
 * We redirect to the form page with the build_cache_id as a get param.
 */
function entityconnect_return($cache_id) {
  $cache = entityconnect_cache_get($cache_id);
  $css_id = $cache->data['form_state']['clicked_button']['#id'];
  $options = array('query' => array(
              'build_cache_id' => $cache_id,
              'return' => TRUE),
            'fragment' => $css_id);
  //Collect additional request parameters, skip 'q', since this is the destination
  foreach ($cache->data['params'] as $key => $value) {
    if ('build_cache_id' == $key) {
      continue;
    }
    $options['query'][$key] = $value;
  }

  drupal_goto($cache->data['dest'], $options);
}

/**
 * Page callback: Load cached form info.
 *
 * This page will load the cached form info, and display links to each of the
 * entityreference types.
 * If there is only one it will redirect to that page.
 *
 * This is mostly a copy and hack up of the node add page.
 *
 * This page is directed to from the entityconnect_add_button_submit.
 */
function entityconnect_add($cache_id) {
  $cache = entityconnect_cache_get($cache_id);
  $entity_type = $cache->data['target_entity_type'];
  $acceptable_types = $cache->data['acceptable_types'];

  $add_info = module_invoke_all('entityconnect_add_info', $cache_id, $entity_type, $acceptable_types);

  // Merge in default values.
  foreach ($add_info as $name => $data) {
    $add_info += array(
      'content' => array(
        'href' => '',
        'label' => '',
        'description' => ''
      ),
      'theme_callback' => 'entityconnect_entity_add_list',
    );
  }

  $context = array(
    'cache_id' => $cache_id,
    'entity_type' => $entity_type,
    'acceptable_tpes' => $acceptable_types
  );
  drupal_alter('entityconnect_add_info', $add_info, $context);

  if (isset($add_info)) {
    $content = $add_info['content'];
    $theme = $add_info['theme_callback'];
  }

  // If we have only one content-type defined,
  // go directly to the node form.
  if (count($content) == 1) {
    $item = array_pop($content);
    // Cast every item as array.
    // That allow both object or array to be treated the same way.
    $item = (array) $item;
    drupal_goto($item['href']);
  }

  $output = theme($theme, array(
    'cache id' => $cache_id,
    'items' => $content,
  ));
  $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");

  return $output;
}

/**
 * Implements hook_entityconnect_add_info().
 */
function entityconnect_entityconnect_add_info($cache_id, $entity_type, $acceptable_types) {
  if (!isset($entity_type)) {
    throw new \Exception(t('Entity type can not be empty'));
  }

  switch ($entity_type) {
    case 'node':
      if (count($acceptable_types) > 0) {
        foreach (node_type_get_types() as $key => $item) {
          if (isset($acceptable_types[$key]) && $acceptable_types[$key]) {
            $type = str_replace("_", '-', $key);
            $content[$key] = array(
              'href' => "node/add/$type/$cache_id",
              'label' => $item->name,
              'description' => $item->description
            );
          }
        }
      }
      else {
        foreach (node_type_get_types() as $key => $item) {
          $type = str_replace("_", '-', $key);
          $content[$key] = array(
            'href' => "node/add/$type/$cache_id",
            'label' => $item->name,
            'description' => $item->description
          );
        }
      }
      break;

    case 'user':
      $content[$entity_type]['href'] = "admin/people/create/$cache_id";
      break;

    case 'taxonomy_term':
      if (count($acceptable_types) > 0) {
        foreach (taxonomy_get_vocabularies() as $key => $item) {
          $type = $item->machine_name;
          if (isset($acceptable_types[$type]) && $acceptable_types[$type]) {
            $item->href = "admin/structure/taxonomy/$type/add/$cache_id";
            $content[$key] = $item;
          }
        }
      }
      else {
        foreach (taxonomy_get_vocabularies() as $key => $item) {
          !isset($item->href) ? $item->href = NULL : $item->href;
          $type = $item->machine_name;
          $item->href = "admin/structure/taxonomy/$type/add/$cache_id";
          $content[$key] = $item;
        }
      }
      $theme_callback = 'entityconnect_taxonomy_term_add_list';
      break;

    case 'taxonomy_vocabulary':
      $content[$entity_type]['href'] = "admin/structure/taxonomy/add/$cache_id";
      break;

    default:
      break;
  }

  if (isset($content)) {
    if (isset($theme_callback)) {
      return array(
        'content' => $content,
        'theme_callback' => $theme_callback,
      );
    }
    else {
      return array(
        'content' => $content,
      );
    }
  }
}

/**
 * Page callback: Redirect to edit form.
 *
 * We use this to redirect to a edit form but pass the build_cache_id.
 */
function entityconnect_edit($cache_id) {
  $cache = entityconnect_cache_get($cache_id);
  $entity_type = $cache->data['target_entity_type'];
  $target_id = $cache->data['target_id'];

  $edit_info = module_invoke_all('entityconnect_edit_info', $cache_id, $entity_type, $target_id);

  // Merge in default values.
  foreach ($edit_info as $name => $data) {
    $edit_info += array(
      'content' => array(
        'href' => '',
        'label' => '',
        'description' => ''
      ),
      'theme_callback' => 'entityconnect_entity_add_list',
    );
  }

  $context = array(
    'cache_id' => $cache_id,
    'entity_type' => $entity_type,
    'target_id' => $target_id
  );
  drupal_alter('entityconnect_edit_info', $edit_info, $context);

  if (isset($edit_info)) {
    $content = $edit_info['content'];
    $theme = $edit_info['theme_callback'];
  }

  if (count($content) == 1) {
    $item = array_pop($content);
    if (is_array($item['href'])) {
      $href= array_shift($item['href']);
    }
    else {
      $href = $item['href'];
    }
    drupal_goto($href, array(
      'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
  }

  $output = theme($theme, array(
    'cache id' => $cache_id,
    'items' => $content,
  ));
  $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");

  return $output;
}

/**
 * Implements hook_entityconnect_edit_info().
 */
function entityconnect_entityconnect_edit_info($cache_id, $entity_type, $target_id) {

  if (!isset($entity_type)) {
    throw new \Exception(t('Entity type can not be empty'));
  }

  if (!isset($target_id)) {
    throw new \Exception(t('Target_id can not be empty'));
  }

  switch ($entity_type) {
    case 'node':
      if (is_array($target_id)) {
        $info = entity_load($entity_type, $target_id);
        foreach ($info as $key => $value) {
          $content[$key] = array(
            'label' => $value->title,
            'href' => 'node/' . $value->nid . '/edit',
            'description' =>  ''
          );
        }
      }
      else {
        $content[$entity_type]['href'] = "node/$target_id/edit";
      }
      break;

    case 'user':
      if (is_array($target_id)) {
        $info = entity_load($entity_type, $target_id);
        foreach ($info as $key => $value) {
          $content[$key] = array(
            'label' => $value->name,
            'href' => 'user/' . $value->uid . '/edit',
            'description' => ''
          );
        }
      }
      else {
        $content[$entity_type]['href'] = "user/$target_id/edit";
      }
      break;

    case 'taxonomy_term':
      if (is_array($target_id)) {
        $info = entity_load($entity_type, $target_id);
        foreach ($info as $key => $value) {
          $content[$key] = array(
            'label' => $value->name,
            'href' => 'taxonomy/term/' . $value->tid . '/edit',
            'description' => ''
          );
        }
      }
      else {
        $content[$entity_type]['href'] = "taxonomy/term/$target_id/edit";
      }
      break;

    case 'taxonomy_vocabulary':
      if (is_array($target_id)) {
        $info = entity_load($entity_type, $target_id);
        foreach ($info as $key => $value) {
          $content[$key] = array(
            'label' => $value->name,
            'href' => 'admin/structure/taxonomy/' . $value->name . '/edit',
            'description' => ''
          );
        }
      }
      else {
        $info = entity_load_single($entity_type, $target_id);
        $content[$entity_type]['href'] = "admin/structure/taxonomy/$info->name/edit";
      }
      break;

    default:
      break;
  }

  if (isset($theme_callback)) {
    return array(
      'content' => $content,
      'theme_callback' => $theme_callback,
    );
  }
  else {
    return array(
      'content' => $content,
    );
  }
}
