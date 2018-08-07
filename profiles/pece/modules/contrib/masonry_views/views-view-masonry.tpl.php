<?php
/**
 * @file
 * Default view template to display content in a Masonry layout.
 */
?>

<?php foreach ($rows as $id => $row): ?>
  <div class="masonry-item<?php if ($classes_array[$id]) print ' ' . $classes_array[$id]; ?>">
    <?php print $row; ?>
  </div>
<?php endforeach; ?>

