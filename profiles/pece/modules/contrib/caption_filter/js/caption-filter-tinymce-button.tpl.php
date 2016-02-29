<?php
/**
 * @file
 * Template for the TinyMCE button dialog.
 *
 * Available variables:
 * - $form: the form array.
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php print drupal_get_title(); ?></title>
<?php print drupal_get_js(); ?>
</head>
<body>
  <?php print drupal_render($form); ?>
</body>
</html>
