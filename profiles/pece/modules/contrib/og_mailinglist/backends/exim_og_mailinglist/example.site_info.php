<?php

/**
 * Information on how to pass emails to og_mailinglist.
 *
 * @return array of sites with associated POST urls and other data.
 */
function og_mailinglist_site_info() {
  return array (
    // Please use lowercase letters only for the group email domain name.
    // Usually example.com, groups.example.com or g.example.com, it has
    // to match the domain name in admin/config/group/mailinglist/config
    'example.com' => array(
              // Whether to use direct posting or not.
              'direct_posting' => True,
              // Used when directly posting, don't use the leading slash.
              // Host here is the website host.
              'drupal_path' => '/var/www/drupal',
              'host' => 'example.com',
              // Used when posting over HTTP.
              'post_url' => 'http://example.com/?=og_mailinglist',
              // The same as in admin/config/group/mailinglist
              'validation_string' => 'abcdefghijklmnopqrstuv1234567890',
     ),
     // And you might have one more site.
     'example.org' => array(
              'direct_posting' => True,
              'drupal_path' => '/var/www/drupal',
              'host' => 'example.org',
              'post_url' => 'http://example.org/?=og_mailinglist',
              'validation_string' => '1234567890abcdefghijklmnopqrstuv',
     ),
  );
}

