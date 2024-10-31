<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\Profile.
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;
use Drupal\migrate\Row;
use Drupal\profile\Plugin\migrate\source\d7\Profile2 as D7Profile;

/**
 * Gets all profiles from the source.
 *
 * @MigrateSource(
 *   id = "v1_profile_source",
 *   source_module = "profile2"
 * )
 */
class Profile extends D7Profile {

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = parent::fields();
    $fields += [
      'user_picture' => $this->t('User picture'),
    ];
    return $fields;
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow(Row $row) {

    $uid = $row->getSourceProperty('uid');

    $user_picture = $this->select('field_data_field_user_picture', 'fup')
      ->fields('fup', ['field_user_picture_fid'])
      ->condition('fup.entity_id', $uid)
      ->execute()->fetchField();
    if ($user_picture) {
      $row->setSourceProperty('user_picture', $user_picture);
    }

    return parent::prepareRow($row);
  }

}


