<?php

class ERViewModeBehavior extends EntityReference_BehaviorHandler_Abstract {

  public function schema_alter(&$schema, $field) {
    $schema['columns']['view_mode'] = array(
      'description' => 'Target view mode machine name.',
      'type' => 'varchar',
      'length' => 32,
      'default' => 'full',
      'not null' => FALSE,
    );
  }

  public function property_info_alter(&$info, $entity_type, $field, $instance, $field_type) {

  }

  /**
   * Generate a settings form for this handler.
   */
  public function settingsForm($field, $instance) {

    $viewmodes = er_viewmode_get_view_modes($field, $instance, TRUE);

    $form['enabled_viewmodes'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Select enabled view modes'),
      '#options' => $viewmodes,
    );

    return $form;
  }
}
