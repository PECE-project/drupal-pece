<?php if (isset($servers)) : ?>
  <div id="server-list">
    <?php foreach ($servers as $server): ?>
      <?php print drupal_render($server); ?>
      <hr/>
    <?php endforeach; ?>
  </div>
<?php else: ?>
  <div class="messages"><?php print t('No app servers are available.'); ?></div>
<?php endif; ?>
