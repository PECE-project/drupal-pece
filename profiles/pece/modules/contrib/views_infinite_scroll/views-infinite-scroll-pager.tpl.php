<?php
/**
 * @file
 * Views infinite scroll pager template.
 */
?>
<ul class="pager pager--infinite-scroll <?php print $automatic_scroll_class ?>">
  <li class="pager__item">
    <?php print render($button); ?>
  </li>
</ul>
