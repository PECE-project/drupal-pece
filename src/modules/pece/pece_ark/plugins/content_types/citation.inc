<?php

$plugin = array(
  'single' => TRUE,
  'top level' => TRUE,
  'title' => t('Content citation'),
  'description' => t('Add citation on Essay page.'),
  'category' => t('PECE'),
  'render callback' => 'pece_ark_citation_pane_render',
  'all contexts' => TRUE,
  //'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'pece_ark_citation_pane_edit_form',
);

/**
 * An edit form for the pane's settings.
 */
function pece_ark_citation_pane_edit_form(&$form, &$form_state) {
  return $form;
}
/**
 * Submit callback for Essay link pane edit form.
 */
function pece_ark_citation_pane_edit_form_submit(&$form, &$form_state) {
  return $form;
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function pece_ark_citation_pane_render($subtype, $conf, $args, $context) {
  $node = $context['panelizer']->data;
  if (strpos($node->type, 'artifact') === false)
    return _citation_render($node);
  else
    return _artifact_citation_render($node);
}

function _citation_render($node) {
  module_load_include('inc', 'pece_profile', 'pece_profile.functions');
  // Prepare response block.
  $block = new stdClass();
  $ark_link = _citation_get_ark_link($node);
  // Define creators
  $creator = pece_get_fullname_or_name(user_load($node->uid));
  $contributors = isset($node->field_pece_contributors[LANGUAGE_NONE]) ? $node->field_pece_contributors[LANGUAGE_NONE] : array();
  $creator = _citation_create_many_names($contributors, $creator);
  $projectId = isset($node->field_pece_project_ref[LANGUAGE_NONE]) ? $node->field_pece_project_ref[LANGUAGE_NONE][0]['target_id'] : null;
  $projectName = '';
  if ($projectId) {
    $projectName = node_load($projectId);
    $projectName = $projectName->title . ',';
  }

  $block->content = array(
    'citation' => array(
      '#theme' => 'html_tag',
      '#tag' => 'p',
      '#value' => t('@creator. @dateCreated, "@title", <i>@projectName @siteName, Platform for Experimental Collaborative Ethnography<i>, last modified @changed, accessed @accessed@ark', array(
        '@creator' => $creator,
        '@projectName' => $projectName,
        '@dateCreated' => format_date($node->created, 'custom', 'j F Y'),
        '@title' => $node->title,
        '@siteName' => variable_get('site_name'),
        '@ark' => $ark_link,
        '@changed' => format_date($node->changed, 'custom', 'j F Y'),
        '@accessed' => date('j F Y')
      )),
      '#attributes' => array(
        'class' => array('citation'),
      ),
    ),
  );

  return $block;
}

function _artifact_citation_render($node) {
  module_load_include('inc', 'pece_profile', 'pece_profile.functions');
  // Prepare response block.
  $block = new stdClass();
  $ark_link = _citation_get_ark_link($node);
  // Define contributor
  $contributor = '';
  // Define creators
  $creators = isset($node->field_pece_authors[LANGUAGE_NONE]) ? $node->field_pece_authors[LANGUAGE_NONE] : array();

  if (count($creators)) {
    $creators = _citation_create_many_names_authors($creators);
    $contributor = pece_get_fullname_or_name(user_load($node->uid));
  }
  else {
    $creators = pece_get_fullname_or_name(user_load($node->uid));
  }

  $contributors = isset($node->field_pece_contributors[LANGUAGE_NONE]) ? $node->field_pece_contributors[LANGUAGE_NONE] : array();
  $contributors = _citation_create_many_names($contributors, $contributor);

  $dateCreated =  isset($node->field_pece_created[LANGUAGE_NONE]) ? date('j F Y', strtotime($node->field_pece_created[LANGUAGE_NONE][0]['value'])) . ',' : '';
  $projectId = isset($node->field_pece_project_ref[LANGUAGE_NONE]) ? $node->field_pece_project_ref[LANGUAGE_NONE][0]['target_id'] : null;
  $projectName = '';
  if ($projectId) {
    $projectName = node_load($projectId);
    $projectName = $projectName->title . ',';
  }

  $block->content = array(
    'citation' => array(
      '#theme' => 'html_tag',
      '#tag' => 'p',
      '#value' => t('@creator, @dateCreated "@title", contributed by @contributors, <i>@projectName @siteName, Platform for Experimental Collaborative Ethnography</i>, last modified @changed, accessed @accessed@ark', array(
        '@creator' => $creators,
        '@projectName' => $projectName,
        '@title' => $node->title,
        '@dateCreated' => $dateCreated,
        '@contributors' => $contributors,
        '@siteName' => variable_get('site_name'),
        '@ark' => $ark_link,
        '@changed' => format_date($node->changed, 'custom', 'j F Y'),
        '@accessed' => date('j F Y')
      )),
      '#attributes' => array(
        'class' => array('citation'),
      ),
    ),
  );

  return $block;
}

/**
 * Helper to return link to ark.
 * @param $node
 *
 * @return string
 */
function _citation_get_ark_link($node) {
  $ark_link = '.';
  $ark = pece_ark_get_data($node);
  if ($ark && $ark['remote_ark_name'] != '')
    $ark_link = ', ' .$ark['remote_ark_name']. '.';

  return $ark_link;
}

/**
 * Helper to transform list name uid in string citations
 * @param $user_list
 * @param string $names
 */
function _citation_create_many_names($user_list, $names = '') {
  for ($cont = 0; $cont < count($user_list); $cont++) {
    // Test if use 'and' or ',' to separate creators.
    if ($names != '') {
      if ($cont + 1 == count($user_list))
        $names .= ' and ';
      elseif ($names != '')
        $names .= ', ';
    }

    $names .= pece_get_fullname_or_name(user_load($user_list[$cont]['target_id']));
  }
  return $names;
}

function _citation_create_many_names_authors($authors_list) {
  foreach ($authors_list as $key => $author) {
    $authors_list[$key] =  $author['tid'];
  }

  $authors = taxonomy_term_load_multiple($authors_list);
  $cont = 1;
  $names = '';
  foreach ($authors as $auth) {
    $names .= $auth->name;

    if ($cont + 1 == count($authors))
      $names .= ' and ';
    elseif ($cont + 1 < count($authors))
      $names .= ', ';

    $cont++;
  }

  return $names;
}
