<?php

/**
 * @file
 * File: entityreference_view_widget_handler_field_checkbox.inc.
 */

/**
 * Handler field checkbox.
 *
 * Provides the checkbox field to tick the view rows
 * and set them as field values.
 *
 * @codingStandardsIgnoreStart
 */
class entityreference_view_widget_handler_field_checkbox extends views_handler_field_entity {
  var $revision = FALSE;

  /**
   * The form which replaces the placeholder from render().
   */
  public function views_form(&$form, &$form_state) {
    // @codingStandardsIgnoreEnd
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );
    // At this point, the query has already been run, so we can access the
    // results in order to get the base key value (for example, nid for nodes).
    foreach ($this->view->result as $row_index => $row) {
      $entity = $this->entities[$row_index];
      if ($this->view->base_field == 'search_api_id' && isset($row->_entity_properties)) {
        $entity_id = $row->_entity_properties[$this->view->base_field];
      }
      else {
        $entity_id = $entity->{$this->view->base_field};
      }

      if ($this->options['ervw']['force_single']) {
        $form[$this->options['id']][$row_index] = array(
          '#type' => 'radio',
          '#title' => check_plain(entity_label($this->entity_type, $entity)),
          '#title_display' => $this->options['ervw']['label_display'],
          '#parents' => array($this->options['id']),
          '#return_value' => $entity_id,
        );
      }
      else {
        $form[$this->options['id']][$row_index] = array(
          '#type' => 'checkbox',
          '#title' => check_plain(entity_label($this->entity_type, $entity)),
          '#title_display' => $this->options['ervw']['label_display'],
          '#return_value' => $entity_id,
          '#default_value' => FALSE,
          '#attributes' => array('class' => array('entity-reference-view-widget-select')),
        );
      }
    }
  }

  /**
   * Render.
   *
   * @codingStandardsIgnoreStart
   */
  public function render($values) {
    // @codingStandardsIgnoreEnd
    if ($this->view->base_field == 'search_api_id' && isset($values->_entity_properties)) {
      $entity_id = $values->_entity_properties[$this->view->base_field];
    }
    else {
      $entity_id = $this->get_value($values, $this->view->base_field);
    }
    if (empty($entity_id)) {
      return;
    }
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  /**
   * Option definition.
   *
   * @codingStandardsIgnoreStart
   */
  public function option_definition() {
    // @codingStandardsIgnoreEnd
    $options = parent::option_definition();
    $options['ervw'] = array(
      'contains' => array(
        'force_single' => array('default' => FALSE),
        'label_display' => array('default' => 'invisible'),
      ),
    );
    return $options;
  }

  /**
   * Options form.
   *
   * @codingStandardsIgnoreStart
   */
  public function options_form(&$form, &$form_state) {
    // @codingStandardsIgnoreEnd
    parent::options_form($form, $form_state);

    $form['ervw'] = array(
      '#type' => 'fieldset',
      '#title' => t('Entity Reference Views Widget'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['ervw']['force_single'] = array(
      '#type' => 'checkbox',
      '#title' => t('Force single'),
      '#default_value' => $this->options['ervw']['force_single'],
      '#description' => t('Check this box to restrict selection to a single value.'),
    );

    $form['ervw']['label_display'] = array(
      '#type' => 'select',
      '#title' => t('Label display'),
      '#options' => array(
        'before' => t('Before'),
        'after' => t('After'),
        'invisible' => t('Invisible'),
        'attribute' => t('Attribute'),
      ),
      '#description' => t('Select the position of the label relative to the checkbox.'),
      '#default_value' => $this->options['ervw']['label_display'],
    );
  }

}
