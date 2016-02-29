<?php
$path_ogm = drupal_get_path('module', 'og_mailinglist');
require_once($path_ogm . "/og_mailinglist_transport.inc");
$raw_email = file_get_contents($path_ogm . "/testing/applemail");
$email['original_email_text'] = $raw_email;

// import an email
$email = _og_mailinglist_parse_email($email);
//print_r($email);

// create a new one
$node = node_load(103);
_og_mailinglist_email_node_email($email, $node);
