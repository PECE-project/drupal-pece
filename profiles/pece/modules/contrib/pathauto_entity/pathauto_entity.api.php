<?php

/**
 * @file
 * Documentation for pathauto_entity API.
 *
 * @see hook_token_info
 * @see hook_tokens
 */

/**
 * Modify the list of supported entity types.
 */
function hook_pathauto_entity_supported_entity_types_alter(&$entity_infos) {
}

/**
 * Allows you to define a key => value array of entity forms.
 * This will allow the "URL path settings" to appear on the entity form defined here.
 */
function hook_pathauto_entity_alias_settings_alter(&$entity_forms) {
  $entity_forms += array(
    'entity_type' => 'form_id',
    'entity_type' => 'form_id',
  );
}
