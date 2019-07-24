<?php

/**
 * @file
 * pece_groups.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function pece_groups_default_rules_configuration() {
  $items = array();
  $items['rules_pece_member_subscribe_pending'] = entity_import('rules_config', '{ "rules_pece_member_subscribe_pending" : {
      "LABEL" : "PECE - member subscribe (Pending)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request for \\u0027[group:title]\\u0027",
            "message" : "[account:name],\\r\\n\\r\\nYour membership to group \\u0027[group:title]\\u0027 located at [group:url] is pending approval.",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] membership request [group:title]",
            "message" : "Hi [group:author:name].\\r\\n\\r\\nUser [account:name] has requested membership on group \\u0027[group:title]\\u0027 Click [site:url]group\\/node\\/[group:nid]\\/admin\\/people to manage group membership.\\r\\n\\r\\n---",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
