#!/usr/bin/php
<?php

$raw_email = "";

// Reads in raw email off the STDIN and posts the email using our curl command
// for the appropriate site.
$fd = fopen("php://stdin", "r");
while (!feof($fd)) {
  $raw_email .= fread($fd, 1024);
}

// Set command line arguments (sent by the exim4 transport) to variables.
$mail_domain = strtolower($argv[1]);

// Load site info.
require_once('site_info.php');
$sites = og_mailinglist_site_info();

if (empty($sites[$mail_domain])) {
  echo "Could not match the email domain with a Drupal site. ";
  echo "Check that you've setup site_info.php correctly.";
  exit(1);
}

// Here we expect that all required elements are present in that array.
$site = $sites[$mail_domain];

if ($site['direct_posting'] === True) {
  // We bootstrap Drupal now.
  // Set some server variables so Drupal doesn't freak out.
  $_SERVER['SCRIPT_NAME'] = '/og_mailinglist_transport.php';
  $_SERVER['SCRIPT_FILENAME'] = '/og_mailinglist_transport.php';
  $_SERVER['HTTP_HOST'] = $_SERVER['SERVER_NAME'] = $site['host'];
  $_SERVER['REMOTE_ADDR'] = '127.0.0.1';
  $_SERVER['REQUEST_METHOD'] = 'POST';
  $_SERVER['SERVER_SOFTWARE'] = 'Linux';

  // Change to the Drupal directory.
  chdir($site['drupal_path']);
  define('DRUPAL_ROOT', $site['drupal_path']);

  // Silence errors during bootstrap.
  //error_reporting(E_ERROR | E_PARSE);

  // Run the initial Drupal bootstrap process.
  require_once('includes/bootstrap.inc');
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

  // Restore error reporting to its normal setting.
  error_reporting(E_ALL);

  // Include og_mailinglist_transport.inc file.
  module_load_include('inc', 'og_mailinglist', 'og_mailinglist_transport');

  // Finally post the email.
  _og_mailinglist_process_email($raw_email);
}
else {
  $token = md5($site['validation_string'] . $raw_email);

  // Since direct posting is disabled, we post over HTTP.
  // Here we use one of two libraries in the preferred order.
  @include_once 'HTTP/Request2.php';
  if (class_exists("HTTP_Request2")) {
    $request = new HTTP_Request2($site['post_url'], HTTP_Request2::METHOD_POST);
    $request->setHeader('Expect:', True);
    $request->addPostParameter('message', $raw_email);
    $request->addPostParameter('token', $token);

    try {
      $response = $request->send();
      if (200 == $response->getStatus()) {
        // All good, do nothing!
      }
      else {
          echo 'Unexpected HTTP status: ' . $response->getStatus() . ' ' .
               $response->getReasonPhrase();
      }
    }
    catch (HTTP_Request2_Exception $e) {
        echo 'Error: ' . $e->getMessage();
    }
  }
  else {
    // We found no HTTP_Request2 class.
    // Let's post using Curl.
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, FALSE);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Expect:'));
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_HEADER, 1);
    curl_setopt($ch, CURLOPT_URL, $site['post_url']);

    // Prepare the field values being posted to the service.
    $data = array(
      'message' => $raw_email,
      'token' => $token,
    );

    curl_setopt($ch, CURLOPT_POSTFIELDS, $data);

    // Make the request.
    curl_exec($ch);
  }
}

