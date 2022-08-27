Administration Views
--------------------
The Administration Views module replaces your content administration and user
administration pages with actual Drupal views that provide expanded field and
filtering capabilities, and also the ability to quickly customize your
administration pages since they are now real Views. This module improves the
usability of searching and modifying content.


Features
--------------------------------------------------------------------------------
* Provides new replacements for the following:
  * Books admin page
  * Comments admin page
  * Node admin page
  * User admin page
  * Vocabular admin page

* Includes a separate Views display plugin that allows replacing system pages.
  This is provided by a submodule and may be used independently of the included
  administrative pages.


Requirements
--------------------------------------------------------------------------------
* Views: https://www.drupal.org/project/views
* Views Bulk Operations: https://www.drupal.org/project/views_bulk_operations


Installation
--------------------------------------------------------------------------------
Install the Administration Views module as you would normally install a
contributed Drupal module. Visit https://www.drupal.org/node/1897420 for
further information.

Included in this package is the Admin Views System Display module, which will be
automatically installed when Administration Views module itself is installed. It
may also be used on its own, should a site want to override system pages without
needing to use the included default displays.


Configuration
--------------------------------------------------------------------------------
Enable the Administrative views module from the module page.

This module requires no configuration. It adds five new items to the Views page;
now that these are views, they can be edited and enhanced to fit individual
needs by adding fields and filters. These Views integrate well with Views Bulk
Operations.


Troubleshooting
--------------------------------------------------------------------------------
If you are upgrading from an older version of Administration Views and the
default views have been overridden (saved in the database) you could encounter
issues or not see any new changes unless you revert these views, so the default
in-code views are used. This can be done in the Views UI listing or using drush
(drush cter views_view --module=admin_views).


Credits / contact
--------------------------------------------------------------------------------
Currently maintained by Damien McKenna [1]; previously maintained by Vijaya
Chandran Mani [2], Daniel Wehner [3], Damian Lee [4] and Yonas Yanfa [5].
Originally written by Daniel Kudwien [6].

Ongoing development is sponsored by Mediacurrent [7]. Original development was
sponsored by Unleashed Mind [8].

The best way to contact the authors is to submit an issue, be it a support
request, a feature request or a bug report, in the project issue queue:
  https://www.drupal.org/project/issues/admin_views


References
--------------------------------------------------------------------------------
1: https://www.drupal.org/u/damienmckenna
2: https://www.drupal.org/u/vijaycs85
3: https://www.drupal.org/u/vijaycs85
4: https://www.drupal.org/u/damiankloip
5: https://www.drupal.org/u/fizk
6: https://www.drupal.org/u/sun
7: https://www.mediacurrent.com/
8: https://www.drupal.org/unleashed-mind
