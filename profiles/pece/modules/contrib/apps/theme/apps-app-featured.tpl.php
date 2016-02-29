<div id="apps-featured-panel">
  <div id="apps-featured-wrapper">
    <div id="apps-featured">
      <div class = 'app-logo'>
        <?php print $logo ?>
      </div>
      <div class="left">
        <h1><?php print $name ?></h1>
        <?php if (isset($rating)): ?>
          <?php print drupal_render($rating); ?>
        <?php endif; ?>
      </div>
      <div class="app-screenshot"><?php print $screenshot ?><div class="screenshot-shadow"></div></div>
    </div>
  </div>
</div>
