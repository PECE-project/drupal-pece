<?php

/**
 * @file
 * Page callbacks for Feeds Import Preview.
 */

/**
 * Form constructor for the feeds import preview form.
 *
 * @see feedspreview_form_validate()
 * @see feedspreview_form_submit()
 */
function feedspreview_form($form, &$form_state, $importer_id) {
  $source = FeedsPreviewSource::instance($importer_id, 0);

  // Set flag that this form is viewed in the admin interface.
  $form_state['admin_preview'] = TRUE;

  $form = array();
  $form['#importer_id'] = $importer_id;
  $form['#attributes']['enctype'] = 'multipart/form-data';

  $form['help'] = array(
    '#markup' => '<p>' . t('This will give you a brief look of what the parsed result looks like (thus before the data is processed). Note that the data may be modified during processing. If your browser supports it, you can use the left and right arrow keys on your keyboard to navigate between the results.') . '</p>',
  );

  if (isset($form_state['feeds_parser_result'])) {
    $form['feedspreview_result'] = feedspreview_table($source, $form_state['feeds_parser_result']);
  }

  $source_form = $source->configForm($form_state);
  if (!empty($source_form)) {
    $form['feeds'] = array(
      '#type' => 'fieldset',
      '#title' => t('Import settings'),
      '#tree' => TRUE,
      '#collapsed' => isset($form_state['feeds_parser_result']),
      '#collapsible' => isset($form_state['feeds_parser_result']),
    ) + $source_form;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Preview import'),
  );

  return $form;
}

/**
 * Returns preview results array.
 *
 * @param string $importer_id
 *   The ID of the importer.
 * @param FeedsParserResult $result
 *   The parser result.
 *
 * @return array
 *   Markup for previewing the results.
 */
function feedspreview_show_result_on_form($importer_id, $result) {
  $field = array(
    '#type' => 'fieldset',
    '#title' => t('Preview'),
    '#weight' => -50,
  );

  $field['help'] = array(
    '#markup' => '<p>' . t('This will give you a brief look of what the parsed result looks like (thus before the data is processed). Note that the data may be modified during processing. If your browser supports it, you can use the left and right arrow keys on your keyboard to navigate between the results.') . '</p>',
  );

  $source = FeedsPreviewSource::instance($importer_id, 0);
  $field['result'] = feedspreview_table($source, $result);

  return $field;
}

/**
 * Form validation handler for feedspreview_form().
 *
 * @see feedspreview_form()
 * @see feedspreview_form_submit()
 */
function feedspreview_form_validate($form, &$form_state) {
  FeedsPreviewSource::instance($form['#importer_id'], 0)->configFormValidate($form_state['values']['feeds']);
}

/**
 * Form submission handler for feedspreview_form().
 *
 * @see feedspreview_form()
 * @see feedspreview_form_validate()
 */
function feedspreview_form_submit($form, &$form_state) {
  $source = FeedsPreviewSource::instance($form['#importer_id'], 0);

  if (!empty($form_state['values']['feeds']) && is_array($form_state['values']['feeds'])) {
    $source->addConfig($form_state['values']['feeds']);
    if (!empty($form_state['admin_preview'])) {
      // Save source only when using the preview form on the importer configuration.
      $source->save();
    }
  }

  try {
    $form_state['feeds_parser_result'] = $source->preview();
  }
  catch (Exception $e) {
    drupal_set_message($e->getMessage(), 'error');
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Builds a preview table.
 *
 * @param FeedsSource $feeds_source
 *   The import source.
 * @param FeedsParserResult $result
 *   The parser result.
 *
 * @return array
 *   A build array in the format expected by drupal_render().
 */
function feedspreview_table(FeedsSource $feeds_source, FeedsParserResult $result) {
  // Check the result's source.
  if (empty($result->items)) {
    drupal_set_message(t('No result.'));
    return;
  }

  $table_builder = new FeedsPreviewTable($feeds_source);
  return $table_builder->build($result);
}
