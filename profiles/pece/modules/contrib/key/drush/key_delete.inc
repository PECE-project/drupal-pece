<?php

use Drush\Log\LogLevel;

/**
 * Delete a key.
 *
 * @param string $id
 *   The ID of the key to delete.
 *
 * @return bool
 *   FALSE if not successful.
 */
function _drush_key_delete($id) {
  // Look for a key with the specified ID. If one does not exist, set an
  // error and abort.
  $key = key_get_key($id, TRUE);
  if (!$key) {
    return drush_set_error('DRUSH_KEY_DOES_NOT_EXIST', dt('Key !id does not exist.', array('!id' => $id)));
  }

  // Confirm that the key should be deleted.
  drush_log(dt('Be extremely careful when deleting a key! It may result in losing access to a service or making encrypted data unreadable.'), LogLevel::WARNING);
  drush_print(dt('The following key will be deleted: !id', array('!id' => $id)));
  if (!drush_confirm(dt('Do you really want to continue?'))) {
    return drush_user_abort();
  }

  // Delete the key.
  key_delete_key($id, FALSE);

  // Try to load the key to confirm that it was deleted.
  $key_check = key_get_key($id, TRUE);

  // If the key still exists, set an error and abort.
  if ($key_check) {
    return drush_set_error('DRUSH_KEY_NOT_DELETED', dt('Key !id was not deleted.', array('!id' => $id)));
  }

  drush_log(dt('Key !id was deleted successfully.', array('!id' => $id)), LogLevel::OK);
}
