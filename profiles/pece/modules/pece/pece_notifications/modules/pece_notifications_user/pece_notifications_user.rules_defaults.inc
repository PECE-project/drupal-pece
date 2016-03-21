<?php
/**
 * @file
 * pece_notifications_user.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function pece_notifications_user_default_rules_configuration() {
  $items = array();
  $items['rules_pece_awaiting_approval_email'] = entity_import('rules_config', '{ "rules_pece_awaiting_approval_email" : {
      "LABEL" : "PECE - Account awaiting approval e-mail",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "PECE" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [ { "user_is_blocked" : { "account" : [ "account" ] } } ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Account details for [account:name] at [site:name] (pending admin approval)",
            "message" : "[account:name],\\r\\n\\r\\nThank you for registering at [site:name]. Your application for an account is currently pending approval. Once it has been approved, you will receive another e-mail containing information about how to log in, set your password, and other details.\\r\\n\\r\\n\\r\\n--  [site:name] team",
            "language" : [ "account:language" ]
          }
        }
      ]
    }
  }');
  return $items;
}
