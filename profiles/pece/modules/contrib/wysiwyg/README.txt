CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Configuration
 * Support requests
 * Maintainers


INTRODUCTION
------------

Wysiwyg API allows users of your site to use WYSIWYG/rich-text,
and other client-side editors for editing contents. This module
depends on third-party editor libraries, most often based on JavaScript.

For a full description of the module, visit the project page:
https://drupal.org/project/wysiwyg


INSTALLATION
------------

 * Install as usual, see
   https://drupal.org/documentation/install/modules-themes/modules-7

 * Go to Administration » Configuration » Content authoring » Wysiwyg,
   and follow the displayed installation instructions to download and install one
   of the supported editors.


CONFIGURATION
-------------

 * Go to Administration » Configuration » Content authoring » Text formats, and

   - either configure the Full HTML format, assign it to trusted roles, and
     disable "Limit allowed HTML tags", "Convert line breaks...", and
     (optionally) "Convert URLs into links".
     Note that disabling "Limit allowed HTML tags" will allow users to post
     anything, including potentially malicious content. For a more configurable
     alternative to "Limit allowed HTML tags" try
     https://drupal.org/project/wysiwyg_filter.

   - or add a new text format, assign it to trusted roles, and ensure that above
     mentioned input filters are configured as detailed.

 * Setup editor profiles in Administration » Configuration » Content authoring
   » Wysiwyg.


SECURITY
--------

Drupal normally stores all content created by users exactly as they input it
and uses the text format system to filter out potentially malicious scripts or
content during rendering, to avoid attacks like Cross-site scripting (XSS).

Editing content posted by other users in WYSIWYG mode may mean, depending on
the editor used and its current configuration, their potentially malicious
content is rendered and executed by your browser.

If the text format the editor profile has been attached to has known security
filters enabled Wysiwyg will run those filters on content before passing it to
an editor. If the text format used for a field is changed, filters from both
text formats will be applied before passing the contents to the editor on the
selected text format, if any, to keep only content allowed by both filters.
Content not allowed by either filter will then be permanently lost.

Wysiwyg lists the known security filters and their status on editor profiles.
Hooks can be implemented to extend or alter the list of known security filters.
There is also a hook specifically to extend the list of allowed tags used if the
"Limit allowed tags" filter is enabled. See wysiwyg.api.php for information.
If a module already implements the equivalent hooks from CKEditor module those
will be called if no implementation for Wysiwyg module is found.


SUPPORT REQUESTS
----------------

Before posting a support request, carefully read the installation
instructions provided in module documentation page.

Before posting a support request, check Recent log entries at
admin/reports/dblog

Once you have done this, you can post a support request at module issue queue:
https://drupal.org/project/issues/wysiwyg

When posting a support request, please inform if you were able to see any errors
at admin/reports/dblog in Recent log entries.


MAINTAINERS
-----------

Current maintainers:
 * Daniel F. Kudwien (sun) - https://drupal.org/user/54136
 * Henrik Danielsson (TwoD) - https://drupal.org/user/244227

This project has been sponsored by:
 * UNLEASHED MIND
   Specialized in consulting and planning of Drupal powered sites, UNLEASHED
   MIND offers installation, development, theming, customization, and hosting
   to get you started. Visit http://www.unleashedmind.com for more information.
