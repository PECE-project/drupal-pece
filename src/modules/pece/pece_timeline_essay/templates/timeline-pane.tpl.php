<div class="pece-timeline-pane">
  <h1>TIMELINE PANE TEMPLATE</h1>
  <?php if (!empty($content['timeline'])) : ?>

    <div class="<?php print $content['class']; ?>">
      <?php if (!empty($content['title'])) : ?>
        <h2><?php print $content['title']; ?></h2>
      <?php endif; ?>

      <p><?php print render($content['timeline']); ?></p>
    </div>

  <?php endif; ?>
</div>