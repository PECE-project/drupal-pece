<?php
/**
 * @file
 * Drupal Ipsum text generation results template.
 *
 * Available variables:
 *  - $drupal_ipsum_text string the generated text
 *  - $drupal_ipsum_form string the markup for the generation form
 */
?>
<div class="drupal_ipsum_results_container">
  <a href="javascript:void(0)" class="drupal_ipsum_select" title="<?php echo t('Select all'); ?>"><?php echo t('Select all'); ?></a>
  <div class="drupal_ipsum_text"><?php echo $drupal_ipsum_text; ?></div>
  <textarea class="drupal_ipsum_textarea"><?php echo $drupal_ipsum_text; ?></textarea>
</div>

<div class="drupal_ipsum_results_form">
  <h2><?php echo t('Want more?'); ?></h2>
  <?php echo $drupal_ipsum_form; ?>
</div>