<?php

include dirname(__FILE__) . '/settings.local.php';

$update_free_access = FALSE;

ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 2000000);

# @TODO: Restore email notifications in the future.
$conf['user_mail_register_pending_approval_notify'] = FALSE;
$conf['user_mail_register_no_approval_required_notify'] = FALSE;

