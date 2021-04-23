
Module: Matomo Analytics
Author: Alexander Hass <https://www.hass.de/>


Description
===========
Adds the Matomo tracking system to your website.

Requirements
============

* Matomo installation
* Matomo website account


Installation
============
* Copy the 'matomo' module directory in to your Drupal
sites/all/modules directory as usual.


Usage
=====
In the settings page enter your Matomo website ID.

You will also need to define what user roles should be tracked.
Simply tick the roles you would like to monitor.

All pages will now have the required JavaScript added to the
HTML footer can confirm this by viewing the page source from
your browser.


Custom variables
=================
One example for custom variables tracking is the "User roles" tracking. Enter
the below configuration data into the custom variables settings form under
admin/config/system/matomo.

Slot: 1
Name: User roles
Value: [current-user:matomo-role-names]
Scope: Visitor

Slot: 1
Name: User ids
Value: [current-user:matomo-role-ids]
Scope: Visitor

More details about custom variables can be found in the Matomo API documentation
at https://matomo.org/docs/javascript-tracking/#toc-custom-variables.


Advanced Settings
=================
You can include additional JavaScript snippets in the advanced
textarea. These can be found on various blog posts, or on the
official Matomo pages. Support is not provided for any customisations
you include.

To speed up page loading you may also cache the matomo.js
file locally. You need to make sure the site file system is in public
download mode.


Known issues
============
Drupal requirements (https://drupal.org/requirements) tell you to configure 
PHP with "session.save_handler = user", but your Matomo installation may
not work with this configuration and gives you a server error 500.

1. You are able to workaround with the PHP default in your php.ini:

   [Session]
   session.save_handler = files

2. With Apache you may overwrite the PHP setting for the Matomo directory only.
   If Matomo is installed in /matomo you are able to create a .htaccess file in
   this directory with the below code:

   # PHP 4, Apache 1.
   <IfModule mod_php4.c>
     php_value session.save_handler files
   </IfModule>

   # PHP 4, Apache 2.
   <IfModule sapi_apache2.c>
     php_value session.save_handler files
   </IfModule>

   # PHP 5, Apache 1 and 2.
   <IfModule mod_php5.c>
     php_value session.save_handler files
   </IfModule>
