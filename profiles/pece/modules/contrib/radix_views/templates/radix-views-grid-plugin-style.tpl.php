<?php
/**
 * @file
 * View template for Radix grid style.
 * @ingroup views_templates
 */
?>
<?php if ($has_grouping): ?>
  <div class="<?php print $views_group_col_class; ?> views-group">
    <h2><?php print $title; ?></h2>
    <?php foreach ($rows as $row): ?>
      <div class="<?php print $views_row_class; ?> views-row">
        <?php foreach ($row as $item): ?>
          <div class="<?php print $views_row_col_class; ?> views-col">
            <?php print $item; ?>
          </div>
        <?php endforeach; ?>
      </div>
    <?php endforeach; ?>
  </div>
<?php else: ?>
  <?php foreach ($rows as $row): ?>
    <div class="row views-row">
      <?php if (is_array($row)): ?>
      <?php foreach ($row as $item): ?>
        <div class="<?php print $views_row_col_class; ?> views-col">
          <?php print $item; ?>
        </div>
      <?php endforeach; ?>
      <?php else: ?>
        <div class="views-col">
          <?php print $row; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endforeach; ?>
<?php endif; ?>
