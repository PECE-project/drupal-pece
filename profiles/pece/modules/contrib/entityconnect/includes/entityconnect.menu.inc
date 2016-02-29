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
  $css_id = "edit-" . str_replace('_', '-', $cache->data['field']);
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
  $content = array();
  $cache = entityconnect_cache_get($cache_id);
  $field = field_info_field($cache->data['field']);

  $entity_type = $cache->data['target_entity_type'];
  $acceptable_types = $cache->data['acceptable_types'];

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

        // If we have only one content-type defined,
        // go directly to the node form.
        if (sizeof($content) == 1) {
          $item = array_pop($content);
          drupal_goto($item['href']);
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
      $output = theme('entityconnect_entity_add_list', array(
        'cache id' => $cache_id,
        'items' => $content,
      ));
      $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      break;

    case 'user':
      $item['href'] = "admin/people/create/$cache_id";
      drupal_goto($item['href']);
      break;

    case 'taxonomy_term':
      $voc_list = array();

      if (count($acceptable_types) > 0) {
        foreach (taxonomy_get_vocabularies() as $key => $item) {
          $type = $item->machine_name;
          if (isset($acceptable_types[$type]) && $acceptable_types[$type]) {
            $item->href = "admin/structure/taxonomy/$type/add/$cache_id";
            $content[$key] = $item;
            $voc_list[] = l($item->name, $item->href);
          }
        }

        // If we have only one vocabulary defined,
        // go directly to the term add form.
        if (sizeof($content) == 1) {
          $item = array_pop($content);
          drupal_goto($item->href);
        }
      }
      else {
        foreach (taxonomy_get_vocabularies() as $key => $item) {
          !isset($item->href) ? $item->href = NULL : $item->href;
          $type = $item->machine_name;
          $item->href = "admin/structure/taxonomy/$type/add/$cache_id";
          $content[$key] = $item;
          $voc_list[] = l($item->name, $item->href);
        }
      }
      $output = theme('entityconnect_taxonomy_term_add_list', array('items' => $content));
      $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      break;

    case 'taxonomy_vocabulary':
      $item['href'] = "admin/structure/taxonomy/add/$cache_id";
      drupal_goto($item['href']);
      break;

    default:
      // Entity construction kit support.
      if (module_exists('eck')) {
        $entity_info = entity_get_info($entity_type);

        if (!empty($entity_info['module']) && $entity_info['module'] == 'eck') {
          // Only one allowed, no need for the intermediate step.
          if (count($acceptable_types) === 1) {
            $bundle_name = array_pop($acceptable_types);
            $bundle = $entity_info['bundles'][$bundle_name];
            drupal_goto($bundle['crud']['add']['path'] . "/$cache_id");
          }
          // All bundles allowed.
          elseif (count($acceptable_types) === 0) {
            foreach ($entity_info['bundles'] as $key => $bundle) {
              $content[$key]['href'] = $bundle['crud']['add']['path'] . "/$cache_id";
              $content[$key]['label'] = $bundle['label'];
            }
          }
          // Only certain bundles allowed.
          else {
            foreach ($acceptable_types as $bundle_name) {
              $bundle = $entity_info['bundles'][$bundle_name];
              $content[$bundle_name] = array(
                'href' => $bundle['crud']['add']['path'] . "/$cache_id",
                'label' => $bundle['label'],
                'description' => ''
              );
            }
          }
          $output = theme('entityconnect_entity_add_list', array(
            'cache id' => $cache_id,
            'items' => $content,
          ));
          $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
        }
      }

      // Bean support.
      if (module_exists('bean_admin_ui')) {
        if (count($acceptable_types) > 0) {
          foreach (bean_admin_ui_get_types() as $key => $item) {
            if (isset($acceptable_types[$key]) && $acceptable_types[$key]) {
              $type = str_replace("_", '-', $key);
              $content[$key] = array(
                'href' => "block/add/$type/$cache_id",
                'label' => $item->label,
                'description' => $item->description
              );
            }
          }

          // If we have only one content-type defined,
          // go directly to the node form.
          if (sizeof($content) == 1) {
            $item = array_pop($content);
            drupal_goto($item['href']);
          }
        }
        else {
          foreach (bean_admin_ui_get_types() as $key => $item) {
            $type = str_replace("_", '-', $key);
            $content[$key] = array(
              'href' => "block/add/$type/$cache_id",
              'label' => $item->label,
              'description' => $item->description
            );
          }
        }
        $output = theme('entityconnect_entity_add_list', array(
          'cache id' => $cache_id,
          'items' => $content,
        ));
        $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      }
      break;
  }
  return $output;
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
  $output = '';

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
        $output = theme('entityconnect_entity_add_list', array(
          'items' => $content,
          'cache id' => $cache_id)
        );
        $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      }
      else {
        drupal_goto("node/" . $cache->data['target_id'] . "/edit", array(
            'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
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
        $output = theme('entityconnect_entity_add_list', array(
          'items' => $content,
          'cache id' => $cache_id)
        );
        $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      }
      else {
        drupal_goto("user/" . $cache->data['target_id'] . "/edit", array(
            'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
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
        $output = theme('entityconnect_entity_add_list', array(
          'items' => $content,
          'cache id' => $cache_id)
        );
        $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      }
      else {
        drupal_goto("taxonomy/term/" . $cache->data['target_id'] . "/edit", array(
            'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
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
        $output = theme('entityconnect_entity_add_list', array(
          'items' => $content,
          'cache id' => $cache_id)
        );
        $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
      }
      else {
        $info = entity_load_single($entity_type, $target_id);
        drupal_goto("admin/structure/taxonomy/" . $info->name . "/edit", array(
            'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
      }
      break;

    default:
      // Support for entity construction kit.
      if (module_exists('eck')) {
        $entity_info = entity_get_info($entity_type);
        if ($entity_info['module'] == 'eck') {

          if (is_array($target_id)) {
            $eck_entities = entity_load($entity_type, $target_id);
            foreach ($eck_entities as $key => $eck_entity) {
              $crud_edit_path = preg_replace('/\%/', $key, $entity_info['bundles'][$eck_entity->type]['crud']['edit']['path']);
              $content[$key] = array(
                'label' => $eck_entity->title,
                'href' => $crud_edit_path,
                'description' => ''
              );
            }
            $output = theme('entityconnect_entity_add_list', array(
                'items' => $content,
                'cache id' => $cache_id)
            );
            $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
          }
          else {
            $eck_entity = entity_load_single($entity_type, $target_id);
            $crud_edit_path = preg_replace('/\%/', $target_id, $entity_info['bundles'][$eck_entity->type]['crud']['edit']['path']);
            drupal_goto($crud_edit_path, array(
              'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
          }
        }
      }

      // Support for Bean module..
      if (module_exists('bean_admin_ui')) {
        $entity_info = entity_get_info($entity_type);
        if ($entity_info['module'] == 'bean') {
          if (is_array($target_id)) {
            $info = entity_load($entity_type, $target_id);
            foreach ($info as $key => $value) {
              $content[$key] = array(
                'label' => $value->label,
                'href' => 'block/' . $value->delta . '/edit',
                'description' =>  ''
              );
            }
            $output = theme('entityconnect_entity_add_list', array(
                'items' => $content,
                'cache id' => $cache_id)
            );
            $output .= l(t('Cancel'), "admin/entityconnect/return/$cache_id");
          }
          else {
            $bean_entity = entity_load_single($entity_type, $target_id);
            drupal_goto("block/" . $bean_entity->delta . "/edit", array(
              'query' => array("build_cache_id" => $cache_id, "child" => TRUE)));
          }
        }
      }
      break;
  }
  return $output;
}
