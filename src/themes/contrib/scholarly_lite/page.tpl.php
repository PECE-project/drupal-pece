<?php if (theme_get_setting('scrolltop_display')): ?>
<div id="toTop"><i class="fa fa-angle-up"></i></div>
<?php endif; ?>

<?php if ($page['header_top_left'] || $page['header_top_right']) :?>
<!-- #header-top -->
<div id="header-top" class="clearfix">
    <div class="container">

        <!-- #header-top-inside -->
        <div id="header-top-inside" class="clearfix">
            <div class="row">
            
            <?php if ($page['header_top_left']) :?>
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
            
            <?php if ($page['header_top_right']) :?>
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
<header id="header" class="clearfix">
    <div class="container">
        
        <!-- #header-inside -->
        <div id="header-inside" class="clearfix">
            <div class="row">
            
                <div class="col-md-4">
                    <!-- #header-inside-left -->
                    <div id="header-inside-left" class="clearfix">

                    <?php if ($logo):?>
                    <div id="logo">
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"> <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /> </a>
                    </div>
                    <?php endif; ?>
                    
                    <?php if ($site_name):?>
                    <div id="site-name">
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
                    </div>
                    <?php endif; ?>
                    
                    <?php if ($site_slogan):?>
                    <div id="site-slogan">
                    <?php print $site_slogan; ?>
                    </div>
                    <?php endif; ?>
                    
                    <?php if ($page['header']) :?>
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
                            <nav>
                                <?php if ($page['navigation']) :?>
                                <?php print render($page['navigation']); ?>
                                <?php else : ?>
                                <div id="main-menu">
                                <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('class' => array('main-menu', 'menu'), ), 'heading' => array('text' => t('Main menu'), 'level' => 'h2', 'class' => array('element-invisible'), ), )); ?>
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

<!-- # Breadcrumb -->
<?php if ($breadcrumb && theme_get_setting("breadcrumb_display")) :?>

<div id="page-intro" class="clearfix">
    <div id="page-intro-inside" class="clearfix internal-banner no-internal-banner-image">
        <div class="container">
            <div class="row">
                <div class="col-md-12">
                    <div id="breadcrumb" class="clearfix">
                        <div id="breadcrumb-inside" class="clearfix">
                        <?php print $breadcrumb; ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<?php endif; ?>
<!-- EOF:#Breadcrumb -->

<?php if ($page['banner']) : ?>
<!-- #banner -->
<div id="banner" class="clearfix">
    <div class="container">

        <!-- #banner-inside -->
        <div id="banner-inside" class="clearfix">
            <div class="row">
                <div class="col-md-12">

                <div class="banner-area">
                <?php print render($page['banner']); ?>
                </div>
               
                </div>
            </div>
        </div>
        <!-- EOF: #banner-inside -->

    </div>
</div>
<!-- EOF:#banner -->
<?php endif; ?>

<!-- #page -->
<div id="page" class="clearfix">

    <!-- #messages-console -->
    <?php if ($messages):?>
    <div id="messages-console" class="clearfix">
        <div class="container">
            <div class="row">
                <div class="col-md-12">
                <?php print $messages; ?>
                </div>
            </div>
        </div>
    </div>
    <?php endif; ?>
    <!-- EOF: #messages-console -->

    <?php if ($page['highlighted']):?>
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

                <?php if ($page['sidebar_first']):?>
                <aside class="<?php print $sidebar_first_grid_class; ?>">
                    <!--#sidebar-->
                    <section id="sidebar-first" class="sidebar clearfix">
                    <?php print render($page['sidebar_first']); ?>
                    </section>
                    <!--EOF:#sidebar-->
                </aside>
                <?php endif; ?>

                <section class="<?php print $main_grid_class; ?>">

                    <!-- #promoted -->
                    <?php if ($page['promoted']):?>
                        <div id="promoted" class="clearfix">
                            <div id="promoted-inside" class="clearfix">
                            <?php print render($page['promoted']); ?>
                            </div>
                        </div>
                    <?php endif; ?>
                    <!-- EOF: #promoted -->

                    <!-- #main -->
                    <div id="main" class="clearfix">

                        <?php print render($title_prefix); ?>
                        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
                        <?php print render($title_suffix); ?>

                        <!-- #tabs -->
                        <?php if ($tabs):?>
                            <div class="tabs">
                            <?php print render($tabs); ?>
                            </div>
                        <?php endif; ?>
                        <!-- EOF: #tabs -->

                        <?php print render($page['help']); ?>

                        <!-- #action links -->
                        <?php if ($action_links):?>
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

                <?php if ($page['sidebar_second']):?>
                <aside class="<?php print $sidebar_second_grid_class; ?>">
                    <!--#sidebar-->
                    <section id="sidebar-second" class="sidebar clearfix">
                    <?php print render($page['sidebar_second']); ?>
                    </section>
                    <!--EOF:#sidebar-->
                </aside>
                <?php endif; ?>
                
            </div>

        </div>
    </div>
    <!-- EOF:#main-content -->

</div>
<!-- EOF: #page -->

<?php if ($page['bottom_content']):?>
<!-- #bottom-content -->
<div id="bottom-content" class="clearfix">
    <div class="container">

        <!-- #bottom-content-inside -->
        <div id="bottom-content-inside" class="clearfix">
            <div class="bottom-content-area">
                <div class="row">
                    <div class="col-md-12">
                    <?php print render($page['bottom_content']); ?>
                    </div>
                </div>
            </div>
        </div>
        <!-- EOF:#bottom-content-inside -->

    </div>
</div>
<!-- EOF: #bottom-content -->
<?php endif; ?>

<?php if ($page['footer_top_left'] || $page['footer_top_right']) :?>
<!-- #footer-top -->
<div id="footer-top" class="clearfix <?php print $footer_top_regions; ?>">
    <div class="container">

        <!-- #footer-top-inside -->
        <div id="footer-top-inside" class="clearfix">
            <div class="row">
            
            <?php if ($page['footer_top_left']) :?>
            <div class="<?php print $footer_top_left_grid_class; ?>">
                <!-- #footer-top-left -->
                <div id="footer-top-left" class="clearfix">
                    <div class="footer-top-area">
                        <?php print render($page['footer_top_left']); ?>
                    </div>
                </div>
                <!-- EOF:#footer-top-left -->
            </div>
            <?php endif; ?>
            
            <?php if ($page['footer_top_right']) :?>
            <div class="<?php print $footer_top_right_grid_class; ?>">
                <!-- #footer-top-right -->
                <div id="footer-top-right" class="clearfix">
                    <div class="footer-top-area">                    
                        <?php print render($page['footer_top_right']); ?>
                    </div>
                </div>
                <!-- EOF:#footer-top-right -->
            </div>
            <?php endif; ?>
            
            </div>
        </div>
        <!-- EOF: #footer-top-inside -->

    </div>
</div>
<!-- EOF: #footer-top -->    
<?php endif; ?>

<?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third'] || $page['footer_fourth']):?>
<!-- #footer -->
<footer id="footer" class="clearfix">
    <div class="container">

        <div class="row">
            <?php if ($page['footer_first']):?>
            <div class="<?php print $footer_grid_class; ?>">
                <div class="footer-area">
                <?php print render($page['footer_first']); ?>
                </div>
            </div>
            <?php endif; ?>      

            <?php if ($page['footer_second']):?>      
            <div class="<?php print $footer_grid_class; ?>">
                <div class="footer-area">
                <?php print render($page['footer_second']); ?>
                </div>
            </div>
            <?php endif; ?>

            <?php if ($page['footer_third']):?>
            <div class="<?php print $footer_grid_class; ?>">
                <div class="footer-area">
                <?php print render($page['footer_third']); ?>
                </div>
            </div>
            <?php endif; ?>

            <?php if ($page['footer_fourth']):?>
            <div class="<?php print $footer_grid_class; ?>">
                <div class="footer-area">
                <?php print render($page['footer_fourth']); ?>
                </div>
            </div>
            <?php endif; ?>
        </div>

    </div>
</footer> 
<!-- EOF #footer -->
<?php endif; ?>

<?php if ($page['sub_footer_left'] || $page['footer']):?>
<div id="subfooter" class="clearfix">
	<div class="container">
		
		<!-- #subfooter-inside -->
		<div id="subfooter-inside" class="clearfix">
            <div class="row">
    			<div class="col-md-4">
                    <!-- #subfooter-left -->
                    <?php if ($page['sub_footer_left']):?>
                    <div class="subfooter-area left">
                    <?php print render($page['sub_footer_left']); ?>
                    </div>
                    <?php endif; ?>
                    <!-- EOF: #subfooter-left -->
    			</div>
    			<div class="col-md-8">
                    <!-- #subfooter-right -->
                    <?php if ($page['footer']):?>
                    <div class="subfooter-area right">
                    <?php print render($page['footer']); ?>
                    </div>
                    <?php endif; ?>
                    
                    <?php if (theme_get_setting('credits_display')): ?>
                    <!-- #credits -->  
                    <div class="subfooter-area">
                    <div class="block">
                    <p>Scholarly Lite is a free theme, contributed to the Drupal Community by <a href="http://www.morethanthemes.com/&mt-referral=scholarlylite" target="_blank">More than Themes</a>.</p></div></div>
                    <!-- EOF: #credits -->
                    <?php endif; ?>
                    
                    <!-- EOF: #subfooter-right -->
    			</div>
            </div>
		</div>
		<!-- EOF: #subfooter-inside -->
	
	</div>
</div><!-- EOF:#subfooter -->
<?php endif; ?>
