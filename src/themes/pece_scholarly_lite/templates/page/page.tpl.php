<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

<?php if (theme_get_setting('scrolltop_display')): ?>
  <div id="toTop"><i class="fa fa-angle-up"></i></div>
<?php endif; ?>

<?php if (!empty($page['header_top_left']) || !empty($page['header_top_right'])) :?>
  <!-- #header-top -->
  <div id="header-top" class="clearfix">
    <div class="container">

      <!-- #header-top-inside -->
      <div id="header-top-inside" class="clearfix">
        <div class="row">

        <?php if (!empty($page['header_top_left'])) :?>
          <div class="<?php print $header_top_left_grid_class; ?>">
            <!-- #header-top-left -->
            <div id="header-top-left" class="clearfix">
              <div class="header-top-area">
                <?php print render($page['header_top_left']); ?>
              </div>
            </div>
            <!-- EOF:#header-top-left -->
          </div>
        <?php endif; ?>

        <?php if (!empty($page['header_top_right'])) :?>
          <div class="<?php print $header_top_right_grid_class; ?>">
            <!-- #header-top-right -->
            <div id="header-top-right" class="clearfix">
              <div class="header-top-area">
                <?php print render($page['header_top_right']); ?>
              </div>
            </div>
            <!-- EOF:#header-top-right -->
          </div>
        <?php endif; ?>

        </div>
      </div>
      <!-- EOF: #header-top-inside -->

    </div>
  </div>
  <!-- EOF: #header-top -->
<?php endif; ?>

<!-- #header -->
<header id="header"  role="banner" class="clearfix">
  <div class="container">

    <!-- #header-inside -->
    <div id="header-inside" class="clearfix">
      <div class="row">

        <div class="col-md-4">
          <!-- #header-inside-left -->
          <div id="header-inside-left" class="clearfix">

          <?php if (!empty($logo)):?>
            <div id="logo">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
                <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
              </a>
            </div>
          <?php endif; ?>

          <?php if ($site_name):?>
            <div id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
            </div>
          <?php endif; ?>

          <?php if ($site_slogan):?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>

          <?php if (!empty($page['header'])) :?>
            <?php print render($page['header']); ?>
          <?php endif; ?>

          </div>
          <!-- EOF:#header-inside-left -->
        </div>

        <div class="col-md-8">
          <!-- #header-inside-right -->
          <div id="header-inside-right" class="clearfix">

            <!-- #main-navigation -->
            <div id="main-navigation" class="clearfix">
              <nav role="navigation">
                <?php if (!empty($page['navigation'])) :?>
                  <?php print render($page['navigation']); ?>
                <?php else : ?>
                <div id="main-menu">
                  <?php print theme('links__system_main_menu', array(
                    'links' => $main_menu,
                    'attributes' => array(
                      'class' => array('main-menu', 'menu'),
                    ),
                    'heading' => array(
                      'text' => t('Main menu'),
                      'level' => 'h2',
                      'class' => array('element-invisible'),
                    ),
                  )); ?>
                </div>
                <?php endif; ?>
              </nav>
            </div>
            <!-- EOF: #main-navigation -->

          </div>
          <!-- EOF:#header-inside-right -->
        </div>

      </div>
    </div>
    <!-- EOF: #header-inside -->

  </div>
</header>
<!-- EOF: #header -->

<!-- #page -->
<div id="page" class="clearfix">

  <!-- #messages-console -->
  <?php if (!empty($messages)):?>
    <div id="messages-console" class="clearfix">
      <div class="container">
        <div class="row">
          <div class="col-md-12"><?php print $messages; ?></div>
        </div>
      </div>
    </div>
  <?php endif; ?>
  <!-- EOF: #messages-console -->

  <?php if (!empty($page['highlighted'])):?>
    <!-- #highlighted -->
    <div id="highlighted">
      <div class="container">

        <!-- #highlighted-inside -->
        <div id="highlighted-inside" class="clearfix">
          <div class="row">
            <div class="col-md-12">
              <?php print render($page['highlighted']); ?>
            </div>
          </div>
        </div>
        <!-- EOF:#highlighted-inside -->

      </div>
    </div>
    <!-- EOF: #highlighted -->
  <?php endif; ?>

  <!-- #main-content -->
  <div id="main-content">
    <div class="container">
      <div class="row">
        <section class="col-md-12">

          <!-- #main -->
          <div id="main" class="clearfix">

            <?php print render($title_prefix); ?>
            <?php if (!empty($title)): ?>
              <h1 class="title" id="page-title"><?php print $title; ?></h1>
            <?php endif; ?>
            <?php print render($title_suffix); ?>

            <!-- #tabs -->
            <?php if (!empty($tabs)):?>
              <div class="tabs">
              <?php print render($tabs); ?>
              </div>
            <?php endif; ?>
            <!-- EOF: #tabs -->

            <?php print render($page['help']); ?>

            <!-- #action links -->
            <?php if (!empty($action_links)):?>
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
            <?php endif; ?>
            <!-- EOF: #action links -->

            <?php if (theme_get_setting('frontpage_content_print') || !drupal_is_front_page()):?>
              <?php print render($page['content']); ?>
              <?php print $feed_icons; ?>
            <?php endif; ?>

          </div>
          <!-- EOF:#main -->

        </section>

      </div>

    </div>
  </div>
  <!-- EOF:#main-content -->

  <!-- #pece links (docs, slack) -->
  <?php if (!empty($pece_docs)): ?>
    <div class="pece-footer-links-wrapper">
      <div class="container">

        <div class="row justify-content-between">
          <div class="col-md-6">
            <div class="pece-link-tab docs">
              <?php print render($pece_docs); ?>
            </div>
            <div class="pece-link-tab slack">
              <?php print render($pece_slack); ?>
            </div>
          </div>
        </div>

      </div>
    </div>
  <?php endif;?>
  <!-- EOF: #pece links -->

</div>
<!-- EOF: #page -->

<?php if (!empty($page['footer'])):?>
  <!-- #footer -->
  <footer id="footer" class="clearfix">
    <div class="container">

      <div class="row">
        <div class="col-md-12">
          <div class="footer-area">
            <?php print render($page['footer']); ?>
          </div>
        </div>
      </div>

    </div>
  </footer>
  <!-- EOF #footer -->
<?php endif; ?>
