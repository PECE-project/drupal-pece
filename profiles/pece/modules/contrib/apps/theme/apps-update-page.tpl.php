<?php if (!empty($content['apps'])) : ?>
  <div id="apps-list">
    <?php print drupal_render($content['apps']); ?>
  </div>
<?php else: ?>
  <?php print t('No apps with available updates.'); ?>
<?php endif; ?>