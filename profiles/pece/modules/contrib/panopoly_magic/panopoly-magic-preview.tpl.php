<?php
/**
 * @file
 * Template for the Panopoly Magic preview.
 */
?>
<fieldset class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <legend>
    <?php if (!empty($add_link)): ?>
      <?php // Only keeping 'widget-preview-title' for backcompat with 3rd party themes. ?>
      <div class="panopoly-magic-preview-title widget-preview-title"><?php print $add_link; ?></div>
    <?php endif; ?>
    <span class="fieldset-legend"><?php print $title; ?></span>
  </legend>
  <div class="fieldset-wrapper">
    <?php print $preview; ?>
  </div>
</fieldset>
