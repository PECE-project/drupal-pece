<?php

/**
 * @file
 * Hooks provided by the Entity Reference View Widget module.
 */

/**
 * Alter arguments passed to the Entity Reference view used by the widget.
 *
 * Sometimes you need to filter your entity reference view based on the form
 * you're editing (based on referencing entity). In order to do that you need to
 * alter arguments passed (besides the "already referenced entities"
 * argument) to entity reference view. This hook allows you to do that.
 *
 * @param array $arguments
 *   The Arguments array to be altered.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 * @param object $view
 *   The view object that is being used.
 *
 * @codingStandardsIgnoreStart
 */
function hook_entityreference_view_widget_views_arguments_alter(&$arguments, $form_state, $view) {
  // @codingStandardsIgnoreEnd
  if (!empty($form_state['values']['your_field'])) {
    $arguments[] = $form_state['values']['your_field'][LANGUAGE_NONE][0]['value'];
  }
}

/**
 * Alter the widget table rows.
 *
 * @param $rows
 *   The renderable table rows.
 * @param $entities
 *   The loaded entities.
 * @param $settings
 *   The widget settings.
 */
function hook_entityreference_view_widget_rows_alter(&$rows, $entities, $settings) {
  // No example.
}
