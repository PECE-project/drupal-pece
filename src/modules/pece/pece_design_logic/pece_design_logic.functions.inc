<?php

/**
 * Ensures the existance of a design logic item.
 *
 * @param $name
 *   The kraftwagen itemname to use as unique id.
 *
 * @param $info
 *   Array with data for the item's fields.
 *
 * @return object
 *   An entity object or NULL if not found/not able to create.
 */
function pece_design_logic_ensure_item($name, $info) {
  module_load_include('inc', 'kw_itemnames');

  $item_id = kw_itemnames_name_get_item_id('design_logic', $name);
  $item = empty($item_id) ? null : kw_itemnames_item_load('design_logic', $item_id);

  if (!empty($item)) {
    return $item;
  }

  $item_values = array(
    'title' => $info['title'],
    'type' => 'design_logic',

    'field_description' => array(
      LANGUAGE_NONE => array(
        0 => array(
          'value' => $info['description'],
          'format' => 'panopoly_html_text',
        ),
      ),
    ),

    'field_image_credits' => array(
      LANGUAGE_NONE => array(
        0 => array(
          'title' => $info['link']['title'],
          'url' => $info['link']['url'],
        ),
      ),
    ),
  );

  // Add thumbnail if available.
  if (!empty($info['thumbnail'])) {
    $file = (object) array(
      'uid' => 1,
      'uri' => $info['thumbnail'],
      'filemime' => file_get_mimetype($info['thumbnail']),
      'status' => 1,
    );

    $item_values['field_thumbnail'] = array(
      LANGUAGE_NONE => array(
        0 => (array) file_copy($file, 'public://'),
      ),
    );
  }

  return kw_itemnames_ensure('design_logic', $name, array(), $item_values);
}
