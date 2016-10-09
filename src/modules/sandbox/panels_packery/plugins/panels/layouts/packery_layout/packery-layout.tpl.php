<?php
/**
 * @file
 * Template for the Packery layout.
 */
?>

<div <?php print drupal_attributes($attributes_array); ?>>

  <div class="packery-layout-panel panel-panel">
    <div class="packery-layout-panel-inner panel-panel-inner">
      <?php print $content['contentmain']; ?>
    </div>
  </div>

</div>
