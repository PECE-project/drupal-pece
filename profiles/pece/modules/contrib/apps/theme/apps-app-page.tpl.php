<div id="app-wrapper" class="clearfix">
  <div id="sidebar">
    <h2><?php print $author_title; ?></h2>
    <div class = 'app-author'><?php print $author ?></div>

    <h2><?php print $version_title; ?></h2>
    <div class = 'app-version'><?php print $version ?></div>

    <!-- Print ratings if enabled -->
    <?php if (isset($rating)): ?>
      <div class="divider"></div>
      <h2><?php print $rating_title; ?></h2>
      <h3><?php print $rating_caption; ?></h3>
      <?php print drupal_render($rating); ?>
    <?php endif; ?>
    <?php if ($parent_apps): ?>
      <h2><?php print $parent_apps_title ?></h2>
      <div class = 'app-parents'><?php print implode(', ', $parent_apps); ?></div>
    <?php endif; ?>
  </div>
  <div class="app-main">

    <div id="app-top">
      <?php if ($logo): ?>
        <div class = 'app-logo-small'>
          <?php print $logo ?>
        </div>
      <?php endif; ?>
      <h1><?php print $name ?></h1>
    </div>

    <?php if (!empty($status_title)): ?>
    <div class = 'app-status'>
      <h2><?php print $status_title; ?></h2>
      <?php print $status ?>
    </div>
    <?php endif; ?>

  <?php if ($description): ?>
    <div class = 'app-description'>
      <h2><?php print $description_title; ?></h2>
      <?php print $description ?>
    </div>
  <?php endif; ?>

    <?php if ($screenshot): ?>
      <div class = 'app-screenshot'><?php print $screenshot ?><div class="screenshot-shadow"></div></div>
    <?php endif; ?>

    <?php if (!empty($conflicts)): ?>
      <div class = 'app-conflicts'>
        <h2><?php print $conflicts_title; ?></h2>
        <?php print $conflicts ?>
      </div>
    <?php endif; ?>

  </div>
</div>
