<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix node-mt"<?php print $attributes; ?>>
    <?php if ($display_submitted || (module_exists('comment') && ($node->comment == COMMENT_NODE_OPEN || ($node->comment == COMMENT_NODE_CLOSED && $node->comment_count > 0)))): ?>
    <div class="post-submitted-info">
        
        <?php if ($display_submitted): ?>
        <div class="submitted-date">
          <?php $custom_month = format_date($node->created, 'custom', 'M'); ?>
          <?php $custom_day = format_date($node->created, 'custom', 'd'); ?>
          <?php $custom_year = format_date($node->created, 'custom', 'Y'); ?>
          <div class="month"><?php print $custom_month; ?></div>
          <div class="day"><?php print $custom_day; ?></div>
          <div class="year"><?php print $custom_year; ?></div>
        </div>
        <?php endif;?>
        <?php if (module_exists('comment') && ($node->comment == COMMENT_NODE_OPEN || ($node->comment == COMMENT_NODE_CLOSED && $node->comment_count > 0))): ?>
        <div class="comments-count">
          <i class="fa fa-comment"></i>
          <div class="comment-counter"><?php print $node->comment_count; ?></div>
        </div>
        <?php endif;?>
    </div>
  <?php endif;?>
    <?php if ($display_submitted || (module_exists('comment') && ($node->comment == COMMENT_NODE_OPEN || ($node->comment == COMMENT_NODE_CLOSED && $node->comment_count > 0)))) { ?>
    <div class="node-main-content custom-width clearfix">
    <?php } else { ?>
    <div class="node-main-content full-width clearfix">
    <?php } ?>
    <?php if ($title_prefix || $title_suffix || $display_submitted || !$page): ?>
    <header>
      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
          <div class="submitted-user">
          <?php print t('By !username', array('!username' => $name)); ?>
          </div>
      <?php endif; ?>
        
      <?php print $user_picture; ?> 

    </header>
    <?php endif; ?>

    <div class="content"<?php print $content_attributes; ?>>
      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        print render($content);
      ?>
    </div>

    <?php if ($links = render($content['links'])): ?>
    <footer>
    <?php print render($content['links']); ?>
    </footer>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>

</article>