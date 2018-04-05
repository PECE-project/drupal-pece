<?php
/**
 * @file
 * Template for PECE Douby Double.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display douby-double clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="container-fluid">
    <div class="row">
      <div class="col-md-10 pece-layouts-content panel-panel">
        <div class="row">
          <div class="col-md-12 pece-layouts-contentheader panel-panel">
            <?php print $content['contentheader']; ?>
          </div>
        </div>
        <div class="row">
          <div class="col-md-12 pece-layouts-contenttop panel-panel">
            <?php print $content['contenttop']; ?>
          </div>
        </div>
        <div class="row">
          <div class="col-md-12 pece-layouts-contentbottom panel-panel">
            <?php print $content['contentbottom']; ?>
          </div>
        </div>
        <div class="row">
          <div class="col-md-12 pece-layouts-contentfooter panel-panel">
            <?php print $content['contentfooter']; ?>
          </div>
        </div>
      </div>
      <div class="col-md-2 pece-layouts-sidebar panel-panel">
        <div class="row">
          <div class="col-md-12 pece-layouts-sidebartop panel-panel">
            <div class="panel-panel-inner">
              <?php print $content['sidebartop']; ?>
            </div>
          </div>
        </div>
        <div class="row">
          <div class="col-md-12 pece-layouts-sidebarbottom panel-panel">
            <div class="panel-panel-inner">
              <?php print $content['sidebarbottom']; ?>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>

</div><!-- /.douby-double -->
