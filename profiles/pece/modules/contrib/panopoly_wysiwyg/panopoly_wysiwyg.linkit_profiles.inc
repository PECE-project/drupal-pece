<?php
/**
 * @file
 * panopoly_wysiwyg.linkit_profiles.inc
 */

/**
 * Implements hook_default_linkit_profiles().
 */
function panopoly_wysiwyg_default_linkit_profiles() {
  $export = array();

  $linkit_profile = new LinkitProfile();
  $linkit_profile->disabled = FALSE; /* Edit this to true to make a default linkit_profile disabled initially */
  $linkit_profile->api_version = 1;
  $linkit_profile->name = 'content_editors';
  $linkit_profile->admin_title = 'Content Editors';
  $linkit_profile->admin_description = '';
  $linkit_profile->profile_type = '1';
  $linkit_profile->data = array(
    'text_formats' => array(
      'panopoly_wysiwyg_text' => 'panopoly_wysiwyg_text',
      'panopoly_html_text' => 0,
      'plain_text' => 0,
    ),
    'search_plugins' => array(
      'entity:search_api_server' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:search_api_index' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:taxonomy_term' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
      'entity:node' => array(
        'enabled' => 1,
        'weight' => '0',
      ),
      'entity:file' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
      'entity:user' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
    ),
    'entity:node' => array(
      'result_description' => '[node:title]',
      'include_unpublished' => 0,
    ),
    'entity:search_api_server' => array(
      'result_description' => '',
      'include_unpublished' => 0,
    ),
    'entity:search_api_index' => array(
      'result_description' => '',
      'include_unpublished' => 0,
    ),
    'entity:file' => array(
      'result_description' => '',
      'bundles' => array(
        'image' => 0,
        'video' => 0,
        'audio' => 0,
        'document' => 0,
      ),
      'group_by_bundle' => 0,
      'show_scheme' => 0,
      'group_by_scheme' => 0,
      'image_extra_info' => array(
        'thumbnail' => 'thumbnail',
        'dimensions' => 'dimensions',
      ),
    ),
    'entity:taxonomy_term' => array(
      'result_description' => '',
    ),
    'entity:user' => array(
      'result_description' => '',
    ),
    'insert_plugin' => array(
      'url_method' => '2',
    ),
    'attribute_plugins' => array(
      'target' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'class' => array(
        'enabled' => 1,
        'weight' => '0',
      ),
      'id' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
      'title' => array(
        'enabled' => 1,
        'weight' => '0',
      ),
      'accesskey' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
      'rel' => array(
        'enabled' => 0,
        'weight' => '0',
      ),
    ),
    'autocomplete' => array(
      'charLimit' => '3',
      'wait' => '350',
      'remoteTimeout' => '10000',
    ),
  );
  $export['content_editors'] = $linkit_profile;

  return $export;
}
