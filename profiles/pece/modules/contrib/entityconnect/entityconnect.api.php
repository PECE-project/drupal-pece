<?php
/**
 * That file describes hooks provided by entityconnect.
 */


/**
 * hook_entityconnect_exclude_forms_alter().
 *
 * Allow modules to alter the list of exclude forms.
 * If you don't want a specific forms to be proceeded, or if Entityconnect affects
 *
 * @param $exclude_forms
 * @return array of forms that not be proceeded.
 *
 * @see entityconnect_child_form_alter()
 */
function hook_entityconnect_exclude_forms_alter(&$exclude_forms) {
  $exclude_forms = array(
    'search_block_form',
    'page_node_form'
  );
}
