NODE EXPIRE
===========

This module allows you to set a "timer" into content nodes. When it reaches
zero, you can perform any type of action with the node, such as unpublishing
it or sending an email to the author.

All this power is possible due Rules module. On each cron, Node expire scan for
expired content and let Rules module work with it. You can select several
actions to perform with these nodes.

If using Date Popup of Date module, the date field will activate a Date Popup
widget in order to make the process easier and more fun.

If using Views module, all data will be exported, allowing you to build
custom lists.


INSTALL
=======

This module is not (YET at least) compatible with previous versions.
So its only indicated to new sites.

7.x branch is self-compatible and every effort will be made to keep
it in this state.


USAGE
=====

The first thing you should do is give the proper permissions:
"administer node expire" will allow you to enable the feature on node types
and put a default value. "edit node expire" will allow you to put
the real date on nodes.

Then you should go to admin/content/types and configure the node type
that will use expiration feature. Under "Publishing options"
("Workflow settings" in Drupal 6), put the default expiration date
using PHP strtotime format.

Now, all users that have "edit node expire" will be able to select a different
expiration date during node creation/editing. If not, the default value will be
used. Note that if the user edit the node, the expiration date will not change.

In Drupal 7 version some parameters of the module can be configured within 
a configuration section. It is located in "Workflow" area under Rules module 
configuration section.


CREDITS
=======

Daryl Houston     <daryl@learnhouston.com> (Original author)
Andrew Langland                            (D5-dev and D6-dev rewrite)
Bruno Massa                                (D6 v2 rewrite)
Nik Alexandrov                             (D7-dev rewrite)


RULES MODULE EXAMPLE
====================

For those people that want to use this module quickly, import the code below on
admin/rules/ie/import and it will automatically configure it to unpublish the
content once it expires. Just paste it and have fun.

-------------------------------------------------------------------------------
"Content expired unpublish".

{ "rules_content_expired_unpublish" : {
    "LABEL" : "Content expired unpublish",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : false,
    "REQUIRES" : [ "node_expire", "rules" ],
    "ON" : [ "node_expired" ],
    "IF" : [ { "node_expire_rules_expired_check" : { "node" : [ "node" ] } } ],
    "DO" : [ { "node_unpublish" : { "node" : [ "node" ] } } ]
  }
}


RULES MODULE EXTRA EXAMPLES FOR TESTING
=======================================

Below are some more rules, which are handy for testing. By enabling/disabling
those rules you can publish/unpublish or promote/unpromote content
to front page.
Just enable necessary rules, run cron and see the result. It is helpful during 
the tests to turn on an option "Allow expire date in the past" in the module 
configuration section.  


-------------------------------------------------------------------------------
"Content expired publish".

{ "rules_content_expired_publish" : {
    "LABEL" : "Content expired publish",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : false,
    "REQUIRES" : [ "node_expire", "rules" ],
    "ON" : [ "node_expired" ],
    "IF" : [ { "node_expire_rules_expired_check" : { "node" : [ "node" ] } } ],
    "DO" : [ { "node_publish" : { "node" : [ "node" ] } } ]
  }
}


-------------------------------------------------------------------------------
"Content expired remove from front page".

{ "rules_content_expired_remove_from_front_page" : {
    "LABEL" : "Content expired remove from front page",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "node_expire", "rules" ],
    "ON" : [ "node_expired" ],
    "IF" : [ { "node_expire_rules_expired_check" : { "node" : [ "node" ] } } ],
    "DO" : [ { "node_unpromote" : { "node" : [ "node" ] } } ]
  }
}

-------------------------------------------------------------------------------
"Content expired promote to front page".

{ "rules_content_expired_promote_to_front_page" : {
    "LABEL" : "Content expired promote to front page",
    "PLUGIN" : "reaction rule",
    "ACTIVE" : false,
    "REQUIRES" : [ "node_expire", "rules" ],
    "ON" : [ "node_expired" ],
    "IF" : [ { "node_expire_rules_expired_check" : { "node" : [ "node" ] } } ],
    "DO" : [
      { "node_expire_unset_expired" : { "node" : [ "node" ] } },
      { "node_promote" : { "node" : [ "node" ] } }
    ]
  }
}
