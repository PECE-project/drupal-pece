<?php
/**
 * @file
 * Output the server manifest in .md format.
 *
 * Note that the spacing in this file is very important.
 * New lines after an ending php tag (?>) are ignored so need double new lines.
 *
 * Available variables:
 *  $title
 *   Title of the server
 *  $apps_render
 *   An array of apps including name, description, and conflicts.
 *  $server
 *   Array of server information.
 *  $apps
 *    Array of app information.
 */
?>
<?php print t('@server App Catalog', array('@server' => $title)); ?>

=======

<?php foreach ($apps_render as $app): ?>

<?php print $app['name']; ?>

-----------
<?php print $app['description']; ?>

  <?php if ($app['conflicts']): ?>

### <?php print t('Conflicts'); ?>

    <?php foreach ($app['conflicts'] as $conflict): ?>
* <?php print $conflict; ?>

    <?php endforeach; ?>
  <?php endif; ?>
<?php endforeach; ?>
