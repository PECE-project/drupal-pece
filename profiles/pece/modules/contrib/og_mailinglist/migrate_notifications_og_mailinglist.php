<?php
/*
 * @file
 *  If you're migrating a site from notifications/messaging to og_mailinglist,
 *  use this script to migrate user's settings. It doesn't work 100% perfect
 *  so you might have to tweak things. Improvements to the script are highly
 *  welcome.
 */

// Set up the drupal directory -- very important.
$DRUPAL_DIR = '/var/www/island_prod';

// Set some server variables so Drupal doesn't freak out.
$_SERVER['SCRIPT_NAME'] = '/script.php';
$_SERVER['SCRIPT_FILENAME'] = '/script.php';
$_SERVER['HTTP_HOST'] = 'example.com';
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';
$_SERVER['REQUEST_METHOD'] = 'POST';

// Act as the first user.
global $user;
$user->uid = 1;

// Gain access to drupal.
// Drupal assumes this is the root dir.
chdir($DRUPAL_DIR);
// Drupal throws a few warnings, so suppress these.
error_reporting(E_ERROR | E_PARSE);
require_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// Restore error reporting to its normal setting.
error_reporting(E_ALL);

// Push all subsriptions in og_uid to og_mailinglist_group_subscription.
// Then update for no email and digest email from notifications.
// Using just data from notifications seemed to miss people somehow.

$results = db_query("SELECT nid, uid FROM {og_uid}");

foreach ($results as $data) {
  //print_r($data);
  $data = array(
      ':nid' => $data['nid'],
      ':uid' => $data['uid'],
    );
  drupal_write_record('og_mailinglist_group_subscription', $data)
}

// The query to pull on current subscriptions SELECT n.uid as uid, f.value as gid, n.send_interval as send_interval FROM notifications n join notifications_fields f on n.sid = f.sid where n.type = "grouptype" and f.field = "group" group by uid, gid order by n.uid
$sql = "SELECT n.uid AS uid, f.value AS gid, n.send_interval AS send_interval
  FROM {notifications} AS n
  JOIN {notifications_fields} AS f
  ON n.sid = f.sid
  WHERE n.type = 'grouptype'
  AND f.field = 'group'
  AND n.send_interval <> 0 "// We've already added those above.
  ."GROUP BY uid, gid
  ORDER BY n.uid";

$results = db_query($sql);

foreach ($results as $data) {
  echo "uid: " . $data['uid'] . " gid: " . $data['gid'] . " interval: " . $data['send_interval'] . "\n";
  if ($data['send_interval'] == -1) {
    echo db_query("UPDATE {og_mailinglist_group_subscription}
         SET subscription_type = 'no email'
         WHERE sid = :sid
         AND uid = :uid",
         array(
           ':sid' => $data['gid'],
           ':uid' => $data['uid'],
         ));
  }
  else {
    echo db_query("UPDATE {og_mailinglist_group_subscription}
         SET subscription_type = 'digest email'
         WHERE sid = :sid
         AND uid = :uid",
         array(
           ':sid' => $data['gid'],
           ':uid' => $data['uid'],
         ));
  }
}

//echo "=== Inserting data into og_mailinglist_thread_subscription for past month of conversations ==";
//// Get list of nodes created in past month
//$results = db_query("SELECT nid
//                    FROM {node}
//                    WHERE created > (UNIX_TIMESTAMP() - 2678400)"); // One month.
//
//// Loop through each node. If not in a space, throw out. If in space, get subscriptions and save.
//while ($data = db_fetch_array($results)) {
//  if ($group_nid = db_result(db_query("SELECT group_nid
//                         FROM og_ancestry
//                         WHERE nid = %d", $data['nid']))) {
//
//    // Node is in a group.
//    $subs = og_mailinglist_get_space_subscriptions($group_nid, 'og');
//    og_mailinglist_save_thread_subscriptions($data['nid'], array_keys($subs));
//    echo "Saved subscriptions for nid: " . $data['nid'] . "\n";
//  }
//}

//echo "testing og_mailinglist_get_space_subscriptions \n\n";
//$subs = og_mailinglist_get_space_subscriptions(251, 'og');
//print_r($subs);
//
//og_mailinglist_save_thread_subscriptions(2232342, array_keys($subs));
//
//$thread_subs = og_mailinglist_get_thread_subscriptions(2232342);
//
//print_r($thread_subs);
