<?php

/**
 * @file
 * Functions related to Ark indexing operations.
 */


/**
 * Form builder function to allow choice of which batch to run.
 */
function pece_ark_batches_form() {

  $form['description'] = array(
    '#type' => 'markup',
    '#markup' => t('Select the batch operation'),
  );
  $form['batch'] = array(
    '#type' => 'select',
    '#title' => 'Choose batch',
    '#options' => array(
      'pece_ark_batch_for_local_ark_data_creation' => t('Generate Ark data for all ARK content types selected'),
      'pece_ark_batch_for_remote_data_update' => t('Update Ark remote data for all ARK content types selected'),
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Go',
  );

  // If no nodes, prevent submission.
  // Find out if we have a node to work with. Otherwise it won't work.
  $nids = _get_all_node_ids_for_selected_ark_node_types();
  $remote_status = variable_get('ark_ezid_remote_status', ARK_DEFAULT_REMOTE_STATUS_ENTRY_VALUE);
  $username = variable_get('ark_ezid_user');
  $password = variable_get('ark_ezid_password');
  if (empty($nids)) {
    drupal_set_message(t("You don't currently have any nodes for the selected ARK content types, and this batch requires at least one node to process. As a result, this form is disabled."));
    $form['submit']['#disabled'] = TRUE;
  }
  if (empty($username)) {
    drupal_set_message(t("You don't set the username to connect to the remote sever under the ") . l(t('Ark Module Settings page'), '/admin/config/services/ark/ark') . ". As a result, this form is disabled.");
    $form['submit']['#disabled'] = TRUE;
  }
  if (empty($password)) {
    drupal_set_message(t("You don't set the password to connect to the remote sever under the ") . l(t('Ark Module Settings page'), '/admin/config/services/ark/ark') . ". As a result, this form is disabled.");
    $form['submit']['#disabled'] = TRUE;
  }
  if (empty($remote_status)) {
    drupal_set_message(t("You don't set the default status to the new entries for the remote sever under the ") . l(t('Ark Module Settings page'), 'admin/config/services/ark/remote_update_settings') . ". As a result, this form is disabled.");
    $form['submit']['#disabled'] = TRUE;
  }
  return $form;
}

function pece_ark_remote_update_settings_form() {

  $form['ark_ezid_remote_status_explanation'] = array(
    '#type' => 'fieldset',
    '#title' => t('EZID Remote Status field'),
    '#weight' => 0,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' =>
      '<div>
        <h2>' . t('Identifier status') . '</h2>
        <p>' . t('Each identifier in EZID has a status.  The status is recorded as the value of the "_status" reserved metadata element (see <a class="reference internal" href="https://ezid.cdlib.org/doc/apidoc.html#internal-metadata">Internal metadata</a> on EZid site) and may be one of:') . '</p>
        <dl>
          <dt><strong>' . t('public') . '</strong></dt>
          <dd>' . t('The default value.') . '</dd>
          <dt><strong>' . t('reserved') . '</strong></dt>
          <dd>' . t('The identifier is known only to EZID.  This status may be used to reserve an identifier name within EZID without advertising the identifier\'s existence to resolvers and other external services. A reserved identifier may be deleted.') . '</dd>
          <dt><strong>' . t('unavailable') . '</strong></dt>
          <dd>'
          . t('The identifier is public, but the object referenced by the identifier is not available.  A reason for the object\'s unavailability may optionally follow the status separated by a pipe character ("|", U+007C), e.g., "unavailable | withdrawn by author".')
          . t('The identifier redirects to an EZID-provided "tombstone" page (an HTML page that displays the identifier\'s citation metadata and the reason for the object\'s unavailability) regardless of its target URL.') .
          '</dd>
        </dl>
        <p>' . t('An identifier\'s status may be changed by setting a new value for the aforementioned "_status" metadata element.  EZID permits only certain status transitions:') . '</p>
        <ul>
          <li>' . t('A status of "reserved" may be specified only at identifier creation time.') . '</li>
          <li>' . t('A reserved identifier may be made public.  At this time the identifier will be registered with resolvers and other external services.') . '</li>
          <li>' . t('A public identifier may be marked as unavailable.  At this time the identifier will be removed from resolvers and external services to the extent possible.') . '</li>
          <li>' . t('An unavailable identifier may be returned to public status.  At this time the identifier will be re-registered with resolvers and other external services.') . '</li>
        </ul>
      </div>'
  );

  $form['ark_ezid_remote_status_explanation']['ark_ezid_remote_status'] = array(
    '#type' => 'textfield',
    '#title' => t('The default value for status field when creating a new remote entry.'),
    '#description' => '<strong>' . t('PLEASE DO NOT CHANGE THIS VALUE IF YOU DON\'T KNOW WHAT IT MEANS!!!') . '</strong>',
    '#default_value' => variable_get( 'ark_ezid_remote_status', ARK_DEFAULT_REMOTE_STATUS_ENTRY_VALUE),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['ark_ezid_remote_status_explanation']['ark_ezid_remote_export'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Determines if the identifier is publicized by exporting it to external indexing and harvesting services. Default is checked.'),
    '#description' => '<strong>' . t('PLEASE DO NOT CHANGE THIS VALUE IF YOU DON\'T KNOW WHAT IT MEANS!!!') . '</strong>',
    '#options' => array(
      'yes' => t('Allow harvesting/indexing.'),
    ),
    '#default_value' => variable_get( 'ark_ezid_remote_export', ARK_DEFAULT_REMOTE_EXPORT_ENTRY_VALUE ),
  );

  $form['ark_ezid_remote_status_explanation']['ark_ezid_update_if_exists'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Update remote ARK entry if already exist. If not, create a new one.'),
    '#options' => array(
      '1' => t('Update remote ARK entry if already exist. If not, create a new one.'),
    ),
    '#default_value' => variable_get( 'ark_ezid_update_if_exists', ARK_DEFAULT_REMOTE_UPDATE_IF_EXISTS ),
  );

  return system_settings_form($form);
}

/**
 * Submit handler.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form.
 */
function pece_ark_batches_form_submit($form, &$form_state) {
  $function = $form_state['values']['batch'];

  if ( $form_state['values']['batch'] == 'pece_ark_batch_for_remote_data_update') {
    if(empty(variable_get('ark_ezid_user')) || empty(variable_get('ark_ezid_password'))) {
      form_set_error('batch', t('Values for ark_ezid_user or ark_ezid_password may be empty. Please set it in the ') . l(t('Ark Module Settings page'), '/admin/config/services/ark/ark')) ;
    }
  }

  // Reset counter for debug information.
  $_SESSION['http_request_count'] = 0;
  $batch = $function();

  batch_set($batch);
}

/**
 * Batch definition that will generate local ARK data.
 */
function pece_ark_batch_for_local_ark_data_creation() {

  // Give helpful information about how many nodes are being operated on.
  $node_count = count(_get_all_node_ids_for_selected_ark_node_types());
  drupal_set_message(
    t('There are @node_count nodes to be processed, so it will require @count requests.',
      array(
        '@node_count' => $node_count,
        '@count' => ceil($node_count / variable_get('ark_indexing_limit', ARK_INDEXING_LIMIT)),
      )
    )
  );

  $operations[] = array(
    'pece_ark_operation_for_local_ark_data_creation',
    array(),
  );
  $batch = array(
    'operations' => $operations,
    'finished' => 'pece_ark_operation_for_local_ark_data_creation_finished',
    // Message displayed while processing the batch. Available placeholders are:
    // @current, @remaining, @total, @percentage, @estimate and @elapsed.
    // These placeholders are replaced with actual values in _batch_process(),
    // using strtr() instead of t().
    // Defaults to t('Completed @current of @total.').
    'title' => t('Creating local ARK URL for the selected content types'),
    'init_message' => t('Preparing to submit content to ARK URL creation...'),
    'progress_message' => t('Creating ARK URLs ...'),
    'error_message' => t('ARK URL creation  has encountered an error.'),
    'file' => drupal_get_path('module', 'pece_ark') . '/pece_ark.batches.inc',
  );
  return $batch;
}

/**
 * Batch definition to update remote ARK data.
 */
function pece_ark_batch_for_remote_data_update() {

  // Give helpful information about how many nodes are being operated on.
  $node_count = count(_get_all_node_data_for_remote_update());
  drupal_set_message(
    t('There are @node_count nodes configured to update remote ARK data to be processed, so it will require @count requests.',
      array(
        '@node_count' => $node_count,
        '@count' => ceil($node_count / variable_get('ark_indexing_limit', ARK_INDEXING_LIMIT)),
      )
    )
  );

  $operations[] = array(
    'pece_ark_operation_for_remote_ark_data_update',
    array(),
  );
  $batch = array(
    'operations' => $operations,
    'finished' => 'pece_ark_operation_for_remote_ark_data_update_finished',
    // Message displayed while processing the batch. Available placeholders are:
    // @current, @remaining, @total, @percentage, @estimate and @elapsed.
    // These placeholders are replaced with actual values in _batch_process(),
    // using strtr() instead of t().
    // Defaults to t('Completed @current of @total.').
    'title' => t('Updating remote ARK data for the existent local ark data'),
    'init_message' => t('Preparing to submit ARK data to remote server...'),
    'progress_message' => t('Updating remote data...'),
    'error_message' => t('Remote data update has encountered an error.'),
    'file' => drupal_get_path('module', 'pece_ark') . '/pece_ark.batches.inc',
  );
  return $batch;
}

/**
 * Batch operation for pece_ark_batch_for_local_ark_data_creation
 *
 * After each group of ARK_INDEXING_LIMIT (default by module 50) control is returned to the batch API for later
 * continuation.
 *
 *
 */
function pece_ark_operation_for_local_ark_data_creation(&$context) {
  module_load_include('module', 'pece_ark');
  module_load_include('inc', 'pece_ark', 'pece_ark.batches');

  module_load_include('module', 'pece_profile');
  module_load_include('inc', 'pece_profile', 'pece_profile.functions');
  // Use the $context['sandbox'] at your convenience to store the
  // information needed to track progression between successive calls.
  $were_ark_nodes = _get_were_clause_for_selected_ark_node_types();

  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;

    // Save node count for the termination message.
    if ($were_ark_nodes) {
      $node_ids = _get_all_node_ids_for_selected_ark_node_types();
      if ($node_ids) {
        $context['sandbox']['max'] = count($node_ids);
      }
    }
  }

  // Process nodes by groups of ARK_INDEXING_LIMIT (default by module 50).
  // When a group of five is processed, the batch update engine determines
  // whether it should continue processing in the same request or provide
  // progress feedback to the user and wait for the next request.
  // That way even though we're already processing at the operation level
  // the operation itself is interruptible.
  $limit = variable_get('ark_indexing_limit', ARK_INDEXING_LIMIT);

  // Retrieve the next group of nids.
  $result = db_select('node', 'n')
            ->fields('n', array('nid'))
            ->orderBy('n.nid', 'ASC')
            ->where("$were_ark_nodes AND (n.nid > :nid)", array(':nid' => $context['sandbox']['current_node']))
            ->extend('PagerDefault')
            ->limit($limit)
            ->execute();

  foreach ($result as $row) {
    // Here we actually perform our dummy 'processing' on the current node.
    $node = node_load($row->nid, NULL, TRUE);
    pece_ark_data_save($node);
    // Store some results for post-processing in the 'finished' callback.
    // The contents of 'results' will be available as $results in the
    // 'finished' function (in this example, batch_example_finished()).
    $context['results'][] = 'ARK data for nid: ' . $node->nid . ', Title "' . check_plain($node->title) . '" processed';

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $node->nid;
    $context['message'] = check_plain($node->title);
    $context['message'] = t('Generating ARK data for node "@title" (nid:@nid)', array('@title' => $node->title, '@nid' => $node->nid));
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
  _batch_ark_update_http_requests();
}

/**
 * Batch operation for ark_operation_for_remote_ark_data_update
 *
 * After each group of ARK_INDEXING_LIMIT (default by module 50) control is returned to the batch API for later
 * continuation.
 *
 *
 */
function pece_ark_operation_for_remote_ark_data_update(&$context) {
  module_load_include('module', 'pece_ark');
  module_load_include('inc', 'pece_ark', 'pece_ark.batches');

  module_load_include('module', 'pece_profile');
  module_load_include('inc', 'pece_profile', 'pece_profile.functions');
  // Use the $context['sandbox'] at your convenience to store the
  // information needed to track progression between successive calls.

  if (empty($context['sandbox'])) {
    $context['sandbox'] = array();
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;

    $nodes_data = _get_all_node_data_for_remote_update();
    if ($nodes_data) {
      $context['sandbox']['max'] = count($nodes_data);
    }
  }

  // Process nodes by groups of ARK_INDEXING_LIMIT (default by module 50).
  // When a group of five is processed, the batch update engine determines
  // whether it should continue processing in the same request or provide
  // progress feedback to the user and wait for the next request.
  // That way even though we're already processing at the operation level
  // the operation itself is interruptible.
  $limit = variable_get('ark_indexing_limit', ARK_INDEXING_LIMIT);

  // Retrieve the next group of nids.
  $result = array();
  $query = db_select('ark_map', 'am');
  $query->join('node' , 'n', 'am.entity_id = n.nid');
  $query->fields('am' , array('ark_name', 'ark_who', 'ark_when'));
  $query->fields('n'  , array('nid', 'title'));
  $query->orderBy('n.nid', 'ASC');
  $query->where('(am.pending_remote_update = :cond) AND (n.nid > :nid)', array(':cond' => 1, ':nid' => $context['sandbox']['current_node']));
  $query->extend('PagerDefault');
  $result = $query->execute()->fetchAll(PDO::FETCH_ASSOC);

  if (count($result)) {
    foreach ($result as $key => $data) {
      $current_status = false;
      // Here we actually perform our dummy 'processing' on the current node.
      $current_status = pece_ark_remote_data_update($data);
      // Store some results for post-processing in the 'finished' callback.
      // The contents of 'results' will be available as $results in the
      // 'finished' function (in this example, batch_example_finished()).
      if ($current_status) {
        $context['results']['successfully_processed'][] = 'Remote ARK data for nid:' . $data['nid'] . ', Title: ' . check_plain($data['title']) . ' successfully processed';
      } else {
        $context['results']['fail_processed'][] = 'Remote ARK data for nid:' . $data['nid'] . ', Title: ' . check_plain($data['title']) . ' failed during the process';
      }


      // Update our progress information.
      $context['sandbox']['progress']++;
      $context['sandbox']['current_node'] = $data['nid'];
      $context['message'] = check_plain($data['title']);
      $context['message'] = t('Updating Remote ARK data for node "@title" (nid:@nid)', array('@title' => $data['title'] , '@nid' => $data['nid']));
    }
  }



  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = ($context['sandbox']['progress'] >= $context['sandbox']['max']);
  }
  _batch_ark_update_http_requests();
}

/**
 * Batch 'finished' callback .
 */
function pece_ark_operation_for_local_ark_data_creation_finished($success, $results, $operations) {
  if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _batch_ark_get_http_requests())));
    drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(
      t('An error occurred while processing @operation with arguments : @args',
        array(
          '@operation' => $error_operation[0],
          '@args' => print_r($error_operation[0], TRUE),
        )
      ),
      'error'
    );
  }
}

/**
 * Batch 'finished' callback .
 */
function pece_ark_operation_for_remote_ark_data_update_finished($success, $results, $operations) {
  if ($success) {
    dd('$results: ');
    dd(print_r($results));
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _batch_ark_get_http_requests())));
    drupal_set_message(t('The final result was "%final"', array('%final' => end($results['successfully_processed']))));

    if ( !empty($results['fail_processed']) ) {
      drupal_set_message(t('Folowing data failed to be processed'), 'error');
      foreach( $results['fail_processed'] as $failed_row) {
        drupal_set_message($failed_row, 'error');
      }
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(
      t('An error occurred while processing @operation with arguments : @args',
        array(
          '@operation' => $error_operation[0],
          '@args' => print_r($error_operation[0], TRUE),
        )
      ),
      'error'
    );
  }
}

/**
 * Utility function to increment HTTP requests in a session variable.
 */
function _batch_ark_update_http_requests() {
  $_SESSION['http_request_count']++;
}

/**
 * Utility function to count the HTTP requests in a session variable.
 *
 * @return int
 *   Number of requests.
 */
function _batch_ark_get_http_requests() {
  return !empty($_SESSION['http_request_count']) ? $_SESSION['http_request_count'] : 0;
}

function _get_were_clause_for_selected_ark_node_types(){
  $ark_node_types = variable_get('ark_node_types');
  $were_ark_nodes = NULL;
  if ($ark_node_types) {
    $array_were_ark_node_types = array();

    foreach ($ark_node_types as $key => $node_type) {
      array_push($array_were_ark_node_types, "(type = '$node_type')");
    }
    $were_ark_nodes  = (count($array_were_ark_node_types) > 1) ? implode(' OR ', $array_were_ark_node_types) : implode('', $array_were_ark_node_types);
    $were_ark_nodes .= ' AND (status = 1)';
  }
  return $were_ark_nodes;
}

function _get_all_node_ids_for_selected_ark_node_types() {
  $result = array();
  $were_ark_nodes = _get_were_clause_for_selected_ark_node_types();
  if ($were_ark_nodes) {
    $node_ids = db_select('node', 'n')
                ->fields('n', array('nid'))
                ->orderBy('n.nid', 'ASC')
                ->where("$were_ark_nodes")
                ->extend('PagerDefault')
                ->execute()->fetchCol('nid');
    if ($node_ids) {
      $result = $node_ids;
    }
  }
  return $result;
}

function _get_all_ark_enabled_content_nids() {
  $result = array();
  $were_ark_nodes = _get_were_clause_for_selected_ark_node_types();
  $query = db_select('node', 'n');
  $query->innerJoin('field_data_field_ark_enabled', 'fdata', 'fdata.entity_id = n.nid');
  $query->fields('n'  , array('nid'));
  $query->where("$were_ark_nodes");
  $query->where("field_ark_enabled_value = 1");
  $query->orderBy('n.nid', 'ASC');
  $query->extend('PagerDefault');
  $result = $query->execute()->fetchAllAssoc('nid',PDO::FETCH_ASSOC);
  return $result;
}

function _get_all_node_data_for_remote_update() {
  $result = array();
  $query = db_select('ark_map', 'am');
  $query->join('node' , 'n', 'am.entity_id = n.nid');
  $query->fields('am' , array('ark_name', 'ark_who', 'ark_when'));
  $query->fields('n'  , array('nid', 'title'));
  $query->orderBy('n.nid', 'ASC');
  $query->where('am.pending_remote_update = :cond', array(':cond' => 1));
  $query->extend('PagerDefault');
  $result = $query->execute()->fetchAll(PDO::FETCH_ASSOC);
  $enabledToArk = _get_all_ark_enabled_content_nids();
  foreach ($result as $key => $data) {
    // test if this content is with enable ark set with true.
    if (!isset($enabledToArk[$data['nid']]))
      unset($result[$key]);
  }
  return $result;
}
