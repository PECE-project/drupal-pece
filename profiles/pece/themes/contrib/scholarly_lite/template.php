<?php

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function scholarly_lite_breadcrumb($variables){

	$breadcrumb = $variables['breadcrumb'];

	if (!empty($breadcrumb)) {
	$breadcrumb[] = drupal_get_title();
	return '<div>' . implode(' <span class="breadcrumb-separator"></span>', $breadcrumb) . '</div>';
	}

}

/**
 * Add classes to block.
 */
function scholarly_lite_preprocess_block(&$variables) {

	$variables['title_attributes_array']['class'][] = 'title';
	$variables['classes_array'][]='clearfix';

}

/**
 * Override or insert variables into the html template.
 */
function scholarly_lite_preprocess_html(&$variables) {

	if (empty($variables['page']['banner'])) {
		$variables['classes_array'][] = 'no-banner';
	}

	$color_scheme = theme_get_setting('color_scheme');

	if ($color_scheme != 'default') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/style-' .$color_scheme. '.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-1'  &&
		theme_get_setting('slogan_font_family')=='slff-1' ||
		theme_get_setting('headings_font_family')=='hff-1' ||
		theme_get_setting('paragraph_font_family')=='pff-1') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/merriweather-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-2'  ||
		theme_get_setting('slogan_font_family')=='slff-2' ||
		theme_get_setting('headings_font_family')=='hff-2' ||
		theme_get_setting('paragraph_font_family')=='pff-2') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/sourcesanspro-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-3'  ||
		theme_get_setting('slogan_font_family')=='slff-3' ||
		theme_get_setting('headings_font_family')=='hff-3' ||
		theme_get_setting('paragraph_font_family')=='pff-3') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/ubuntu-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-4'  ||
		theme_get_setting('slogan_font_family')=='slff-4' ||
		theme_get_setting('headings_font_family')=='hff-4' ||
		theme_get_setting('paragraph_font_family')=='pff-4') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/ptsans-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-5'  ||
		theme_get_setting('slogan_font_family')=='slff-5' ||
		theme_get_setting('headings_font_family')=='hff-5' ||
		theme_get_setting('paragraph_font_family')=='pff-5') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/roboto-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-6'  ||
		theme_get_setting('slogan_font_family')=='slff-6' ||
		theme_get_setting('headings_font_family')=='hff-6' ||
		theme_get_setting('paragraph_font_family')=='pff-6') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/opensans-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-7'  ||
		theme_get_setting('slogan_font_family')=='slff-7' ||
		theme_get_setting('headings_font_family')=='hff-7' ||
		theme_get_setting('paragraph_font_family')=='pff-7') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/lato-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-8'  ||
		theme_get_setting('slogan_font_family')=='slff-8' ||
		theme_get_setting('headings_font_family')=='hff-8' ||
		theme_get_setting('paragraph_font_family')=='pff-8') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/roboto-condensed-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-9'  ||
		theme_get_setting('slogan_font_family')=='slff-9' ||
		theme_get_setting('headings_font_family')=='hff-9' ||
		theme_get_setting('paragraph_font_family')=='pff-9') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/exo-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-10'  ||
		theme_get_setting('slogan_font_family')=='slff-10' ||
		theme_get_setting('headings_font_family')=='hff-10' ||
		theme_get_setting('paragraph_font_family')=='pff-10') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/roboto-slab-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-11'  ||
		theme_get_setting('slogan_font_family')=='slff-11' ||
		theme_get_setting('headings_font_family')=='hff-11' ||
		theme_get_setting('paragraph_font_family')=='pff-11') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/raleway-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-12'  ||
		theme_get_setting('slogan_font_family')=='slff-12' ||
		theme_get_setting('headings_font_family')=='hff-12' ||
		theme_get_setting('paragraph_font_family')=='pff-12') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/josefin-sans-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-14'  ||
		theme_get_setting('slogan_font_family')=='slff-14' ||
		theme_get_setting('headings_font_family')=='hff-14' ||
		theme_get_setting('paragraph_font_family')=='pff-14') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/playfair-display-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-15'  ||
		theme_get_setting('slogan_font_family')=='slff-15' ||
		theme_get_setting('headings_font_family')=='hff-15' ||
		theme_get_setting('paragraph_font_family')=='pff-15') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/philosopher-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-16'  ||
		theme_get_setting('slogan_font_family')=='slff-16' ||
		theme_get_setting('headings_font_family')=='hff-16' ||
		theme_get_setting('paragraph_font_family')=='pff-16') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/cinzel-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-17'  ||
		theme_get_setting('slogan_font_family')=='slff-17' ||
		theme_get_setting('headings_font_family')=='hff-17' ||
		theme_get_setting('paragraph_font_family')=='pff-17') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/oswald-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-18'  ||
		theme_get_setting('slogan_font_family')=='slff-18' ||
		theme_get_setting('headings_font_family')=='hff-18' ||
		theme_get_setting('paragraph_font_family')=='pff-18') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/playfairdisplaysc-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-19'  ||
		theme_get_setting('slogan_font_family')=='slff-19' ||
		theme_get_setting('headings_font_family')=='hff-19' ||
		theme_get_setting('paragraph_font_family')=='pff-19') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/cabin-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-20'  ||
		theme_get_setting('slogan_font_family')=='slff-20' ||
		theme_get_setting('headings_font_family')=='hff-20' ||
		theme_get_setting('paragraph_font_family')=='pff-20') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/notosans-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-22'  ||
		theme_get_setting('slogan_font_family')=='slff-22' ||
		theme_get_setting('headings_font_family')=='hff-22' ||
		theme_get_setting('paragraph_font_family')=='pff-22') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/droidserif-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-23'  ||
		theme_get_setting('slogan_font_family')=='slff-23' ||
		theme_get_setting('headings_font_family')=='hff-23' ||
		theme_get_setting('paragraph_font_family')=='pff-23') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/ptserif-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-24'  ||
		theme_get_setting('slogan_font_family')=='slff-24' ||
		theme_get_setting('headings_font_family')=='hff-24' ||
		theme_get_setting('paragraph_font_family')=='pff-24') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/vollkorn-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-25'  ||
		theme_get_setting('slogan_font_family')=='slff-25' ||
		theme_get_setting('headings_font_family')=='hff-25' ||
		theme_get_setting('paragraph_font_family')=='pff-25') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/alegreya-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-26'  ||
		theme_get_setting('slogan_font_family')=='slff-26' ||
		theme_get_setting('headings_font_family')=='hff-26' ||
		theme_get_setting('paragraph_font_family')=='pff-26') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/notoserif-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-27'  ||
		theme_get_setting('slogan_font_family')=='slff-27' ||
		theme_get_setting('headings_font_family')=='hff-27' ||
		theme_get_setting('paragraph_font_family')=='pff-27') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/crimsontext-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-28'  ||
		theme_get_setting('slogan_font_family')=='slff-28' ||
		theme_get_setting('headings_font_family')=='hff-28' ||
		theme_get_setting('paragraph_font_family')=='pff-28') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/gentiumbookbasic-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-29'  ||
		theme_get_setting('slogan_font_family')=='slff-29' ||
		theme_get_setting('headings_font_family')=='hff-29' ||
		theme_get_setting('paragraph_font_family')=='pff-29') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/volkhov-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	if (theme_get_setting('sitename_font_family')=='sff-31'  ||
		theme_get_setting('slogan_font_family')=='slff-31' ||
		theme_get_setting('headings_font_family')=='hff-31' ||
		theme_get_setting('paragraph_font_family')=='pff-31') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/alegreyasc-font.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	drupal_add_css(path_to_theme() . '/fonts/sourcecodepro-font.css', array('group' => CSS_THEME, 'type' => 'file'));

	drupal_add_css(path_to_theme() . '/fonts/ptserif-blockquote-font.css', array('group' => CSS_THEME, 'type' => 'file'));

  drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css', array('type' => 'external'));

	drupal_add_css(path_to_theme() . '/ie9.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(IE 9)&(!IEMobile)', '!IE' => FALSE), 'preprocess' => FALSE));

	/**
	 * Add local.css file for CSS overrides.
	 */
	drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/local.css', array('group' => CSS_THEME, 'type' => 'file'));

	/**
	* Bootstrap CDN
	*/
    if (theme_get_setting('bootstrap_css_cdn', 'scholarly_lite')) {
        $cdn = '//maxcdn.bootstrapcdn.com/bootstrap/' . theme_get_setting('bootstrap_css_cdn', 'scholarly_lite')  . '/css/bootstrap.min.css';
        drupal_add_css($cdn, array('type' => 'external'));
    }

    if (theme_get_setting('bootstrap_js_cdn', 'scholarly_lite')) {
        $cdn = '//maxcdn.bootstrapcdn.com/bootstrap/' . theme_get_setting('bootstrap_js_cdn', 'scholarly_lite')  . '/js/bootstrap.min.js';
        drupal_add_js($cdn, array('type' => 'external'));
    }

	/**
	 * Add Javascript for enable/disable scrollTop action.
	 */
	if (theme_get_setting('scrolltop_display')) {

		drupal_add_js('jQuery(document).ready(function($) {
		$(window).scroll(function() {
			if($(this).scrollTop() != 0) {
				$("#toTop").addClass("show");
			} else {
				$("#toTop").removeClass("show");
			}
		});

		$("#toTop").click(function() {
			$("body,html").animate({scrollTop:0},800);
		});

		});',
		array('type' => 'inline', 'scope' => 'header'));

	}
	//EOF:Javascript

	$fixed_header = theme_get_setting('fixed_header');
	if ($fixed_header) {

		/**
		 * Add Javascript for the fixed header
		 */
		drupal_add_js('jQuery(document).ready(function($) {

			var	headerTopHeight = $("#header-top").outerHeight(),
			headerHeight = $("#header").outerHeight();

			$(window).scroll(function() {
			if(($(this).scrollTop() > headerTopHeight+headerHeight) && ($(window).width() > 767)) {
				$("body").addClass("onscroll");
				if (($("#site-name").length > 0) && ($("#logo").length > 0)) {
					$(".onscroll #logo").addClass("hide");
				}

				if ($("#banner").length > 0) {
 					$("#banner").css("marginTop", (headerHeight)+"px");
				} else if ($("#page-intro").length > 0) {
					$("#page-intro").css("marginTop", (headerHeight)+"px");
				} else {
					$("#page").css("marginTop", (headerHeight)+"px");
				}
			} else {
				$("body").removeClass("onscroll");
				$("#logo").removeClass("hide");
				$("#page,#banner,#page-intro").css("marginTop", (0)+"px");
			}
			});
		});',
		array('type' => 'inline', 'scope' => 'header'));
		//EOF:Javascript

	}

	$responsive_meanmenu = theme_get_setting('responsive_multilevelmenu_state');

	if ($responsive_meanmenu) {

	drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/js/meanmenu/meanmenu.css');
	drupal_add_js(drupal_get_path('theme', 'scholarly_lite') .'/js/meanmenu/jquery.meanmenu.fork.js', array('preprocess' => false));

		/**
		 * Add Javascript for the mobile mean menu
		 */
		drupal_add_js('jQuery(document).ready(function($) {

			$("#main-navigation .sf-menu, #main-navigation .content>ul.menu, #main-navigation ul.main-menu").wrap("<div class=\'meanmenu-wrapper\'></div>");
			$("#main-navigation .meanmenu-wrapper").meanmenu({
				meanScreenWidth: "767",
				meanRemoveAttrs: true,
				meanMenuContainer: "#header-inside",
				meanMenuClose: ""
			});

			$("#header-top .sf-menu, #header-top .content>ul.menu").wrap("<div class=\'header-top-meanmenu-wrapper\'></div>");
			$("#header-top .header-top-meanmenu-wrapper").meanmenu({
				meanScreenWidth: "767",
				meanRemoveAttrs: true,
				meanMenuContainer: "#header-top-inside",
				meanMenuClose: ""
			});

		});',
		array('type' => 'inline', 'scope' => 'header'));
		//EOF:Javascript

	}

}

/**
 * Override or insert variables into the html template.
 */
function scholarly_lite_process_html(&$vars) {

	$classes = explode(' ', $vars['classes']);
	$classes[] = theme_get_setting('sitename_font_family');
	$classes[] = theme_get_setting('slogan_font_family');
	$classes[] = theme_get_setting('headings_font_family');
	$classes[] = theme_get_setting('paragraph_font_family');
	$classes[] = theme_get_setting('form_style');
	$vars['classes'] = trim(implode(' ', $classes));

}

/**
 * Preprocess variables for page template.
 */
function scholarly_lite_preprocess_page(&$variables) {

	$three_columns_grid_layout = theme_get_setting('three_columns_grid_layout', 'scholarly_lite');
	$sidebar_first 		= !empty($variables['page']['sidebar_first']) ? $variables['page']['sidebar_first'] : null;
	$sidebar_second 	= !empty($variables['page']['sidebar_second']) ? $variables['page']['sidebar_second'] : null;
	$header_top_left 	= !empty($variables['page']['header_top_left']) ? $variables['page']['header_top_left'] : null;
	$header_top_right = !empty($variables['page']['header_top_right']) ? $variables['page']['header_top_right'] : null;
	$footer_top_left 	= !empty($variables['page']['footer_top_left']) ? $variables['page']['footer_top_left'] : null;
	$footer_top_right = !empty($variables['page']['footer_top_right']) ? $variables['page']['footer_top_right'] : null;
	$footer_first 		= !empty($variables['page']['footer_first']) ? $variables['page']['footer_first'] : null;
	$footer_second 		= !empty($variables['page']['footer_second']) ? $variables['page']['footer_second'] : null;
	$footer_third 		= !empty($variables['page']['footer_third']) ? $variables['page']['footer_third'] : null;
	$footer_fourth 		= !empty($variables['page']['footer_fourth']) ? $variables['page']['footer_fourth'] : null;
	$breadcrumb 			= theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));

	/**
	 * Insert variables into the page template.
	 */
	if (isset($variables['node']) && $variables['node']->type != 'page' ) {
		if($sidebar_first && $sidebar_second) {
			if ($three_columns_grid_layout == 'grid_3_6_3') {
				$variables['main_grid_class'] = 'col-md-6';
				$variables['sidebar_first_grid_class'] = 'col-md-3';
				$variables['sidebar_second_grid_class'] = 'col-md-3';
			} elseif ($three_columns_grid_layout == 'grid_2_6_4') {
				$variables['main_grid_class'] = 'col-md-6';
				$variables['sidebar_first_grid_class'] = 'col-md-2';
				$variables['sidebar_second_grid_class'] = 'col-md-4';
			} elseif ($three_columns_grid_layout == 'grid_4_6_2') {
				$variables['main_grid_class'] = 'col-md-6';
				$variables['sidebar_first_grid_class'] = 'col-md-4';
				$variables['sidebar_second_grid_class'] = 'col-md-2';
			}
		} elseif ($sidebar_first && !$sidebar_second) {
			$variables['main_grid_class'] = 'col-md-8';
			$variables['sidebar_first_grid_class'] = 'col-md-4 fix-sidebar-first';
		} elseif (!$sidebar_first && $sidebar_second) {
			$variables['main_grid_class'] = 'col-md-8';
			$variables['sidebar_second_grid_class'] = 'col-md-4 fix-sidebar-second';
		} else {
			$variables['main_grid_class'] = 'col-md-8 col-md-offset-2';
			$variables['sidebar_first_grid_class'] = '';
			$variables['sidebar_second_grid_class'] = '';
		}
	} else {
		if($sidebar_first && $sidebar_second) {
			if ($three_columns_grid_layout == 'grid_3_6_3') {
				$variables['main_grid_class'] = 'col-md-6';
				$variables['sidebar_first_grid_class'] = 'col-md-3';
				$variables['sidebar_second_grid_class'] = 'col-md-3';
			} elseif ($three_columns_grid_layout == 'grid_2_6_4') {
				$variables['main_grid_class'] = 'col-md-6';
				$variables['sidebar_first_grid_class'] = 'col-md-2';
				$variables['sidebar_second_grid_class'] = 'col-md-4';
			} elseif ($three_columns_grid_layout == 'grid_4_6_2') {
				$variables['main_grid_class'] = 'col-md-6';
				$variables['sidebar_first_grid_class'] = 'col-md-4';
				$variables['sidebar_second_grid_class'] = 'col-md-2';
			}
		} elseif ($sidebar_first && !$sidebar_second) {
			$variables['main_grid_class'] = 'col-md-8';
			$variables['sidebar_first_grid_class'] = 'col-md-4 fix-sidebar-first';
		} elseif (!$sidebar_first && $sidebar_second) {
			$variables['main_grid_class'] = 'col-md-8';
			$variables['sidebar_second_grid_class'] = 'col-md-4 fix-sidebar-second';
		} else {
			$variables['main_grid_class'] = 'col-md-12';
			$variables['sidebar_first_grid_class'] = '';
			$variables['sidebar_second_grid_class'] = '';
		}
	}

	if($header_top_left && $header_top_right) {
		$variables['header_top_left_grid_class'] = 'col-md-8';
		$variables['header_top_right_grid_class'] = 'col-md-4';
	} elseif ($header_top_right || $header_top_left) {
		$variables['header_top_left_grid_class'] = 'col-md-12';
		$variables['header_top_right_grid_class'] = 'col-md-12';
	}

	if($footer_top_left && $footer_top_right) {
		$variables['footer_top_left_grid_class'] = 'col-sm-6';
		$variables['footer_top_right_grid_class'] = 'col-sm-6';
		$variables['footer_top_regions'] = 'two-regions';
	} elseif ($footer_top_right || $footer_top_left) {
		$variables['footer_top_regions'] = 'one-region';
		$variables['footer_top_left_grid_class'] = 'col-md-12';
		$variables['footer_top_right_grid_class'] = 'col-ms-12';
	}

	if ($footer_first && $footer_second && $footer_third && $footer_fourth) {
		$variables['footer_grid_class'] = 'col-sm-3';
	} elseif ((!$footer_first && $footer_second && $footer_third && $footer_fourth) || ($footer_first && !$footer_second && $footer_third && $footer_fourth)
	|| ($footer_first && $footer_second && !$footer_third && $footer_fourth) || ($footer_first && $footer_second && $footer_third && !$footer_fourth)) {
		$variables['footer_grid_class'] = 'col-sm-4';
	} elseif ((!$footer_first && !$footer_second && $footer_third && $footer_fourth) || (!$footer_first && $footer_second && !$footer_third && $footer_fourth)
	|| (!$footer_first && $footer_second && $footer_third && !$footer_fourth) || ($footer_first && !$footer_second && !$footer_third && $footer_fourth)
	|| ($footer_first && !$footer_second && $footer_third && !$footer_fourth) || ($footer_first && $footer_second && !$footer_third && !$footer_fourth)) {
		$variables['footer_grid_class'] = 'col-sm-6';
	} else {
		$variables['footer_grid_class'] = 'col-sm-12';
	}

}

/**
* Implements hook_preprocess_maintenance_page().
*/
function scholarly_lite_preprocess_maintenance_page(&$variables) {

	$color_scheme = theme_get_setting('color_scheme');
	if ($color_scheme != 'default') {
		drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/style-' .$color_scheme. '.css', array('group' => CSS_THEME, 'type' => 'file'));
	}

	drupal_add_css(drupal_get_path('theme', 'scholarly_lite') . '/fonts/lato-font.css', array('group' => CSS_THEME, 'type' => 'file'));

}

function scholarly_lite_page_alter($page) {

	$mobileoptimized = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'MobileOptimized',
		'content' =>  'width'
		)
	);
	$handheldfriendly = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'HandheldFriendly',
		'content' =>  'true'
		)
	);
	$viewport = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'viewport',
		'content' =>  'width=device-width, initial-scale=1'
		)
	);
	drupal_add_html_head($mobileoptimized, 'MobileOptimized');
	drupal_add_html_head($handheldfriendly, 'HandheldFriendly');
	drupal_add_html_head($viewport, 'viewport');

}

function scholarly_lite_form_alter(&$form, &$form_state, $form_id) {

	if ($form_id == 'search_block_form') {
	unset($form['search_block_form']['#title']);
	$form['search_block_form']['#title_display'] = 'invisible';
	$form_default = t('Enter terms then hit Search...');
	$form['search_block_form']['#default_value'] = $form_default;

	$form['actions']['submit']['#attributes']['value'][] = '';

	$form['search_block_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '{$form_default}';}", 'onfocus' => "if (this.value == '{$form_default}') {this.value = '';}" );
	}

	if(substr($form_id, 0, 30) == 'commerce_cart_add_to_cart_form'){
		$form['submit']['#attributes']['value'][] = 'Subscribe to course';
	}

}
